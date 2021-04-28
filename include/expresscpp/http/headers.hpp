#ifndef HEADERS_HPP
#define HEADERS_HPP

#include <map>
#include <string>
#include <vector>

namespace express {
	namespace http {
		struct headers
		{
		protected:
			std::map<std::string, std::vector<std::string>> headers_;
		public:

			inline void set(std::string key, std::string value)
			{
				headers_[key].push_back(value);
			}

			inline std::string toString() const
			{
				std::string headers;

				for (auto header : headers_)
					for (auto value : header.second)
						headers += header.first + ": " + value + "\r\n";

				return headers;
			}

			inline std::vector<std::string>& operator[](std::string key)
			{
				return headers_[key];
			}
		
			explicit inline operator std::string() const
			{
				return toString();
			}
		};
	}
}

#endif