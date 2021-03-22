#define _WIN32_WINNT 0x0601

#include <iostream>
#include <expresscpp/http.hpp>


int main()
{
	express::HttpServer server(123);
	std::system("pause");
}
