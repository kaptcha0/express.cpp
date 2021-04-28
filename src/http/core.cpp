#include "expresscpp/http/core.hpp"

namespace express {
	HttpServer::HttpServer(uint16_t port)
		:port_(port), socket_(io_context_)
	{	}

	HttpServer::HttpServer(const char* addr, uint16_t port)
		:address_(asio::ip::make_address(addr)), socket_(io_context_), port_(port)
	{	}

	void HttpServer::eventLoop(asio::ip::tcp::acceptor& acc)
	{
		acc.async_accept(socket_, [&, this](const asio::error_code& ec) {
			if (!ec)
			{
				auto conn = std::make_shared<http::http_connection>(std::move(socket_), std::move(&handlers_));
				conn->start();
			}

			this->eventLoop(acc);
		});
	}

	inline void HttpServer::appendToHandlers(const char* path, http::RequestHandler* handle, http::method method)
	{
		handlers_.emplace(path, http::handler{ method, *handle });
	}
	
	void HttpServer::use(const char* path, http::RequestHandler handle)
	{
		appendToHandlers(path, &handle, http::method::ALL);
	}

	void HttpServer::get(const char* path, http::RequestHandler handler)
	{
		appendToHandlers(path, &handler, http::method::GET);
	}

	void HttpServer::post(const char* path, http::RequestHandler handler)
	{
		appendToHandlers(path, &handler, http::method::POST);
	}

	void HttpServer::head(const char* path, http::RequestHandler handler)
	{
		appendToHandlers(path, &handler, http::method::HEAD);
	}

	void HttpServer::put(const char* path, http::RequestHandler handler)
	{
		appendToHandlers(path, &handler, http::method::PUT);
	}

	void HttpServer::_delete(const char* path, http::RequestHandler handler)
	{
		appendToHandlers(path, &handler, http::method::_DELETE);
	}

	void HttpServer::trace(const char* path, http::RequestHandler handler)
	{
		appendToHandlers(path, &handler, http::method::TRACE);
	}

	void HttpServer::connect(const char* path, http::RequestHandler handler)
	{
		appendToHandlers(path, &handler, http::method::CONNECT);
	}

	void HttpServer::options(const char* path, http::RequestHandler handler)
	{
		appendToHandlers(path, &handler, http::method::OPTIONS);
	}

	void HttpServer::listen()
	{
		socket_ = asio::ip::tcp::socket(io_context_);
			
		// Setup socket
		asio::ip::tcp::acceptor acceptor(io_context_, {address_, port_});

		// Start listening loop
		eventLoop(acceptor);

		std::cout << "Listening on " << address_.to_string() << ":" << port_ << " (Press any key to stop the server)\n";

		std::thread t([&, this]() {
			// Wait for key press
			std::cin.get();

			// Close all services
			acceptor.cancel();
			acceptor.close();

			socket_.shutdown(asio::socket_base::shutdown_both);

			io_context_.stop();


			std::cout << "Shutdown socket and acceptor. Server terminated successfully\n\n";
		});

		t.detach();
		
		io_context_.run();

	}
}