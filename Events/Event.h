#pragma once

#include <iostream>
#include <vector>
#include "../Players/Player.h"

#define Snail_CombatPower 5
#define Snail_Loot 2
#define Snail_Damage 10

#define Slime_CombatPower 12
#define Slime_Loot 5
#define Slime_Damage 25

#define Balrog_CombatPower 15
#define Balrog_Loot 100
#define Balrog_Damage 9001

using namespace std;

class Event {
public:
    Event() = default;
    virtual ~Event() = default;
    virtual string apply(Player& player)  = 0;
    virtual string getDescription() const = 0;
    virtual string getTypeString() const = 0;
};

class Encounter : public Event {
protected:
    int CombatPower;
    int Loot;
    int Damage;
public:

    int getCombatPower() const {
        return CombatPower;
    }
    int getLoot() const {
        return Loot;
    }
    int getDamage() const {
        return Damage;
    }


    Encounter(int CombatPower, int Loot, int Damage)
            : CombatPower(CombatPower), Loot(Loot), Damage(Damage) {}


    ~Encounter() override = default;

    void setBalrogCombatPower() {
        this->CombatPower = CombatPower + 2;
    }

    void levelUp(Player& player) const {
        player.setLevel(player.getLevel() + 1);
    }

    bool canPlayerWin(Player &player);

    string apply(Player &player) override;
};

class Snail : public Encounter {
public:
    Snail();
    ~Snail() override = default;

    string getTypeString() const override;
    string getDescription() const override;


};

class Slime : public Encounter {
public:
    Slime();
    ~Slime() override = default;

    string getTypeString() const override;
    string getDescription() const override;


};

class Balrog : public Encounter {
public:
    Balrog();
    ~Balrog() override = default;

    string getTypeString() const override;
    string getDescription() const override;


};

class Pack : public Encounter {
private:
    std::vector<std::shared_ptr<Encounter>> events;
public:
    explicit Pack(const std::vector<std::shared_ptr<Encounter>>& events);
    ~Pack() override = default;

    string getTypeString() const override;

    string getDescription() const override;

    string apply(Player& player)  override;
};


class SpecialEncounter : public Event {
public:
    SpecialEncounter() = default;
    ~SpecialEncounter() override = default;
};

class SolarEclipse : public SpecialEncounter {
public:
    SolarEclipse() = default;
    ~SolarEclipse() override = default;
    string getDescription() const override;
    string apply(Player& player)  override;
    string getTypeString() const override;
};

class PotionsMerchant : public SpecialEncounter {
private:
    string applyResponsible(Player& player) const;
    string applyRiskTaking(Player& player) const;

public:
    PotionsMerchant() = default;
    ~PotionsMerchant() override = default;
    string getTypeString() const override;


    string getDescription() const override;
    string apply(Player& player)  override;
};