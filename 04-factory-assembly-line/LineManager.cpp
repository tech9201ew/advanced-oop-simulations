/*
assignment 4

Author: YI-LUN,WU
Student ID: 173968231
Email: ywu296@myseneca.ca

Date
2025/11/30
*/

#include "LineManager.h"
#include "Utilities.h"
#include <fstream>
#include <algorithm>
#include <string>

namespace seneca
{

    LineManager::LineManager(const std::string &file, const std::vector<Workstation *> &stations)
    {
        Utilities util;
        std::ifstream ifs(file);

        if (!ifs)
        {
            throw std::string("ERROR: Unable to open file.");
        }

        std::string record;
        while (std::getline(ifs, record))
        {
            size_t next_pos = 0;
            bool more = true;

            std::string currentName = util.extractToken(record, next_pos, more);

            auto currIter = std::find_if(stations.begin(), stations.end(), [&](Workstation *ws)
                                         { return ws->getItemName() == currentName; });

            if (currIter != stations.end())
            {
                Workstation *currStation = *currIter;
                m_activeLine.push_back(currStation);

                if (more)
                {
                    std::string nextName = util.extractToken(record, next_pos, more);

                    auto nextIter = std::find_if(stations.begin(), stations.end(), [&](Workstation *ws)
                                                 { return ws->getItemName() == nextName; });

                    if (nextIter != stations.end())
                    {
                        currStation->setNextStation(*nextIter);
                    }
                }
            }
        }
        ifs.close();

        // ref ai
        auto firstIter = std::find_if(m_activeLine.begin(), m_activeLine.end(), [&](Workstation *potentialFirst)
                                      { return std::none_of(m_activeLine.begin(), m_activeLine.end(), [&](Workstation *other)
                                                            { return other->getNextStation() == potentialFirst; }); });

        if (firstIter != m_activeLine.end())
        {
            m_firstStation = *firstIter;
        }

        m_cntCustomerOrder = g_pending.size();
    }

    // ref ai
    void LineManager::reorderStations()
    {
        std::vector<Workstation *> sortedLine;
        Workstation *curr = m_firstStation;

        while (curr != nullptr)
        {
            sortedLine.push_back(curr);
            curr = curr->getNextStation();
        }

        m_activeLine = sortedLine;
    }

    bool LineManager::run(std::ostream &os)
    {
        static size_t count = 1;
        os << "Line Manager Iteration: " << count++ << std::endl;

        if (!g_pending.empty())
        {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }

        // ref ai
        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation *ws)
                      { ws->fill(os); });

        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation *ws)
                      { ws->attemptToMoveOrder(); });

        return (g_completed.size() + g_incomplete.size()) == m_cntCustomerOrder;
    }

    void LineManager::display(std::ostream &os) const
    {
        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation *ws)
                      { ws->display(os); });
    }
}