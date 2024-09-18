#pragma once

#include <chrono>
#include <thread>

class Utilities
{
public:
	static void Wait(int miliseconds) { std::this_thread::sleep_for(std::chrono::milliseconds(miliseconds)); }
};