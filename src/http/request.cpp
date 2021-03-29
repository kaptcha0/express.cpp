#include "expresscpp/http/request.hpp"

namespace express {
	namespace http {
		request::request(raw_request& request)
			:raw(&request)
		{
			parseRequest();
		}

		void request::parseRequest()
		{
			// Parsing status string
			const std::string& head = raw->reqLine;

			size_t pathBegin = head.find_first_of(" ");
			size_t pathEnd = head.find_last_of(" ");

			if (pathBegin == std::string::npos || pathEnd == std::string::npos)
				return;

			this->path = head.substr(pathBegin + 1, pathEnd);

			// Getting query info
			size_t queryStart = path.find('?');

			if (queryStart != std::string::npos)
			{
				this->queries = query(this->path.substr(queryStart + 1, this->path.length()));

				this->path = this->path.substr(0, queryStart);
			}

			this->requestMethod = method(head.substr(0, pathBegin));
			this->reqVersion = version(head.substr(pathEnd + 1, head.length()));

			// Parsing headers
			this->headers = raw->headers;

			// Parsing body
			this->body = raw->body;
			
		}
	}
}