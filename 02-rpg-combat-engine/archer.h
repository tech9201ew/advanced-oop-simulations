/*
assignment 1

Author: YI-LUN,WU
Student ID: 173968231
Email: ywu296@myseneca.ca

Date
2025/10/11
*/

#ifndef SENECA_ARCHER_H
#define SENECA_ARCHER_H

#include <iostream>
#include "characterTpl.h"
#include "weapons.h"
#include "health.h"

namespace seneca
{
    template <typename Weapon_t>
    class Archer : public CharacterTpl<seneca::SuperHealth>
    {
    private:
        int m_baseDefense;
        int m_baseAttack;
        Weapon_t m_weapon;

    public:
        Archer(const char *name, int healthMax, int baseAttack, int baseDefense, Weapon_t weapon)
            : CharacterTpl<seneca::SuperHealth>(name, healthMax), m_baseDefense(baseDefense), m_baseAttack(baseAttack), m_weapon(weapon) {}

        int getAttackAmnt() const override
        {
            return m_baseAttack * 1.3;
        }

        int getDefenseAmnt() const override
        {
            return m_baseDefense * 1.2;
        }

        Character *clone() const override
        {
            return new Archer<Weapon_t>(*this);
        }

        void attack(Character *enemy) override
        {
            std::cout << this->getName() << " is attacking " << enemy->getName() << "." << std::endl;

            int damage = getAttackAmnt();

            std::cout << "    Archer deals " << damage << " ranged damage!" << std::endl;

            enemy->takeDamage(damage);
        }

        void takeDamage(int dmg) override
        {
            std::cout << this->getName() << " is attacked for " << dmg << " damage." << std::endl;
            std::cout << "    Archer has a defense of " << getDefenseAmnt() << ". Reducing damage received." << std::endl;

            int reducedDmg = dmg - getDefenseAmnt();
            if (reducedDmg < 0)
            {
                reducedDmg = 0;
            }

            CharacterTpl<seneca::SuperHealth>::takeDamage(reducedDmg);
        }
    };
}

#endif