#include "Lt_time.h"

uint64_t Lt_time_GetMs()
{
	using namespace std::chrono;
	return duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
	).count();
}