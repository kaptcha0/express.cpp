#ifndef QUERY_HPP
#define QUERY_HPP

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
				raw += "&";
				size_t begin = 0;
				size_t end = raw.find('&');

				while (end != std::string::npos)
				{
					std::string query = raw.substr(begin, end);

					if (query.find('&') != std::string::npos)
						query.erase(query.find("&"), 1);

					size_t separator = query.find("=");
					
					if (separator == std::string::npos)
						continue;

					std::string key = query.substr(0, separator);
					std::string value = query.substr(separator + 1, query.length());

					queries_[key] = value;
					
					if (end + 1 == raw.length())
						break;

					begin = end + 1;
					end = raw.find('&', begin);
				}

				/*while (end != std::string::npos)
				{
					std::string line = raw.substr(prev, end);

					if (line.compare("") == 0)
						break;

					size_t separator = line.find_first_of('=');

					if (separator == std::string::npos)
						continue;

					std::string key = line.substr(0, separator);
					std::string value = line.substr(separator + 1, line.length());

					queries_[key] = value;
					prev = end + 1;
					end = raw.find('&', prev) == std::string::npos ? raw.length() : raw.find('&', prev);
				}*/
			}

			bool exists(const char* key) const
			{
				return queries_.find(key) != queries_.end();
			}

			inline std::string& operator[](std::string key)
			{
				return queries_.find(key)->second;
			}
		};
	}
}


#endif
