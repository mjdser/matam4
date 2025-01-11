

#include "Event.h"

#include "iostream"

Slime::Slime() : Encounter(Slime_CombatPower, Slime_Loot, Slime_Damage) {}

string Slime::getTypeString() const {
    return "Slime";
}

string Slime::getDescription() const {
    return getTypeString() + " (power " + std::to_string(getCombatPower()) +
           ", loot " + std::to_string(getLoot()) +
           ", damage " + std::to_string(getDamage()) + ")";
}
