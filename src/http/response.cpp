#include "expresscpp/http/response.hpp"

namespace express {
	namespace http {
		response::response(version v)
			:statusCode(status::OK), resVersion(v)
		{
			headers.set("Connection", "Close");
		}

		raw_response response::construct()
		{
			std::string head = static_cast<std::string>(resVersion) + " " + std::to_string(statusCode) + " " + static_cast<std::string>(statusCode);
			return raw_response{head, headers, body.str()};
		}

		void response::status(uint16_t status)
		{
			statusCode = static_cast<http::status>(status);
		}

		void response::setHeader(std::string key, std::string value)
		{
			headers[key] = std::vector<std::string>{value};
		}

		void response::send(const std::string data)
		{
			body.str(data);
		}
		
		void response::sendFile(const std::string filename)
		{
			const auto getContentType = [](const std::string* name) {
				const auto iequals = [](const std::string& ext, const char* type) {
					if (ext.compare(type) == 0)
						return true;
					return false;
				};

				const size_t pos = name->find_last_of('.');

				if (pos == std::string::npos)
					return "INVALID";

				const std::string ext = name->substr(pos + 1, name->length());

				if (iequals(ext, ".htm"))  return "text/html";
				if (iequals(ext, ".html")) return "text/html";
				if (iequals(ext, ".php"))  return "text/html";
				if (iequals(ext, ".css"))  return "text/css";
				if (iequals(ext, ".txt"))  return "text/plain";
				if (iequals(ext, ".js"))   return "application/javascript";
				if (iequals(ext, ".json")) return "application/json";
				if (iequals(ext, ".xml"))  return "application/xml";
				if (iequals(ext, ".swf"))  return "application/x-shockwave-flash";
				if (iequals(ext, ".flv"))  return "video/x-flv";
				if (iequals(ext, ".png"))  return "image/png";
				if (iequals(ext, ".jpe"))  return "image/jpeg";
				if (iequals(ext, ".jpeg")) return "image/jpeg";
				if (iequals(ext, ".jpg"))  return "image/jpeg";
				if (iequals(ext, ".gif"))  return "image/gif";
				if (iequals(ext, ".bmp"))  return "image/bmp";
				if (iequals(ext, ".ico"))  return "image/vnd.microsoft.icon";
				if (iequals(ext, ".tiff")) return "image/tiff";
				if (iequals(ext, ".tif"))  return "image/tiff";
				if (iequals(ext, ".svg"))  return "image/svg+xml";
				if (iequals(ext, ".svgz")) return "image/svg+xml";
				return "application/text";
			};

			headers["Content-Type"][0] = getContentType(&filename);

			std::ifstream readStream(filename);
			std::string file((std::istreambuf_iterator<char>(readStream)),
				std::istreambuf_iterator<char>());

			status(status::Accepted);
			headers["Content-Length"][0] = file.length();

			body.str(file);
		}
	}
}