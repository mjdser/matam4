
#include "Event.h"

#include "iostream"

Pack::Pack(const std::vector<std::shared_ptr<Encounter>>& events) :
        Encounter(0, 0, 0) {
    if (events.size() < 2) {
        throw std::invalid_argument("Pack must be at least 2");
    }

    this->events = events;


    for (const auto& event : events) {
        CombatPower += event->getCombatPower();
        Loot += event->getLoot();
        Damage += event->getDamage();
    }

    this->CombatPower = CombatPower;
    this->Loot = Loot;
    this->Damage = Damage;

}

string Pack::getTypeString() const {
    return "Pack";
}
