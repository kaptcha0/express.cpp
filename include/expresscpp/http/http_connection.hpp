#ifndef HTTP_CONNECTION_HPP
#define HTTP_CONNECTION_HPP

#include <array>
#include "expresscpp/http/types.hpp"
#include "expresscpp/commons/pch.hpp"
#include "expresscpp/http/request.hpp"
#include "expresscpp/http/http_io.hpp"
#include "expresscpp/http/response.hpp"
#include "expresscpp/http/raw_parsed.hpp"

namespace express {
	namespace http {
		struct http_connection : public std::enable_shared_from_this<http_connection>
		{
		private:
			// Raw request, after parsing
			raw_request req_;

			// Raw response, after parsing
			raw_response res_;

			// Socket to read/write from
			asio::ip::tcp::socket socket_;

			// Raw data from read
			std::string rawData_;

			std::multimap<std::string, http::handler>* handlerMap_;

			// Handles reading data
			void readRequest();

			// Handles parsing requests
			void processRequest();

			// Finds relevent handlers
			void callHandlers(request&, response&);

			// Sends the request to the client
			void writeRequest(request*, response*);

		public:
			http_connection(asio::ip::tcp::socket&&, std::multimap<std::string, http::handler>*);

			// Starts all ops.
			void start();
		};
	}
}

#endif
