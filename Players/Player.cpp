
#include <iostream>
#include <fstream>
#include "Player.h"

using std::string;



Player::Player(const string& name, const string& character, const string& job) : name(name), level(1), coins(10),
force(5), healthPoints(MAX_HP), MAX_HealthPoints(MAX_HP) {
    if (character == "RiskTaking") {
        this->character = std::make_unique<RiskTaking>();
    } else if (character == "Responsible") {
        this->character = std::make_unique<Responsible>();
    }

    if (job == "Warrior") {
        this->healthPoints = MAX_HP_WARRIOR;
        this->MAX_HealthPoints = MAX_HP_WARRIOR;
        this->job = std::make_unique<Warrior>();
    } else if (job == "Magic") {
        this->job = std::make_unique<Magic>();
    } else if (job == "Archer") {
        this->coins = 20;
        this->job = std::make_unique<Archer>();
    }
}


int Player::getCombatPower() const {
    if(job->getJobtoString() == "Warrior") {
        return force * 2 + level;
    }
    return force + level;
}


int Player::getforce() const {
    return force;
}

int Player::getLevel() const {
    return level;
}

int Player::getHealthPoints() const {
    return healthPoints;
}



string Player::getDescription() const {

    string Player_name = this->name;
    string Player_job = this->job->getJobtoString();
    string Player_Character = this->character->getCharactertoString();
    int Player_level = this->level;
    int Player_Force = this->force;

    return Player_name + ", " + Player_job + " with " + Player_Character + " character (level " +
           std::to_string(Player_level) + ", force " + std::to_string(Player_Force) + ")";
}

bool Player::isDead() const {
    return healthPoints <= 0;
}