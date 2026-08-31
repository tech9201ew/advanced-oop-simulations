/* 
assignment 1 

Author: YI-LUN,WU
Student ID: 173968231
Email: ywu296@myseneca.ca

Date       
2025/09/25
*/


#include "timeMonitor.h"

namespace seneca
{
	void TimeMonitor::startEvent(const char* name)
	{
		m_eventName = name;
		m_startTime = std::chrono::steady_clock::now();
	}

	Event TimeMonitor::stopEvent()
	{
		auto endTime = std::chrono::steady_clock::now();
		auto duration = endTime - m_startTime;
		auto duration_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);

		return Event(m_eventName.c_str(), duration_ns);
	}
}