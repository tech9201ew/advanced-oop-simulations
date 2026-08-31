
#ifndef SENECA_EVENT_H
#define SENECA_EVENT_H

#include <iostream>
#include <chrono>
#include <string>
#include "settings.h"

namespace seneca
{
	class Event
	{
		std::string m_name{};
		std::chrono::nanoseconds m_duration{};

	public:
		Event() = default;
		Event(const char* name, const std::chrono::nanoseconds& duration); 

		std::string getName() const;
		std::chrono::nanoseconds getDuration() const;
	};

	std::ostream& operator<<(std::ostream& os, const Event& event);
}

#endif 
