

#ifndef SENECA_BARBARIAN_H
#define SENECA_BARBARIAN_H

#include <iostream>
#include "characterTpl.h"
#include "weapons.h"
#include "abilities.h"

namespace seneca
{
    template <typename T, typename Ability_t, typename Weapon_t>
    class Barbarian : public CharacterTpl<T>
    {
    private:
        int m_baseDefense;
        int m_baseAttack;
        Ability_t m_ability;
        Weapon_t m_weapon[2];

    public:
        Barbarian(const char *name, int healthMax, int baseAttack, int baseDefense, Weapon_t primaryWeapon, Weapon_t secondaryWeapon)
            : CharacterTpl<T>(name, healthMax), m_baseDefense(baseDefense), m_baseAttack(baseAttack), m_ability(), m_weapon{primaryWeapon, secondaryWeapon} {}

        int getAttackAmnt() const override
        {
            return m_baseAttack + (static_cast<double>(m_weapon[0]) / 2) + (static_cast<double>(m_weapon[1]) / 2);
        }
   

        int getDefenseAmnt() const override
        {
            return m_baseDefense;
        }

        Character *clone() const override
        {
            return new Barbarian<T, Ability_t, Weapon_t>(*this);
        }
      

        void attack(Character *enemy) override
        {
            std::cout << this->getName() << " is attacking " << enemy->getName() << "." << std::endl;

            m_ability.useAbility(this);

            int damage = getAttackAmnt();
            m_ability.transformDamageDealt(damage);

            std::cout << "    Barbarian deals " << damage << " melee damage!" << std::endl;

            enemy->takeDamage(damage);
        }

        void takeDamage(int dmg) override
        {
            std::cout << this->getName() << " is attacked for " << dmg << " damage." << std::endl;
            std::cout << "    Barbarian has a defense of " << getDefenseAmnt() << ". Reducing damage received." << std::endl;

            int reducedDmg = dmg - getDefenseAmnt();
            if (reducedDmg < 0)
            {
                reducedDmg = 0;
            }

            m_ability.transformDamageReceived(reducedDmg);

            CharacterTpl<T>::takeDamage(reducedDmg);
        }
    };
}

#endif
