#include "expresscpp/http/http_connection.hpp"

namespace express {
	namespace http {
		http_connection::http_connection(asio::ip::tcp::socket* sock)
			:socket_(sock)
		{	}

		void http_connection::start() {
			readRequest();
			processRequest();
		}

		void http_connection::readRequest()
		{
			std::function<void(const asio::error_code &ec, std::size_t bytes_transferred)> readHandler = [&](const asio::error_code &ec, std::size_t bytes_transferred) {
				if (!ec)
				{
					rawData_ += buffer_;
					socket_->async_read_some(asio::buffer(buffer_), [&](const asio::error_code &ec, std::size_t bytes_transferred) {
						readHandler(ec, bytes_transferred);
					});
				}
			};

			socket_->async_read_some(asio::buffer(buffer_), readHandler);
		}

		void http_connection::processRequest()
		{
			req_ = http_io::deserialize(rawData_);
			socket_->write_some(asio::buffer("HTTP/1.1 200 OK\r\n\r\nHello world"));
		}
	}
}