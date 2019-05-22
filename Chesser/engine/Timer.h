#ifndef TIMER_H
#define TIMER_H

#include "common.h"

namespace GEngine {

enum TimerResolution { milliseconds = 0, microseconds, nanoseconds };

class Timer {
   public:
	Timer(void);
	~Timer(void);

	void reset(void);
	void tick(void);

	long double GetDeltaTick(void);
	long double GetLastDeltaTick(void);
	long double GetTick(void);

	std::chrono::high_resolution_clock::time_point GetStart(void);
	std::chrono::high_resolution_clock::time_point GetCurrent(void);
	std::chrono::high_resolution_clock::time_point GetLastDeltaQueryTime(void);
	std::chrono::high_resolution_clock::duration GetLastDeltaCalc(void);
	std::chrono::high_resolution_clock::duration GetDeltaCalc(void);

	TimerResolution GetPrecision(void) { return this->_precision; }
	auto GetTicksPerSec(void) { return this->_ticks_per_sec; }

   private:
	std::chrono::high_resolution_clock clock;
	std::chrono::high_resolution_clock::time_point start;
	std::chrono::high_resolution_clock::time_point current;
	std::chrono::high_resolution_clock::time_point lastDeltaQueryTime;
	std::chrono::high_resolution_clock::duration lastDelta;
	long double _total_ticks;

	long double _ticks_per_sec;
	TimerResolution _precision;
};
}  // namespace GEngine

#endif