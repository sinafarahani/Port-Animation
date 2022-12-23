#pragma once
#include <chrono>

class ChiliTimer
{
public:
	ChiliTimer() noexcept;
	float Mark() noexcept;
	float Peek() const noexcept;
private:
	std::chrono::high_resolution_clock::time_point last;
};