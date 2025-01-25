

#include "Event.h"
#include "Utilities.h"





std::string Encounter::apply(Player& player) {
    int powerBeforeAdjustment = getCombatPower();

    if (getTypeString() == "Balrog") {
        setBalrogCombatPower();
    }

    // Default health adjustment
    int healthAdjustment = getDamage();
    if (player.getCombatPower() > powerBeforeAdjustment) {
        // Player wins the encounter
        player.setCoins(player.getCoins() + getLoot());

        if (player.getJob() == "Warrior") {
            player.setHealthPoints(player.getHealthPoints() - 10);
        }

        levelUp(player);
        return getEncounterWonMessage(player, getLoot());
    } else {
        // Player loses the encounter
        player.setHealthPoints(player.getHealthPoints() - healthAdjustment);
        return getEncounterLostMessage(player, getDamage());
    }
}
