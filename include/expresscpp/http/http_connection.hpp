#pragma once

#include <functional>
#include "expresscpp/pch.hpp"
#include "expresscpp/http/http_io.hpp"
#include "expresscpp/http/raw_parsed.hpp"

// Max read buffer size
#define MAX_BUF_SIZE 1024

namespace express {
	namespace http {
		struct http_connection
		{
		private:
			// Raw request, after parsing
			raw_request req_;

			// Raw response, after parsing
			raw_response res_;

			// Socket to read/write from
			asio::ip::tcp::socket* socket_;

			char buffer_[MAX_BUF_SIZE];

			// Raw data from read
			std::string rawData_;

			// Handles reading data
			void readRequest();

			// Handles parsing requests
			void processRequest();

		public:
			http_connection(asio::ip::tcp::socket *);

			// Starts all ops.
			void start();
		};
	}
}