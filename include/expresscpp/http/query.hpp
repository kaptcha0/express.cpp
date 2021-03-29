#ifndef QUERY_HPP
#define QUERY_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <map>

namespace express {
	namespace http {
		struct query
		{
		private:
			std::map<std::string, std::string> queries_;
		public:
			query() = default;

			query(std::string raw)
			{
				for (std::string line; std::getline(std::stringstream(raw), line, '&');)
				{
					size_t separator = line.find_first_of('=');

					if (separator == std::string::npos)
						continue;

					std::string key = line.substr(0, separator);
					std::string value = line.substr(separator, line.length());

					queries_[key] = value;
				}
			}

			inline std::string& operator[](std::string key) const
			{
				return const_cast<std::string&>(queries_.find(key)->second);
			}
		};
	}
}


#endif
