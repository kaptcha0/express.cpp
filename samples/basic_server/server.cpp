#include <iostream>
#include <filesystem>
#include <expresscpp/http.hpp>
#define _WIN32_WINNT 0x0601

#define EXPRESS_DEBUG


int main()
{
	express::HttpServer server("192.168.1.219", 8080);

	/* 
		- Sets working directory from build folder to folder containing this file
		- Nessesary for correct file I/O 
	*/
	std::filesystem::current_path("../samples/basic_server");

	// Wild card for all request
	server.use("/*", [](express::http::request& req, express::http::response& res) {
		std::cout << static_cast<std::string>(req.requestMethod) << " Request on '" 
			<< req.path << "' From '" << req.address.to_string() << "'\n";
	});

	server.get("/", [](express::http::request& req, express::http::response& res) {
		res.send("Works");
	});

	server.get("/favicon.ico", [](express::http::request& req, express::http::response& res) {
		res.sendFile("assets/troll.ico");
	});

	server.get("/foo", [](express::http::request& req, express::http::response& res) {
		res.sendFile("pages/foo.html");
	});

	server.get("/foo/data{bar}{bo}", [](express::http::request& req, express::http::response& res) {
		res.send("Bar is " + req.queries["bar"] + "<br>Bo is " + req.queries["bo"]);
	});

	server.listen();

	std::system("pause");
}
