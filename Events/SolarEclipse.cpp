#include "Event.h"
#include "Utilities.h"



string SolarEclipse::apply(Player& player) {
    if(player.getForce() == 0){
        return getSolarEclipseMessage(player, 0);
    }
    int effect = 0;
    if (player.getJob() == "Magician") {
        player.setForce(player.getForce() + 1);
        effect = 1;
    } else {
        player.setForce(player.getForce() - 1);
        effect = -1;
    }
    return getSolarEclipseMessage(player, effect);
}





string SolarEclipse::getDescription() const {
    return "SolarEclipse";
}

string SolarEclipse::getTypeString() const {
    return "SolarEclipse";
}

