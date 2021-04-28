#ifndef COOKIES_HPP
#define COOKIES_HPP

#include <map>
#include "expresscpp/commons/pch.hpp"

namespace express {
	namespace http {
		struct cookies
		{
		private:
			std::map<const char*, std::string> cookies_;
		public:
			std::string inline toString() const
			{
				std::string c;

				for (auto cookie : cookies_)
				{
					c += "Set-Cookie: " + std::string(cookie.first) + "=" + cookie.second;
				}

				return c;
			}

			inline std::string& operator[](const char* key)
			{
				return cookies_[key];
			}

			explicit inline operator std::string() const
			{
				return toString();
			}
		};
	}
}


#endif
