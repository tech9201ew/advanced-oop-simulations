/*
assignment 1

Author: YI-LUN,WU
Student ID: 173968231
Email: ywu296@myseneca.ca

Date
2025/10/11
*/

#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H

#include <iostream>
#include <string>
#include "character.h"

namespace seneca
{
    class Team
    {
    private:
        std::string m_name;
        Character **m_members;
        size_t m_memberCount;
        size_t m_capacity;

    public:
        Team() : m_name(""), m_members(nullptr), m_memberCount(0), m_capacity(0) {}

        Team(const char *name) : m_name(name), m_members(nullptr), m_memberCount(0), m_capacity(0) {}

        ~Team()
        {
            for (size_t i = 0; i < m_memberCount; ++i)
            {
                delete m_members[i];
            }
            delete[] m_members;
        }
        // ref ai

        Team(const Team &other) : m_name(other.m_name), m_members(nullptr), m_memberCount(0), m_capacity(0)
        {
            if (other.m_memberCount > 0)
            {
                m_capacity = other.m_capacity;
                m_memberCount = other.m_memberCount;
                m_members = new Character *[m_capacity];
                for (size_t i = 0; i < m_memberCount; ++i)
                {
                    m_members[i] = other.m_members[i]->clone(); // 使用clone()來複製每個角色
                }
            }
        }

        Team &operator=(const Team &other)
        {
            if (this != &other)
            {

                for (size_t i = 0; i < m_memberCount; ++i)
                {
                    delete m_members[i];
                }
                delete[] m_members;

                m_name = other.m_name;
                m_memberCount = other.m_memberCount;
                m_capacity = other.m_capacity;
                if (m_memberCount > 0)
                {
                    m_members = new Character *[m_capacity];
                    for (size_t i = 0; i < m_memberCount; ++i)
                    {
                        m_members[i] = other.m_members[i]->clone();
                    }
                }
                else
                {
                    m_members = nullptr;
                }
            }
            return *this;
        }
        // ref ai

        Team(Team &&other) noexcept
            : m_name(other.m_name), m_members(other.m_members), m_memberCount(other.m_memberCount), m_capacity(other.m_capacity)
        {

            other.m_members = nullptr;
            other.m_memberCount = 0;
            other.m_capacity = 0;
            other.m_name.clear();
        }

        Team &operator=(Team &&other) noexcept
        {
            if (this != &other)
            {

                for (size_t i = 0; i < m_memberCount; ++i)
                {
                    delete m_members[i];
                }
                delete[] m_members;

                m_name = other.m_name;
                m_members = other.m_members;
                m_memberCount = other.m_memberCount;
                m_capacity = other.m_capacity;

                other.m_members = nullptr;
                other.m_memberCount = 0;
                other.m_capacity = 0;
                other.m_name.clear();
            }
            return *this;
        }
        // ref ai

        void addMember(const Character *c)
        {
            bool found = false;
            for (size_t i = 0; i < m_memberCount && !found; ++i)
            {
                if (m_members[i]->getName() == c->getName())
                {
                    found = true;
                }
            }

            if (!found)
            {
                if (m_memberCount >= m_capacity)
                {

                    int newCapacity = (m_capacity == 0) ? 4 : m_capacity * 2;
                    Character **newMembers = new Character *[newCapacity];
                    for (size_t i = 0; i < m_memberCount; ++i)
                    {
                        newMembers[i] = m_members[i];
                    }
                    delete[] m_members;
                    m_members = newMembers;
                    m_capacity = newCapacity;
                }
                m_members[m_memberCount] = c->clone();
                m_memberCount++;
            }
        }

        void removeMember(const std::string &name)
        {
            int found_idx = -1;
            for (size_t i = 0; i < m_memberCount && found_idx == -1; ++i)
            {
                if (m_members[i]->getName() == name)
                {
                    found_idx = i;
                }
            }

            if (found_idx != -1)
            {
                delete m_members[found_idx];

                for (size_t i = found_idx; i < m_memberCount - 1; ++i)
                {
                    m_members[i] = m_members[i + 1];
                }
                m_memberCount--;
            }
        }

        Character *operator[](size_t idx) const
        {
            if (idx < m_memberCount)
            {
                return m_members[idx];
            }
            return nullptr;
        }

        void showMembers() const
        {
            if (m_name.empty())
            {
                std::cout << "No team." << std::endl;
            }
            else
            {
                std::cout << "[Team] " << m_name << std::endl;
                for (size_t i = 0; i < m_memberCount; ++i)
                {
                    std::cout << "    " << i + 1 << ": " << *m_members[i] << std::endl;
                }
            }
        }
    };
}

#endif