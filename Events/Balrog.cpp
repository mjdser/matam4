

#include "Event.h"
#include "iostream"

Balrog::Balrog() : Encounter(Balrog_CombatPower, Balrog_Loot, Balrog_Damage) {}

string Balrog::getTypeString() const {
    return "Balrog";
}

string Balrog::getDescription() const {
    return getTypeString() + " (power " + std::to_string(getCombatPower()) +
           ", loot " + std::to_string(getLoot()) +
           ", damage " + std::to_string(getDamage()) + ")";
}