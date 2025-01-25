

#pragma once
#include <string>

class Character
{
public:

    Character() = default;
    virtual ~Character() = default;
    virtual std::string getCharactertoString() const = 0;
    virtual std::unique_ptr<Character> clone() const = 0;
};

class RiskTaking : public Character
{
public:
    RiskTaking() = default;
    ~RiskTaking() override = default;
    std::string getCharactertoString() const override
    {
        return "RiskTaking";
    }

    std::unique_ptr<Character> clone() const override
    {
        return std::make_unique<RiskTaking>();
    }
};

class Responsible : public Character
{
public:
    Responsible() = default;
    ~Responsible() override = default;
    std::string getCharactertoString() const override
    {
        return "Responsible";
    }

    std::unique_ptr<Character> clone() const override
    {
        return std::make_unique<Responsible>();
    }
};