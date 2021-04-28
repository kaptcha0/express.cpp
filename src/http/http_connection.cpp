#include "expresscpp/http/http_connection.hpp"

namespace express {
	namespace http {
		http_connection::http_connection(asio::ip::tcp::socket&& sock, std::multimap<std::string, http::handler>* handlers)
			:socket_(std::move(sock)), handlerMap_(std::move(handlers))
		{	}

		void http_connection::start() {
			commons::Timer t("http_connection::start", true);
			readRequest();
		}

		void http_connection::readRequest()
		{
			auto self = shared_from_this();

			asio::error_code ec;


			std::vector<char> buf(1024 * 4);

			size_t bytes = socket_.read_some(asio::buffer(buf), ec);

			if (ec)
				return;

			rawData_ = buf.data();

			if (rawData_.compare("") == 0)
				return;


			processRequest();
		}

		void http_connection::callHandlers(request& req, response& res)
		{
			// Not most optimal way; will refactor later
			auto getValid = [req](std::string& originalPath, std::multimap<std::string, http::handler>* handlers) {
				commons::Timer t("http_connection::calHandlers::getValid", true);

				std::vector<http::handler*> valid;

				for (auto& it : *handlers)
				{
					const std::string& path = it.first;
					express::http::handler& handle = it.second;
					
					// Looks to see if all queries are there
					bool add = true;

					// If the request path does not match the handler path
					if (path.compare(originalPath) != 0)
					{
						// Look for wildcard '*'
						size_t wildcard = path.find('*');

						// If wildcard is not found, continue the search
						if (wildcard == std::string::npos)
							goto QUERIES;

						// Check if root of the handler is equal to the root request path
						std::string root = path.substr(0, wildcard);

						if (originalPath.find(root) == std::string::npos)
							goto QUERIES;
							
						// Look for query format '{key}'
						QUERIES: {
							size_t pos = path.find('{');
							size_t endPos = path.find('}');

							root = path.substr(0, pos);

							if (originalPath.find(root) == std::string::npos)
								continue;

							// Find all query strings
							while (pos != std::string::npos && endPos != std::string::npos)
							{
								std::string query = path.substr(pos + 1, endPos);

								if (size_t danglingBracket = query.find('}'); danglingBracket != std::string::npos)
								{
									query = query.substr(0, danglingBracket);
								}

								if (!req.queries.exists(query.c_str()))
								{
									continue;
								}

								// Get the next occurrence from the current position
								pos = path.find('{', pos + 1);
								endPos = path.find('}', endPos);
							}
						}

					}

					
					valid.push_back(&handle);
				}

				return valid;
			};

			std::vector<http::handler*> h = getValid(req.path, handlerMap_);
			
			bool called = false;

			if (h.empty())
			{
				res.setStatus(405);
				return;
			}

			for (auto handle : h)
			{
				if (handle->method == req.requestMethod || handle->method == method::ALL)
				{
					handle->handle(req, res);
					called = true;
				}	
			}

			if (!called)
			{
				res.setStatus(404);
				res.send("Cannot " + static_cast<std::string>(req.requestMethod) + " on '" + req.path + "'");
			}

		}

		void http_connection::processRequest()
		{
			auto data = http_io::deserialize(rawData_);

			if (!data)
				return;
			
			req_ = data.value();
			request req(req_, socket_.remote_endpoint().address());

			// Check if request path has is a wildcard
			if (req.path.compare("/*") == 0)
				return;

			response res(req.reqVersion);

			callHandlers(req, res);

			writeRequest(&req, &res);
		}

		void http_connection::writeRequest(request* req, response* res)
		{
			auto self = shared_from_this();
			raw_response rres = res->construct();
			std::string sendData = rres.resLine + "\r\n" + static_cast<std::string>(rres.headers) + "\r\n" + rres.body;
			

			asio::async_write(socket_, asio::buffer(&sendData[0], sendData.size()), [&, self](asio::error_code ec, size_t bytes) {	});
		}
	}
}
