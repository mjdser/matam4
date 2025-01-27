

#include "Event.h"
#include "Utilities.h"





std::string Encounter::apply(Player& player) {
    int powerBeforeAdjustment = getCombatPower();

    if (getTypeString() == "Balrog") {
        setBalrogCombatPower();
    }

    int healthAdjustment = getDamage();

    if (player.getCombatPower() > powerBeforeAdjustment) {

        player.setCoins(player.getCoins() + getLoot());

        if (player.getJob() == "Warrior") {
            player.setHealthPoints(player.getHealthPoints() - 10);
        }

        levelUp(player);
        return getEncounterWonMessage(player, getLoot());
    } else {

        player.setHealthPoints(player.getHealthPoints() - healthAdjustment);

        return getEncounterLostMessage(player, getDamage());
    }
}
