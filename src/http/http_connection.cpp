#include "expresscpp/http/http_connection.hpp"

namespace express {
	namespace http {
		http_connection::http_connection(asio::ip::tcp::socket&& sock)
			:socket_(std::move(sock))
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

		void http_connection::processRequest()
		{
			auto data = http_io::deserialize(rawData_);

			if (!data)
				return;
			
			req_ = data.value();
			request req(req_);
			response res(req.reqVersion);

			res.send("Hello 123");

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
