#include "Timer.h"

GEngine::Timer::Timer(void) {
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
	this->start = clock.now();
	this->current = start;
	this->lastDeltaQueryTime = start;
	this->lastDelta = std::chrono::seconds(0);
}
void GEngine::Timer::tick(void) { current = clock.now(); }

long double GEngine::Timer::GetDeltaTick(void) {
	auto delta = clock.now() - lastDeltaQueryTime;
	this->lastDeltaQueryTime = clock.now();
	this->lastDelta = delta;
	return delta.count();
}
long double GEngine::Timer::GetLastDeltaTick(void) {
	return this->lastDelta.count();
}
long double GEngine::Timer::GetTick(void) {
	return (this->current - this->start).count();
}

std::chrono::high_resolution_clock::time_point GEngine::Timer::GetStart(void) {
	return start;
}
std::chrono::high_resolution_clock::time_point GEngine::Timer::GetCurrent(
	void) {
	return current;
}
std::chrono::high_resolution_clock::time_point
GEngine::Timer::GetLastDeltaQueryTime(void) {
	return this->lastDeltaQueryTime;
}
std::chrono::high_resolution_clock::duration GEngine::Timer::GetLastDeltaCalc(
	void) {
	return this->lastDelta;
}
std::chrono::high_resolution_clock::duration GEngine::Timer::GetDeltaCalc(
	void) {
	auto delta = clock.now() - lastDeltaQueryTime;
	this->lastDeltaQueryTime = clock.now();
	this->lastDelta = delta;
	return delta;
}