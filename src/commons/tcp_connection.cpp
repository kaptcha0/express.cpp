#include "expresscpp/commons/tcp_connection.hpp"

namespace express {
	namespace commons {
		tcp_connection::tcp_connection(asio::ip::tcp::socket* socket)
			:socket_(socket)
		{	}

		void tcp_connection::readRequest()
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

		void tcp_connection::start()
		{
			this->readRequest();
		}
	}
}