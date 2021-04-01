#include "expresscpp/http/core.hpp"

namespace express {
	HttpServer::HttpServer(uint16_t port)
		:port_(port), socket_(io_context_)
	{	}

	HttpServer::HttpServer(std::string addr, uint16_t port)
		:address_(asio::ip::make_address(addr)), socket_(io_context_), port_(port)
	{	}

	void HttpServer::eventLoop(asio::ip::tcp::acceptor& acc)
	{
		acc.async_accept(socket_, [&, this](const asio::error_code& ec) {

			std::cout << "\nAccept " << ec.value() << ": " << ec.message() << std::endl;

			if (!ec)
			{
				auto conn = std::make_shared<http::http_connection>(std::move(socket_));
				conn->start();
			}

			this->eventLoop(acc);
		});
	}

	void HttpServer::listen()
	{
		socket_ = asio::ip::tcp::socket(io_context_);
			
		// Setup socket
		asio::ip::tcp::acceptor acceptor(io_context_, {address_, port_});

		std::cout << "Listening on " << address_.to_string() << ":" << port_ << "\n";

		// Start listening loop
		eventLoop(acceptor);

		io_context_.run();
	}
}