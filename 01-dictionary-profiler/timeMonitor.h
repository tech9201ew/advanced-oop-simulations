

#ifndef SENECA_TIMEMONITOR_H
#define SENECA_TIMEMONITOR_H

#include <chrono>
#include <string>
#include "event.h"

namespace seneca
{
	class TimeMonitor
	{
		std::string m_eventName{};
		std::chrono::steady_clock::time_point m_startTime{};

	public:

		void startEvent(const char* name);
		Event stopEvent();
	};
}

#endif
