#pragma once

#include <functional>
#include "expresscpp/pch.hpp"

// Max read buffer size
#define MAX_BUF_SIZE 1024

namespace express {
	namespace commons {
		struct tcp_connection : public std::enable_shared_from_this<tcp_connection>
		{
		protected:
			// Socket to read/write from
			asio::ip::tcp::socket* socket_;

			char buffer_[MAX_BUF_SIZE];

			// Raw data from read
			std::string rawData_;

			// Handles reading data
			virtual void readRequest();

		public:
			tcp_connection(asio::ip::tcp::socket*);

			// Start all operations
			virtual void start();
		};
	}
}

