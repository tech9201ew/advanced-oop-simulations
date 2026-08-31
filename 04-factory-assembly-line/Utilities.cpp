/*
assignment 4

Author: YI-LUN,WU
Student ID: 173968231
Email: ywu296@myseneca.ca

Date
2025/11/30
*/

#include "Utilities.h"
#include <iostream>
#include <string>
#include <algorithm>

namespace seneca
{

    char Utilities::m_delimiter = ' ';

    void Utilities::setFieldWidth(size_t newWidth)
    {
        m_widthField = newWidth;
    }

    size_t Utilities::getFieldWidth() const
    {
        return m_widthField;
    }

    std::string Utilities::extractToken(const std::string &str, size_t &next_pos, bool &more)
    {

        if (next_pos >= str.length())
        {
            more = false;
            return "";
        }

        // ref ai
        std::string token = "";
        size_t end_pos = str.find(m_delimiter, next_pos);

        if (end_pos == next_pos)
        {
            more = false;
            throw std::string("ERROR: No token.");
        }

        if (end_pos != std::string::npos)
        {
            token = str.substr(next_pos, end_pos - next_pos);
            next_pos = end_pos + 1;
            more = true;
        }
        else
        {

            token = str.substr(next_pos);
            next_pos = str.length();
            more = false;
        }

        size_t start = token.find_first_not_of(" \t");
        if (start != std::string::npos)
        {
            token = token.substr(start);
        }

        size_t end = token.find_last_not_of(" \t");
        if (end != std::string::npos)
        {
            token = token.substr(0, end + 1);
        }

        if (token.length() > m_widthField)
        {
            m_widthField = token.length();
        }

        return token;
    }

    void Utilities::setDelimiter(char newDelimiter)
    {
        m_delimiter = newDelimiter;
    }

    char Utilities::getDelimiter()
    {
        return m_delimiter;
    }
}