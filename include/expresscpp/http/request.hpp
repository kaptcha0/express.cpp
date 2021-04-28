#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "expresscpp/http/query.hpp"
#include "expresscpp/commons/pch.hpp"
#include "expresscpp/http/headers.hpp"
#include "expresscpp/http/cookies.hpp"
#include "expresscpp/http/raw_parsed.hpp"

namespace express {
	namespace http {
		struct http_connection;

		class request 
		{
			friend struct http_connection;

		private:
			version reqVersion;
			raw_request* raw;

			// Tranforms `raw_request` to `request`
			void parseRequest();

		public:
			method requestMethod;
			http::headers headers;
			http::cookies cookes;
			asio::ip::address address;
			std::string path;
			std::string body;
			query queries;

			request(raw_request&, asio::ip::address);
		};
	}
}

#endif