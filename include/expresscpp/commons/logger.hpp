#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>

namespace express {
	namespace commons {
		enum class LogLevel
		{
			ALL,
			DEBUG,
			WARNING,
			ERROR,
			NONE
		};

		template <std::ostream& stream>
		class Logger
		{
		public:
			LogLevel logLevel;

			Logger(LogLevel log)
				:logLevel(log)
			{	}

			template <typename T>
			void log(LogLevel level, T data)
			{
				stream << data << std::endl;;
			}
		};
	}
}

#endif
