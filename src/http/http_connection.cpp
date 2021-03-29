#include "expresscpp/http/http_connection.hpp"

namespace express {
	namespace http {
		http_connection::http_connection(asio::ip::tcp::socket* sock)
			:socket_(std::move(sock))
		{	}

		void http_connection::start() {
			readRequest();
		}

		void http_connection::readRequest()
		{
			std::function<void(const asio::error_code &ec, std::size_t bytes_transferred)> readHandler = [&](const asio::error_code &ec, std::size_t bytes_transferred) {
				if (!ec)
				{
					socket_->async_read_some(asio::buffer(buffer_), [&](const asio::error_code &ec, std::size_t bytes_transferred) {
						readHandler(ec, bytes_transferred);
					});
				}
			};

			socket_->async_read_some(asio::buffer(buffer_), readHandler);

			rawData_ = buffer_;


			processRequest();
		}

		void http_connection::processRequest()
		{
			req_ = http_io::deserialize(rawData_);
			request req(req_);
			response res(req.reqVersion);
		}

		void http_connection::writeRequest(response& r)
		{
			raw_response res = r.construct();
			std::string sendData = res.resLine + "\r\n" + static_cast<std::string>(res.headers) + res.body;
		}
	}
}