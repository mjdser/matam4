
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

void Player::setLevel(int level_toSet) {
    this->level = level_toSet;
}

void Player::setForce(int force_ToSet) {
    this->force = force_ToSet;
}

int Player::getCoins() const {
    return coins;
}

void Player::setCoins(int coins_toSet) {
    this->coins = coins_toSet;
}

void Player::setHealthPoints(int healthPoints_toSet) {
    if(healthPoints_toSet > MAX_HealthPoints) {
        this->healthPoints = MAX_HealthPoints;
        return;
    }
    this->healthPoints = healthPoints_toSet;
}

int Player::getMaxHealthPoints() const {
    return MAX_HealthPoints;
}

string Player::getName() const {
    return name;
}

string Player::getJob() const {
    return job->getJobtoString();
}

string Player::getCharacter() const {
    return character->getCharactertoString();
}

int Player::getForce() const {
    return force;
}


