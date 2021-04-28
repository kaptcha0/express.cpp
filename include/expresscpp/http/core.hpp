#ifndef CORE_HPP
#define CORE_HPP

#include <map>
#include <thread>
#include "expresscpp/http/types.hpp"
#include "expresscpp/commons/pch.hpp"
#include "expresscpp/http/http_connection.hpp"

namespace express {
	class HttpServer
	{
	private:
		// The port number
		uint16_t port_;

		// Address
		asio::ip::address address_ = asio::ip::make_address("127.0.0.1");

		// IO Context
		asio::io_context io_context_;

		// Listening socket
		asio::ip::tcp::socket socket_;

		// All handlers
		std::multimap<std::string, http::handler> handlers_;

		// Handles all connections
		void eventLoop(asio::ip::tcp::acceptor&);

		inline void appendToHandlers(const char*, http::RequestHandler*, http::method);

	public:
		HttpServer(uint16_t);
		HttpServer(const char*, uint16_t);
		HttpServer() = default;

		// Global middleware
		void use(const char*, http::RequestHandler);

		// GET request handler
		void get(const char*, http::RequestHandler);

		// POST request handler
		void post(const char*, http::RequestHandler);

		// HEAD request handler
		void head(const char*, http::RequestHandler);

		// PUT request handler
		void put(const char*, http::RequestHandler);

		// DELETE request handler
		void _delete(const char*, http::RequestHandler);

		// TRACE request handler
		void trace(const char*, http::RequestHandler);

		// CONNECT request handler
		void connect(const char*, http::RequestHandler);

		// OPTIONS request handler
		void options(const char*, http::RequestHandler);

		// Starts listening
		void listen();
	};
}

#endif