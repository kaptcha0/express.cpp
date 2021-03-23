#include "expresscpp/http/http_io.hpp"

namespace express { 
	namespace http {
		raw_request http_io::deserialize(const std::string& data)
		{
			const char* reqline;
			const char* body;
			std::multimap<std::string, std::string> headers;

			size_t start = 0, end = data.find_first_of("\r\n\r\n");
			reqline = data.substr(start, end).c_str();

			start = end;

			std::istringstream iss(data.substr(start, data.length()));

			for (std::string line; std::getline(iss, line, '\r');)
			{
				size_t separator = line.find(": ");
				
				std::string key = line.substr(0, separator), value = line.substr(separator + 2, line.length());

				std::pair<std::string, std::string> head = std::make_pair(key, value);

				headers.insert(head);
			}

			return raw_request{reqline, headers, body};
		}

		std::string http_io::serialize(const raw_response& res)
		{
			std::string headers;

			for (auto header : res.headers)
				headers += header.first + ": " + header.second;

			return res.resLine + headers + res.body;
		}
	}
}