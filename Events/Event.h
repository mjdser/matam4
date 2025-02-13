#pragma once

#include <iostream>
#include <vector>
#include "../Players/Player.h"





using namespace std;

class SolarEclipse;
class PotionsMerchant;
class Snail;
class Slime;
class Balrog;

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


    string apply(Player &player) override;





};

class Snail : public Encounter {
public:
    Snail();
    ~Snail() override = default;

    string getTypeString() const override;
    string getDescription() const override;

    const static int Snail_CombatPower = 5;
    const static int Snail_Loot = 2;
    const static int Snail_Damage = 10;


};

class Slime : public Encounter {
public:
    Slime();
    ~Slime() override = default;

    string getTypeString() const override;
    string getDescription() const override;

    const static int Slime_CombatPower = 12;
    const static int Slime_Loot = 5;
    const static int Slime_Damage = 25;

};

class Balrog : public Encounter {

public:
    Balrog();
    ~Balrog() override = default;

    string getTypeString() const override;
    string getDescription() const override;



    const static int Balrog_CombatPower = 15;
    const static int Balrog_Loot = 100;
    const static int Balrog_Damage = 9001;


};

class Pack : public Encounter {
private:
    std::vector<std::shared_ptr<Encounter>> events;

public:
    explicit Pack(const std::vector<std::shared_ptr<Encounter>>& events);

    string getTypeString() const override;

    string getDescription() const override;

    string apply(Player& player)  override;

    void Refill();
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
    static string applyResponsible(Player& player) ;
    static string applyRiskTaking(Player& player) ;

public:
    PotionsMerchant() = default;
    ~PotionsMerchant() override = default;
    string getTypeString() const override;


    string getDescription() const override;
    string apply(Player& player)  override;

};


