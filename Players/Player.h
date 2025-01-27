
#pragma once

#include <string>
#include <memory>
#include "Job.h"
#include "Character.h"






using std::string;
using std::unique_ptr;


class Player {

    unique_ptr<Job> job;
    unique_ptr<Character> character;
    string name;
    int level;
    int coins;
    int force;
    int healthPoints;
    int MAX_HealthPoints;
    const static int MAX_LEVEL = 10;
    const static int MAX_HP_WARRIOR = 150;
    const static int MAX_HP = 100;
public:

    Player(const string& name, const string& character, const string& job);
    Player(const Player& player);
    ~Player() = default;

    string getJob() const;
    string getCharacter() const;
    int getCombatPower() const;
    /**
     * Gets the description of the player
     *
     * @return - description of the player
    */
    string getDescription() const;

    /**
     * Gets the name of the player
     *
     * @return - name of the player
    */
    string getName() const;

    /**
     * Gets the current level of the player
     *
     * @return - level of the player
    */
    int getLevel() const;

    /**
     * Gets the of force the player has
     *
     * @return - force points of the player
    */
    int getForce() const;

    /**
     * Gets the amount of health points the player currently has
     *
     * @return - health points of the player
    */
    int getHealthPoints() const;

    /**
     * Gets the amount of coins the player has
     *
     * @return - coins of the player
    */
    int getCoins() const;

    bool isDead() const;

    void setCoins(int coins_toSet);

    void setHealthPoints(int healthPoints);

    int getMaxHealthPoints() const;

    void setLevel(int level_ToSet);

    void setForce(int force_ToSet);

    void applyJobEffects(const std::string& job);

};
