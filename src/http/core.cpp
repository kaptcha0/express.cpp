#include <expresscpp/http/core.hpp>

namespace express {
	HttpServer::HttpServer(uint16_t port)
		:port_(port)
	{
		std::cout << "Listening on port " << port << "\n";
	}

	void HttpServer::listen(int port)
	{

	}
}