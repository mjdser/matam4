#include "Event.h"
#include "Utilities.h"




/*
void PotionsMerchant::applyResponsible(Player& player) const {
    int counter = 0;
    while (player.getCoins() >= 5 && player.getHealthPoints() < player.getMaxHealthPoints()) {
        player.setCoins(player.getCoins() - 5);
        player.setHealthPoints(player.getHealthPoints() + 10);
        counter++;
    }
    getPotionsPurchaseMessage(player,counter);
}

void PotionsMerchant::applyRiskTaking(Player& player) const {
    int counter = 0;
    if (player.getCoins() >= 5 && player.getHealthPoints() < player.getMaxHealthPoints() && player.getHealthPoints() < 50) {
        player.setCoins(player.getCoins() - 5);
        player.setHealthPoints(player.getHealthPoints() + 10);
        counter++;
    }
    getPotionsPurchaseMessage(player,counter);
}

string PotionsMerchant::apply(Player& player) const {
    if (player.getCharacter() == "Responsible") {
        applyResponsible(player);
    } else if (player.getCharacter() == "RiskTaking") {
        applyRiskTaking(player);
    }
}



*/
string PotionsMerchant::applyResponsible(Player &player) const {
    int counter = 0;
    while (player.getCoins() >= 5 && player.getHealthPoints() < player.getMaxHealthPoints()) {
        player.setCoins(player.getCoins() - 5);
        player.setHealthPoints(player.getHealthPoints() + 10);
        counter++;
    }
    return getPotionsPurchaseMessage(player,counter);
}

string PotionsMerchant::applyRiskTaking(Player &player) const {
    int counter = 0;
    if (player.getCoins() >= 5 && player.getHealthPoints() < player.getMaxHealthPoints() && player.getHealthPoints() < 50) {
        player.setCoins(player.getCoins() - 5);
        player.setHealthPoints(player.getHealthPoints() + 10);
        counter++;
    }
    return getPotionsPurchaseMessage(player,counter);
}

string PotionsMerchant::apply(Player &player) {
    if (player.getCharacter() == "Responsible") {
        return applyResponsible(player);
    } else if (player.getCharacter() == "RiskTaking") {
        return applyRiskTaking(player);
    }
    return "";
}



string PotionsMerchant::getTypeString() const {
    return "PotionsMerchant";
}

