#include "ChiliTimer.h"

using namespace std::chrono;

ChiliTimer::ChiliTimer() noexcept
{
	last = high_resolution_clock::now();
}

float ChiliTimer::Mark() noexcept
{
	const auto old = last;
	last = high_resolution_clock::now();
	const duration<float> frameTime = last - old;
	return frameTime.count();
}

float ChiliTimer::Peek() const noexcept
{
	return duration<float>(high_resolution_clock::now() - last ).count();
}
