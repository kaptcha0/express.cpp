#pragma once
#include "expresscpp/pch.hpp"

namespace express {
	class HttpServer
	{
	private:
		uint16_t port_;
		asio::io_context io_context_;
		asio::ip::tcp::acceptor acceptor_;

	public:
		HttpServer(uint16_t);
		HttpServer() = default;

		void listen(int);
	};
}