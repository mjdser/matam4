#pragma once
#include <string>

class Job {
public:
    Job() = default;
    virtual ~Job() = default;
    virtual std::string getJobtoString() const = 0;

};

class Warrior : public Job {
public:
    Warrior() = default;
    ~Warrior() override = default;
    std::string getJobtoString() const override {
        return "Warrior";
    }
};


class Magic : public Job {
public:
    Magic() = default;
    ~Magic() override = default;
    std::string getJobtoString() const override {
        return "Magic";
    }
};

class Archer : public Job {
public:
    Archer() = default;
    ~Archer() override = default;
    std::string getJobtoString() const override {
        return "Archer";
    }
};