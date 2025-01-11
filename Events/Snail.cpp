#include "Event.h"      // Include the declaration of Barlog (defined in Event.h)


Snail::Snail() : Encounter(Snail_CombatPower, Snail_Loot, Snail_Damage) {}

string Snail::getTypeString() const {
    return "Snail";
}

string Snail::getDescription() const {
    return getTypeString() + " (power " + std::to_string(getCombatPower()) +
           ", loot " + std::to_string(getLoot()) +
           ", damage " + std::to_string(getDamage()) + ")";
}
