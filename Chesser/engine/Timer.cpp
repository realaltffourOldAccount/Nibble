#include "Timer.h"

GEngine::Timer::Timer(void) {
	// Sets the resolution of the timer.
	this->_ticks_per_sec = std::chrono::high_resolution_clock::period::den;
	if (_ticks_per_sec == 1000)
		this->_precision = TimerResolution::milliseconds;
	else if (_ticks_per_sec == 1000000)
		this->_precision = TimerResolution::microseconds;
	else if (_ticks_per_sec == 1000000000)
		this->_precision = TimerResolution::nanoseconds;
}
GEngine::Timer::~Timer(void) {}

void GEngine::Timer::reset(void) {
	// Resets the timer.
	this->start = clock.now();
	this->current = start;
	this->lastDeltaQueryTime = start;
	this->lastDelta = std::chrono::seconds(0);
}
void GEngine::Timer::tick(void) { current = clock.now(); }

long double GEngine::Timer::GetDeltaTick(void) {
	// Calculates the delta time from the last time of the calling of this
	// function.
	auto delta = clock.now() - lastDeltaQueryTime;
	this->lastDeltaQueryTime = clock.now();
	this->lastDelta = delta;
	return delta.count();
}
long double GEngine::Timer::GetLastDeltaTick(void) {
	// Returns the last delta calculated
	return this->lastDelta.count();
}
long double GEngine::Timer::GetTick(void) {
	// Returns the total ticks from the last reset of the timer.
	return (this->current - this->start).count();
}

std::chrono::high_resolution_clock::time_point GEngine::Timer::GetStart(void) {
	// Returns the start time of the timer.
	return start;
}
std::chrono::high_resolution_clock::time_point GEngine::Timer::GetCurrent(
	void) {
	// Returns the current tick time of the timer.
	return current;
}
std::chrono::high_resolution_clock::time_point
GEngine::Timer::GetLastDeltaQueryTime(void) {
	// Returns the last delta tick query time.
	return this->lastDeltaQueryTime;
}
std::chrono::high_resolution_clock::duration GEngine::Timer::GetLastDeltaCalc(
	void) {
	// Returns the last delat calculated.
	return this->lastDelta;
}
std::chrono::high_resolution_clock::duration GEngine::Timer::GetDeltaCalc(
	void) {
	// Calculates the delta time from the last time of the calling of this
	// function.
	auto delta = clock.now() - lastDeltaQueryTime;
	this->lastDeltaQueryTime = clock.now();
	this->lastDelta = delta;
	return delta;
}