#pragma once
#include <chrono>

class MyTimer
{
private:
	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;
public:
	MyTimer() {}
	~MyTimer() {}

	void start()
	{
		begin = std::chrono::steady_clock::now();
	}
	long long stop()
	{
		end = std::chrono::steady_clock::now();
		return std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
	}
};