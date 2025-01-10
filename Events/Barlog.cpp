

#include "Event.h"

#include "iostream"

Barlog::Barlog() : Encounter(Barlog_CombatPower, Barlog_Loot, Barlog_Damage) {}

string Barlog::getTypeString() const {
    return "Barlog";
}
