#ifndef UTILS_HPP
#define UTILS_HPP

#if defined(_DEBUG) || !defined(NDEBUG)
#include <iostream>
#endif
#include <chrono>

namespace express {
	namespace commons {
#if defined(_DEBUG) || !defined(NDEBUG)
		class Timer
		{
		private:
			std::chrono::time_point<std::chrono::high_resolution_clock> startTimePoint_;

			const char* name_ = "";

			bool print_ = true;
			bool stopped_ = false;

		public:
			Timer()
			{
				startTimePoint_ = std::chrono::high_resolution_clock::now();
			}

			Timer(const char* name, bool enableTimeLog = true)
				:name_(name), print_(enableTimeLog)
			{
				startTimePoint_ = std::chrono::high_resolution_clock::now();
			}

			~Timer()
			{
				if (!stopped_)
					Stop();
			}

			// Returns milliseconds
			double Stop()
			{
				auto endTimepoint = std::chrono::high_resolution_clock::now();

				auto start = std::chrono::time_point_cast<std::chrono::microseconds>(startTimePoint_).time_since_epoch();
				auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch();

				auto duration = end - start;
				double ms = duration.count() * 0.001;

				if (print_)
					std::cout << "\n[DEBUG]: " << name_ << " took "  << duration.count() << "us (" << ms << "ms)\n\n";

				stopped_ = true;

				return ms;
			}
		};
#else
		struct Timer
		{
		public:
			Timer() = default;

			Timer(const char* name, bool print=false)
			{	}

			float Stop() {};
		};
#endif
	}
}

#endif