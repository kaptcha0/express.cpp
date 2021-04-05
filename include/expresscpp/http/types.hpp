#ifndef TYPES_HPP
#define TYPES_HPP

#include <functional>
#include "expresscpp/http/request.hpp"
#include "expresscpp/http/response.hpp"
#include "expresscpp/http/raw_parsed.hpp"

namespace express {
	namespace http {
		typedef std::function<void(request&, response&)> RequestHandler;

		struct handler
		{
		public:
			http::method method;
			RequestHandler handle;
		};
	}
}




#endif