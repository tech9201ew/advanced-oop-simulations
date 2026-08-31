

#include "Station.h"
#include "Utilities.h"
#include <iomanip>
#include <string>

namespace seneca
{
    
    size_t Station::m_widthField = 0;
    int Station::id_generator = 0;

    Station::Station(const std::string &str)
    {
        Utilities util;
        size_t next_pos = 0;
        bool more = true;

        m_id = ++id_generator;

        try
        {
            if (more)
            {
                m_itemName = util.extractToken(str, next_pos, more);
            }

            if (more)
            {
                m_serialNumber = std::stoul(util.extractToken(str, next_pos, more));
            }

            if (more)
            {
                m_quantity = std::stoul(util.extractToken(str, next_pos, more));
            }

            if (m_widthField < util.getFieldWidth())
            {
                m_widthField = util.getFieldWidth();
            }

            if (more)
            {
                m_description = util.extractToken(str, next_pos, more);
            }
        }
        catch (std::string &err)
        {
            throw err;
        }
    }

    const std::string &Station::getItemName() const
    {
        return m_itemName;
    }

    size_t Station::getNextSerialNumber()
    {
        return m_serialNumber++;
    }

    size_t Station::getQuantity() const
    {
        return m_quantity;
    }

    void Station::updateQuantity()
    {
        if (m_quantity > 0)
        {
            m_quantity--;
        }
    }

    void Station::display(std::ostream &os, bool full) const
    {
        os << std::setw(3) << std::setfill('0') << std::right << m_id << " | ";

        os << std::setw(m_widthField) << std::setfill(' ') << std::left << m_itemName << " | ";

        os << std::setw(6) << std::setfill('0') << std::right << m_serialNumber << " | ";

        if (full)
        {

            os << std::setw(4) << std::setfill(' ') << std::right << m_quantity << " | ";

            os << m_description;
        }

        os << std::endl;
    }
}
