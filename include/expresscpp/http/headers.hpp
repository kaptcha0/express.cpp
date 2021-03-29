#ifndef HEADERS_HPP
#define HEADERS_HPP

#include <map>
#include <string>
#include <vector>

namespace express {
	namespace http {
		struct headers
		{
		private:
			std::multimap<std::string, std::string> headers_;
		public:

			inline void set(std::string key, std::string value)
			{
				headers_.insert(std::make_pair(key, value));
			}

			inline std::string toString() const
			{
				std::string headers;

				for (auto header : headers_)
					headers += header.first + ": " + header.second + "\r\n";

				return headers;
			}

			inline std::vector<std::string> operator[](std::string key) const
			{
				std::vector<std::string> valid;
				auto range = headers_.equal_range(key);

				for (auto it = range.first; it != range.second; ++it)
					valid.push_back(it->second);

				return valid;
			}
		
			explicit inline operator std::string() const
			{
				return toString();
			}
		};
	}
}

#endif