/*
assignment 4

Author: YI-LUN,WU
Student ID: 173968231
Email: ywu296@myseneca.ca

Date
2025/11/30
*/

#include "Workstation.h"
#include <iostream>

namespace seneca
{

    std::deque<CustomerOrder> g_pending;
    std::deque<CustomerOrder> g_completed;
    std::deque<CustomerOrder> g_incomplete;

    Workstation::Workstation(const std::string &str) : Station(str) {}

    void Workstation::fill(std::ostream &os)
    {
        if (!m_orders.empty())
        {

            m_orders.front().fillItem(*this, os);
        }
    }

    bool Workstation::attemptToMoveOrder()
    {
        bool moved = false;
        if (!m_orders.empty())
        {

            CustomerOrder &order = m_orders.front();

            if (order.isItemFilled(getItemName()) || getQuantity() <= 0)
            {

                if (m_pNextStation)
                {
                    *m_pNextStation += std::move(order);
                }
                else
                {

                    if (order.isOrderFilled())
                    {
                        g_completed.push_back(std::move(order));
                    }
                    else
                    {
                        g_incomplete.push_back(std::move(order));
                    }
                }

                m_orders.pop_front();
                moved = true;
            }
        }
        return moved;
    }

    void Workstation::setNextStation(Workstation *station)
    {
        m_pNextStation = station;
    }

    Workstation *Workstation::getNextStation() const
    {
        return m_pNextStation;
    }

    void Workstation::display(std::ostream &os) const
    {
        if (m_pNextStation)
        {
            os << getItemName() << " --> " << m_pNextStation->getItemName() << std::endl;
        }
        else
        {
            os << getItemName() << " --> End of Line" << std::endl;
        }
    }

    Workstation &Workstation::operator+=(CustomerOrder &&newOrder)
    {

        m_orders.push_back(std::move(newOrder));
        return *this;
    }
}