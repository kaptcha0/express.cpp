#include <expresscpp/http/core.hpp>

namespace express {
	HttpServer::HttpServer(uint16_t port)
		:port_(port), socket_(io_context_)
	{	}

	HttpServer::HttpServer(std::string addr, uint16_t port)
		:address_(asio::ip::make_address(addr)), socket_(io_context_), port_(port)
	{	}

	void HttpServer::eventLoop(asio::ip::tcp::acceptor* acc)
	{
		acc->async_accept(socket_, [&, this](const asio::error_code& ec)
		{
			if (!ec)
			{
				std::shared_ptr<http::http_connection> conn = std::make_shared<http::http_connection>(&socket_);
			}

			this->eventLoop(acc);
		});
	}

	void HttpServer::listen()
	{
		try 
		{
			// Setup socket
			asio::ip::tcp::acceptor acceptor{io_context_, {address_, port_}};

			std::cout << "Listening on port " << address_.to_string() << ":" << port_ << "\n";

			eventLoop(&acceptor);

			io_context_.run();
		}
		catch (const std::exception& e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}
	}
}