#include "expresscpp/http/http_io.hpp"

namespace express { 
	namespace http {
		std::optional<raw_request> http_io::deserialize(const std::string& data)
		{
			std::string reqline, body;
			http::headers headers;

			// Parse request line

			size_t start = 0, end = data.find_first_of("\r\n");
			
			if (end == std::string::npos)
				return {	};

			reqline = data.substr(start, end).c_str();

			start = end + 2;
			end = data.length();

			// Parse headers

			std::istringstream iss(data.substr(start, data.length()));

			for (std::string line; std::getline(iss, line, '\r');)
			{
				size_t separator = line.find(": ");

				if (separator == std::string::npos)
					continue;
				
				std::string key = line.substr(0, separator);

				if (key[0] == '\n')
					key = key.substr(1, key.length());

				std::string value = line.substr(separator + 2, line.length());

				headers.set(key, value);
			}

			// Get body

			start = data.find("\r\n\r\n");

			if (start == std::string::npos)
				return {	};


			body = data.substr(start + 4, end);

			return raw_request{reqline, headers, body};
		}

		std::string http_io::serialize(const raw_response& res)
		{
			return res.resLine + "\r\n" + static_cast<std::string>(res.headers) + "\r\n\r\n" + res.body;
		}
	}
}