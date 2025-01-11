
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
    return "Pack of" + std::to_string(events.size()) + "members";
}



string Pack::apply(Player &player) {

    //check if playaer can win with this . damage

    bool canWin = false;

    if (player.getCombatPower() >= CombatPower){
        canWin = true;
    }

        for (const auto &event: events) {
        event->apply(player);
    }

    // Recalculate CombatPower, Loot, and Damage after applying all events
    CombatPower = 0;
    Loot = 0;
    Damage = 0;
    for (const auto &event: events) {
        CombatPower += event->getCombatPower();
        Loot += event->getLoot();
        Damage += event->getDamage();
    }

        return to_string(canWin);
}

string Pack::getDescription() const {
    string description = getTypeString() + " (power " + std::to_string(getCombatPower()) +
                         ", loot " + std::to_string(getLoot()) +
                         ", damage " + std::to_string(getDamage()) + ")";

    return description;
}