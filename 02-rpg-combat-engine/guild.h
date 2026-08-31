/*
assignment 1

Author: YI-LUN,WU
Student ID: 173968231
Email: ywu296@myseneca.ca

Date
2025/10/11
*/

#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H

#include <iostream>
#include <string>
#include "character.h"

namespace seneca
{
    class Guild
    {
    private:
        std::string m_name;
        Character **m_members;
        size_t m_memberCount;
        size_t m_capacity;

    public:
        Guild() : m_name(""), m_members(nullptr), m_memberCount(0), m_capacity(0) {}

        Guild(const char *name) : m_name(name), m_members(nullptr), m_memberCount(0), m_capacity(0) {}

        ~Guild()
        {
            delete[] m_members;
        }

        Guild(const Guild &other) : m_name(other.m_name), m_members(nullptr), m_memberCount(0), m_capacity(0)
        {
            if (other.m_memberCount > 0)
            {
                m_capacity = other.m_capacity;
                m_memberCount = other.m_memberCount;
                m_members = new Character *[m_capacity];
                for (size_t i = 0; i < m_memberCount; ++i)
                {
                    m_members[i] = other.m_members[i];
                }
            }
        }

        Guild &operator=(const Guild &other)
        {
            if (this != &other)
            {
                delete[] m_members;

                m_name = other.m_name;
                m_memberCount = other.m_memberCount;
                m_capacity = other.m_capacity;
                if (m_memberCount > 0)
                {
                    m_members = new Character *[m_capacity];
                    for (size_t i = 0; i < m_memberCount; ++i)
                    {
                        m_members[i] = other.m_members[i];
                    }
                }
                else
                {
                    m_members = nullptr;
                }
            }
            return *this;
        }

        Guild(Guild &&other) noexcept
            : m_name(other.m_name), m_members(other.m_members), m_memberCount(other.m_memberCount), m_capacity(other.m_capacity)
        {

            other.m_members = nullptr;
            other.m_memberCount = 0;
            other.m_capacity = 0;
            other.m_name.clear();
        }

        Guild &operator=(Guild &&other) noexcept
        {
            if (this != &other)
            {
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

        void addMember(Character *c)
        {
            bool found = false;
            for (size_t i = 0; i < m_memberCount && !found; ++i)
            {
                if (m_members[i] == c)
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
                m_members[m_memberCount] = c;
                m_memberCount++;

                c->setHealthMax(c->getHealthMax() + 300);
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

                m_members[found_idx]->setHealthMax(m_members[found_idx]->getHealthMax() - 300);

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
                std::cout << "No guild." << std::endl;
            }
            else
            {
                std::cout << "[Guild] " << m_name << std::endl;
                for (size_t i = 0; i < m_memberCount; ++i)
                {
                    std::cout << "    " << i + 1 << ": " << *m_members[i] << std::endl;
                }
            }
        }
    };
}

#endif