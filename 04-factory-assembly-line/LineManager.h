/*
assignment 4

Author: YI-LUN,WU
Student ID: 173968231
Email: ywu296@myseneca.ca

Date
2025/11/30
*/

#ifndef SENECA_LINEMANAGER_H
#define SENECA_LINEMANAGER_H

#include <vector>
#include <iostream>
#include <string>
#include "Workstation.h"

namespace seneca
{
    class LineManager
    {
        std::vector<Workstation *> m_activeLine;
        size_t m_cntCustomerOrder{0};
        Workstation *m_firstStation{nullptr};

    public:
        LineManager(const std::string &file, const std::vector<Workstation *> &stations);

        void reorderStations();

        bool run(std::ostream &os);

        void display(std::ostream &os) const;
    };
}

#endif
