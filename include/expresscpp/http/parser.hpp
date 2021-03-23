#pragma once;
#include "expresscpp/pch.hpp"

namespace express {
	namespace http {
		struct http_parser
		{
		private:
		public:
			static http_parser parse(std::string&);
		};
	}
}