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
				auto conn = std::make_shared<http::http_connection>(std::move(socket_), std::move(&handlers_));
				conn->start();
			}

			this->eventLoop(acc);
		});
	}

	void HttpServer::get(std::string path, http::RequestHandler handler)
	{
		handlers_.emplace(path, http::handler{ http::method::GET, handler});
	}

	void HttpServer::listen()
	{
		socket_ = asio::ip::tcp::socket(io_context_);
			
		// Setup socket
		asio::ip::tcp::acceptor acceptor(io_context_, {address_, port_});

		// Start listening loop
		eventLoop(acceptor);

		std::cout << "Listening on " << address_.to_string() << ":" << port_ << "\n";

		std::thread t([this]() {
			std::cin.get();
			io_context_.stop();
			std::cout << "Terminated server\n";
		});

		t.detach();
		
		io_context_.run();

	}
}