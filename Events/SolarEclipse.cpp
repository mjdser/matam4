#include "Event.h"
#include "Utilities.h"



string SolarEclipse::apply(Player& player) {
    int effect = 0;
    if (player.getCharacter() == "Magician") {
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

