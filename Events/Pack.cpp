#include "Event.h"
#include "Utilities.h"
#include <iostream>

Pack::Pack(const std::vector<std::shared_ptr<Encounter>>& events)
        : Encounter(0, 0, 0), events(events) {

    if (events.size() < 2) {
        throw std::invalid_argument("Pack must be at least 2");
    }

    Refill();
}

void Pack::Refill(){
    CombatPower = 0;
    Loot = 0;
    Damage = 0;

    for (const auto& event : events) {
        CombatPower += event->getCombatPower();
        Loot += event->getLoot();
        Damage += event->getDamage();
    }
}

string Pack::getTypeString() const {
    return "Pack of " + std::to_string(events.size()) + " members";
}

std::string Pack::apply(Player& player) {
    bool canWin = player.getCombatPower() > CombatPower;

    for (const auto& event : events) {
        if (event->getTypeString() == "Balrog") {
            event->setBalrogCombatPower();
        }
    }

    Refill();

    if (canWin) {
        player.setCoins(player.getCoins() + Loot);
        if (player.getJob() == "Warrior") {
            player.setHealthPoints(player.getHealthPoints() - 10);
        }
        levelUp(player);
        return getEncounterWonMessage(player, Loot);
    } else {
        player.setHealthPoints(player.getHealthPoints() - Damage);
        return getEncounterLostMessage(player, Damage);
    }
}

string Pack::getDescription() const {
    return getTypeString() + " (power " + std::to_string(CombatPower) +
           ", loot " + std::to_string(Loot) +
           ", damage " + std::to_string(Damage) + ")";
}
