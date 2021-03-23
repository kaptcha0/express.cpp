#include <iostream>
#include <expresscpp/http.hpp>
#define _WIN32_WINNT 0x0601


int main()
{
	express::HttpServer server(8080);

	server.listen();

	std::system("pause");
}
