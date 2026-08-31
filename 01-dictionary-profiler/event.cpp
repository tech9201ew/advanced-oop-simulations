
#include <iomanip> 
#include "event.h"

namespace seneca
{

	Event::Event(const char* name, const std::chrono::nanoseconds& duration) : m_name(name), m_duration(duration) {}

	std::string Event::getName() const {
		return m_name;
	}
	std::chrono::nanoseconds Event::getDuration() const {
		return m_duration;
	}

	std::ostream& operator<<(std::ostream& os, const Event& event)
	{
		static size_t counter = 0;
		++counter;

		long long duration_val = 0;
		int width = 0;

		if (g_settings.m_time_units == "seconds") {
			duration_val = std::chrono::duration_cast<std::chrono::seconds>(event.getDuration()).count();
			width = 2;
		}
		else if (g_settings.m_time_units == "milliseconds") {
			duration_val = std::chrono::duration_cast<std::chrono::milliseconds>(event.getDuration()).count();
			width = 5;
		}
		else if (g_settings.m_time_units == "microseconds") {
			duration_val = std::chrono::duration_cast<std::chrono::microseconds>(event.getDuration()).count();
			width = 8;
		}
		else { // default to nanoseconds
			duration_val = event.getDuration().count();
			width = 11;
		}

		
		os << std::right << std::setw(2) << counter << ": "
		   << std::right << std::setw(40) << event.getName() << " -> "
		   << std::right << std::setw(width) << duration_val << " " << g_settings.m_time_units;

		return os;
	}
}
