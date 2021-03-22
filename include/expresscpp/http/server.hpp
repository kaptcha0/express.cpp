#pragma once
#include "expresscpp/pch.hpp"

namespace express {
	class HttpServer
	{
	private:
		uint16_t m_port;

	public:
		HttpServer(uint16_t);
		HttpServer() = default;
	};
}