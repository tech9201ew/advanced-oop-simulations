

#ifndef SENECA_LOGGER_H
#define SENECA_LOGGER_H

#include <iostream>
#include "event.h"

namespace seneca 
{
	class Logger 
	{
		Event* m_events{ nullptr }; 
		size_t m_event_count{ 0 };  
		size_t m_capacity{ 0 };     

	public:
	
		Logger() = default; 
		void addEvent(const Event& event); 

		~Logger();

		Logger(const Logger& other) = delete;
		Logger& operator=(const Logger& other) = delete;

		Logger(Logger&& src);
		Logger& operator=(Logger&& src);

        friend std::ostream& operator<<(std::ostream& os, const Logger& logger);

	};

	std::ostream& operator<<(std::ostream& os, const Logger& logger);
}

#endif
