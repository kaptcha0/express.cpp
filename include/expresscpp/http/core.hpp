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

	public:
		HttpServer(uint16_t);
		HttpServer(std::string, uint16_t);
		HttpServer() = default;

		// GET request handler
		void get(std::string, http::RequestHandler);

		// Starts listening
		void listen();
	};
}

#endif