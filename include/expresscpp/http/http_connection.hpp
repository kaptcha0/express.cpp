#pragma once

#include "expresscpp/pch.hpp"
#include "expresscpp/commons/tcp_connection.hpp"

namespace express {
	namespace http {
		struct http_connection : public commons::tcp_connection {
			void start() override;
		};
	}
}