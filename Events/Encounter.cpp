

#include "Event.h"
#include "Utilities.h"

//תור התחלה, המשחק שלנו יכיל ארבעה סוגי מפלצות:
//• חילזון (Snail – (עם יכולת קרב ,5 שלל 2 ונזק .10
//• רפש (Slime – (עם יכולת קרב ,12 שלל 5 ונזק .25
//• באלור (Balrog – (עם יכולת קרב ,15 שלל 100 ונזק .9001
//לאחר מפגש, יכולת הקרב של הבלרוג עולה ב ,2- ללא קשר אם ניצח או הפסיד בקרב

bool Encounter::canPlayerWin(Player &player)  {
    bool flag = false;
    if (player.getCombatPower() > CombatPower) {
        flag = true;
    }

    return flag;
}

string Encounter::apply(Player& player) {

    if(getTypeString() == "Balrog"){
        this->setBalrogCombatPower();
    }

    if (canPlayerWin(player)) {
        player.setCoins(player.getCoins() + getLoot());
        if(player.getJob() == "Warrior"){
            player.setHealthPoints(player.getHealthPoints() - ( getDamage() + 10));
        }
        else{
        player.setHealthPoints(player.getHealthPoints() - getDamage());
        }
        levelUp(player);
        return getEncounterWonMessage(player,getLoot());
    } else {
        player.setHealthPoints(player.getHealthPoints() - getDamage());
        return getEncounterLostMessage(player,getDamage());
    }
}
