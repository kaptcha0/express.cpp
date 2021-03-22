#include <expresscpp/http/server.hpp>

namespace express {
	HttpServer::HttpServer(uint16_t port)
		:m_port(port)
	{
		std::cout << "Listening on port " << port << "\n";
	}
}