#include "expresscpp/http/http_connection.hpp"

namespace express {
	namespace http {
		http_connection::http_connection(asio::ip::tcp::socket&& sock, std::multimap<std::string, http::handler>* handlers)
			:socket_(std::move(sock)), handlerMap_(std::move(handlers))
		{	}

		void http_connection::start() {
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

			std::cout << "Read " << ec.value() << ": " << ec.message() << "\n";

			if (rawData_.compare("") == 0)
				return;


			processRequest();
		}

		void http_connection::callHandlers(request& req, response& res)
		{
			auto h = handlerMap_->equal_range(req.path);
			bool called = false;

			if (h.first == h.second)
			{
				res.statusCode(405);
			}

			for (auto it = h.first; it != h.second; ++it)
			{
				handler& handle = it->second;
				
				if (handle.method == req.requestMethod)
				{
					handle.handle(req, res);
					called = true;
				}	
			}

			if (!called)
			{
				res.statusCode(404);
				res.send("Cannot " + static_cast<std::string>(req.requestMethod) + " on '" + req.path + "'");
			}


		}

		void http_connection::processRequest()
		{
			auto data = http_io::deserialize(rawData_);

			if (!data)
				return;
			
			req_ = data.value();
			request req(req_);
			response res(req.reqVersion);

			callHandlers(req, res);

			writeRequest(&req, &res);
		}

		void http_connection::writeRequest(request* req, response* res)
		{
			auto self = shared_from_this();
			raw_response rres = res->construct();
			std::string sendData = rres.resLine + "\r\n" + static_cast<std::string>(rres.headers) + "\r\n" + rres.body;
			

			asio::async_write(socket_, asio::buffer(&sendData[0], sendData.size()), [&, self](asio::error_code ec, size_t bytes) {
				std::cout << "Request from: " << socket_.remote_endpoint(ec).address().to_string() << " " << bytes << "B (" << bytes / 1000 << " KB) transfered\n";
				std::cout << "Write " << ec.value() << ": " << ec.message() << "\n";
			});
		}
	}
}
