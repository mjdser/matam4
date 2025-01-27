#include "Event.h"
#include "Utilities.h"

std::string PotionsMerchant::applyResponsible(Player &player) {
    int purchases = 0;
    while (player.getCoins() >= 5 && player.getHealthPoints() < player.getMaxHealthPoints()) {
        player.setCoins(player.getCoins() - 5);
        player.setHealthPoints(player.getHealthPoints() + 10);
        purchases++;
    }
    return getPotionsPurchaseMessage(player, purchases);
}

std::string PotionsMerchant::applyRiskTaking(Player &player) {
    if (player.getCoins() >= 5 && player.getHealthPoints() < player.getMaxHealthPoints() && player.getHealthPoints() < 50) {
        player.setCoins(player.getCoins() - 5);
        player.setHealthPoints(player.getHealthPoints() + 10);
        return getPotionsPurchaseMessage(player, 1);
    }
    return getPotionsPurchaseMessage(player, 0);
}

std::string PotionsMerchant::apply(Player &player) {
    if (player.getCharacter() == "Responsible") {
        return applyResponsible(player);
    } else if (player.getCharacter() == "RiskTaking") {
        return applyRiskTaking(player);
    }
    return "";
}

std::string PotionsMerchant::getDescription() const {
    return "PotionsMerchant";
}

std::string PotionsMerchant::getTypeString() const {
    return "PotionsMerchant";
}