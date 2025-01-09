
#pragma once

#include "../Players/Player.h"

#include "iostream"
#include "vector"



#define Snail_CombatPower 5
#define Snail_Loot 2
#define Snail_Damage 10

#define Slime_CombatPower 12
#define Slime_Loot 5
#define Slime_Damage 25

#define Barlog_CombatPower 15
#define Barlog_Loot 100
#define Barlog_Damage 9001


class Event {

public:
    Event() = default;
    virtual ~Event() = default;
    virtual void apply(Player& player) const = 0;
    virtual string getDescription() const = 0;
};


class Encounter : public Event {
protected:
    int CombatPower;
    int Loot;
    int Damage;
public:
    Encounter(int CombatPower, int Loot, int Damage);
    virtual ~Encounter() = default;
    virtual void apply(Player& player) const = 0;
    string getDescription() const ;

};

class Snail : public Encounter {
public:
    Snail();
    string getDescription() const override;
    void apply(Player& player) const override;
};

class Slime : public Encounter {
public:
    Slime();
    string getDescription() const override;
    void apply(Player& player) const override;
};

class Barlog : public Encounter {
public:
    Barlog();
    string getDescription() const override;
    void apply(Player& player) const override;
};

class Pack : public Encounter {
private:
    std::vector<unique_ptr<Encounter>> events;
public:
    Pack();
    string getDescription() const override;
    void apply(Player& player) const override;

};


class SolarEclipse : public Event {
public:
    SolarEclipse();
    string getDescription() const override;
    void apply(Player& player) const override;

};

class PotionsMerchant : public Event {
public:
    PotionsMerchant();
    string getDescription() const override;
    void apply(Player& player) const override;
};