

#include "Event.h"

#include "iostream"

Slime::Slime() : Encounter(Slime_CombatPower, Slime_Loot, Slime_Damage) {}

string Slime::getTypeString() const {
    return "Slime";
}
