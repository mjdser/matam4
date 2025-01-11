
#include "Event.h"

#include "iostream"

Snail::Snail() : Encounter(Snail_CombatPower, Snail_Loot, Snail_Damage) {}

string Snail::getTypeString() const {
    return "Snail";
}


