

#include "Event.h"

#include "iostream"

Barlog::Barlog() : Encounter(Barlog_CombatPower, Barlog_Loot, Barlog_Damage) {}

string Barlog::getTypeString() const {
    return "Barlog";
}

string Barlog::getDescription() const {
    return getTypeString() + " (power " + std::to_string(getCombatPower()) +
           ", loot " + std::to_string(getLoot()) +
           ", damage " + std::to_string(getDamage()) + ")";
}

