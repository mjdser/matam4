#pragma once

#include "../Players/Player.h"
#include <iostream>
#include <vector>

#define Snail_CombatPower 5
#define Snail_Loot 2
#define Snail_Damage 10

#define Slime_CombatPower 12
#define Slime_Loot 5
#define Slime_Damage 25

#define Barlog_CombatPower 15
#define Barlog_Loot 100
#define Barlog_Damage 9001

using namespace std;

class Event {
public:
    Event() = default;
    virtual ~Event() = default;
    virtual void apply(Player& player) const = 0;
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

    virtual ~Encounter() = default;

    string getDescription() const override {
        return "Encounter with combat power: " + to_string(CombatPower);
    }
};

class Snail : public Encounter {
public:
    Snail();
    ~Snail() override = default;

    string getTypeString() const override;

    void apply(Player& player) const override;
};

class Slime : public Encounter {
public:
    Slime();
    ~Slime() override = default;

    string getTypeString() const override;

    void apply(Player& player) const override;
};

class Barlog : public Encounter {
public:
    Barlog();
    ~Barlog() override = default;

    string getTypeString() const override;

    void apply(Player& player) const override;
};

class Pack : public Encounter {
private:
    std::vector<std::shared_ptr<Encounter>> events;
public:
    explicit Pack(const std::vector<std::shared_ptr<Encounter>>& events);
    ~Pack() override = default;

    string getTypeString() const override;

    string getDescription() const override;

    void apply(Player& player) const override;
};

class SolarEclipse : public Event {
public:
    SolarEclipse() = default;
    ~SolarEclipse() override = default;

    string getDescription() const override;

    string getTypeString() const override;

    void apply(Player& player) const override;
};

class PotionsMerchant : public Event {
private:
    void applyResponsible(Player& player) const;
    void applyRiskTaking(Player& player) const;

public:
    PotionsMerchant() = default;
    ~PotionsMerchant() override = default;

    string getMerchantPurchaseMessage() const;

    string getTypeString() const override;

    void apply(Player& player) const override;



};