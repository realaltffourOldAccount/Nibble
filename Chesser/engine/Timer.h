/**
 * @file Timer.h
 * @author Ayham Mamoun (ayhamaboulafadl@gmail.com)
 * @brief Contains the main timer of the app. The thing that ticks.
 * @version 0.1
 * @date 2019-05-31
 *
 */
#ifndef TIMER_H
#define TIMER_H

#include "common.h"

namespace GEngine {

/**
 * @brief Holds information of the resolution of the timer.
 *
 */
enum TimerResolution { milliseconds = 0, microseconds, nanoseconds };

/**
 * @brief The Timer of the app.
 *
 */
class Timer {
   public:
	Timer(void);
	~Timer(void);

	/**
	 * @brief Resets the timer.
	 *
	 */
	void reset(void);
	/**
	 * @brief Updates the timer's current time.
	 *
	 */
	void tick(void);

	/**
	 * @brief Get the Delta Tick object.
	 *
	 * @return long double
	 */
	long double GetDeltaTick(void);
	/**
	 * @brief Get the Last Delta Tick object.
	 *
	 * @return long double
	 */
	long double GetLastDeltaTick(void);
	/**
	 * @brief Get the Tick object.
	 *
	 * @return long double
	 */
	long double GetTick(void);

	/**
	 * @brief Get the Start object.
	 *
	 * @return std::chrono::high_resolution_clock::time_point
	 */
	std::chrono::high_resolution_clock::time_point GetStart(void);
	/**
	 * @brief Get the Current object.
	 *
	 * @return std::chrono::high_resolution_clock::time_point
	 */
	std::chrono::high_resolution_clock::time_point GetCurrent(void);
	/**
	 * @brief Get the Last Delta Query Time object.
	 *
	 * @return std::chrono::high_resolution_clock::time_point
	 */
	std::chrono::high_resolution_clock::time_point GetLastDeltaQueryTime(void);
	/**
	 * @brief Get the Last Delta Calc object.
	 *
	 * @return std::chrono::high_resolution_clock::duration
	 */
	std::chrono::high_resolution_clock::duration GetLastDeltaCalc(void);
	/**
	 * @brief Get the Delta Calc object.
	 *
	 * @return std::chrono::high_resolution_clock::duration
	 */
	std::chrono::high_resolution_clock::duration GetDeltaCalc(void);

	/**
	 * @brief Get the Precision object.
	 *
	 * @return TimerResolution
	 */
	TimerResolution GetPrecision(void) { return this->_precision; }
	/**
	 * @brief Get the Ticks Per Sec object.
	 *
	 * @return auto
	 */
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