#include "expresscpp/http/http_connection.hpp"

namespace express {
	namespace http {
		void http_connection::start() {
			this->readRequest();
			
		}
	}
}