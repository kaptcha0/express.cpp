#pragma once

#include <string>
#include <map>

namespace express {
	namespace http {
		struct method
		{
		public:
			enum value : uint8_t
			{
				OPTIONS,
				GET,
				HEAD,
				POST,
				PUT,
				_DELETE,
				TRACE,
				CONNECT
			};

			method() = default;

			constexpr method(value method) : method_(method) { }

			inline operator std::string()
			{
				switch(method_)
				{
					case OPTIONS:
						return "OPTIONS";
					case GET:
						return "GET";
					case HEAD:
						return "HEAD";
					case POST:
						return "POST";
					case PUT:
						return "PUT";
					case _DELETE:
						return "DELETE";
					case TRACE:
						return "TRACE";
					case CONNECT:
						return "CONNECT";
					default:
						return "INVALID REQUEST METHOD";
				};
			}

		private:
			value method_;
		};

		struct raw_request
		{
		public:
			std::string reqLine;
			std::multimap<std::string, std::string> headers;
			std::string body;
		};

		struct raw_response
		{
		public:
			std::string resLine;
			std::multimap<std::string, std::string> headers;
			std::string body;
		};
	}
}