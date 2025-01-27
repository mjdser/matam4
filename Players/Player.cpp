
#include <iostream>
#include <fstream>
#include "Player.h"

using std::string;


static std::unique_ptr<Character> createCharacter(const std::string& character) {
    if (character == "RiskTaking") return std::make_unique<RiskTaking>();
    if (character == "Responsible") return std::make_unique<Responsible>();
    throw std::invalid_argument("Unknown character type: " + character);
}

static std::unique_ptr<Job> createJob(const std::string& job) {
    if (job == "Warrior") return std::make_unique<Warrior>();
    if (job == "Magician") return std::make_unique<Magic>();
    if (job == "Archer") return std::make_unique<Archer>();
    throw std::invalid_argument("Unknown job type: " + job);
}

void Player::applyJobEffects(const std::string& job_type) {
    if(job_type == "Warrior") {
        this->healthPoints = MAX_HP_WARRIOR;
        this->MAX_HealthPoints = MAX_HP_WARRIOR;
    }
    if(job_type == "Archer") {
        this->coins = 20;
    }
}


Player::Player(const std::string& name, const std::string& character, const std::string& job)
        : name(name), level(1), coins(10), force(5), healthPoints(MAX_HP), MAX_HealthPoints(MAX_HP) {

    this->job = createJob(job);
    this->character = createCharacter(character);


    applyJobEffects(job);
}



Player::Player(const Player& other) :name(other.name), level(other.level),
coins(other.coins), force(other.force){
    this->job = other.job->clone();
    this->character = other.character->clone();
    this->healthPoints = other.healthPoints;
    this->MAX_HealthPoints = other.MAX_HealthPoints;

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
    if(healthPoints_toSet <= 0) {
        this->healthPoints = 0;
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




