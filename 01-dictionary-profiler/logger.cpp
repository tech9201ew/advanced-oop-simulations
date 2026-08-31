

#include <utility> 
#include "logger.h"

namespace seneca
{
	void Logger::addEvent(const Event& event) {

		if (m_event_count >= m_capacity) {

			size_t new_capacity = (m_capacity == 0) ? 1 : m_capacity * 2;

			Event* new_events = new Event[new_capacity];

			for (size_t i = 0; i < m_event_count; ++i) {
				new_events[i] = m_events[i];
			}

			delete[] m_events;

			m_events = new_events;
			m_capacity = new_capacity;
		}

		m_events[m_event_count] = event;
		m_event_count++;
	}

	Logger::~Logger() {

		delete[] m_events;
	}

	Logger::Logger(Logger&& src) {

		m_events = src.m_events;
		m_event_count = src.m_event_count;
		m_capacity = src.m_capacity;

		src.m_events = nullptr;
		src.m_event_count = 0;
		src.m_capacity = 0;
	}

	Logger& Logger::operator=(Logger&& src) {

		if (this != &src) {

			delete[] m_events;

			m_events = src.m_events;
			m_event_count = src.m_event_count;
			m_capacity = src.m_capacity;

			src.m_events = nullptr;
			src.m_event_count = 0;
			src.m_capacity = 0;
		}
		return *this;
	}

	std::ostream& operator<<(std::ostream& os, const Logger& logger) {

		for (size_t i = 0; i < logger.m_event_count; ++i) {
			os << logger.m_events[i] << std::endl;
		}
		return os;
	}
}
