#include <iostream>
#include <filesystem>
#include <expresscpp/http.hpp>
#define _WIN32_WINNT 0x0601


int main()
{
	express::HttpServer server(8080);

	std::filesystem::current_path("../samples/basic_server");

	std::cout << "CWD: " << std::filesystem::current_path() << std::endl;

	server.get("/", [](express::http::request& req, express::http::response& res) {
		res.send("Works");
	});

	server.get("/foo", [](express::http::request& req, express::http::response& res) {
		res.sendFile("pages/foo.html");
	});

	server.listen();

	std::system("pause");
}
