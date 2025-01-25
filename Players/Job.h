#pragma once
#include <string>

class Job {
public:
    Job() = default;
    virtual ~Job() = default;
    virtual std::string getJobtoString() const = 0;
    virtual std::unique_ptr<Job> clone() const = 0;

};

class Warrior : public Job {
public:
    Warrior() = default;
    ~Warrior() override = default;
    std::string getJobtoString() const override {
        return "Warrior";
    }

    std::unique_ptr<Job> clone() const override {
        return std::make_unique<Warrior>();
    }
};


class Magic : public Job {
public:
    Magic() = default;
    ~Magic() override = default;
    std::string getJobtoString() const override {
        return "Magician";
    }

    std::unique_ptr<Job> clone() const override {
        return std::make_unique<Magic>();
    }
};

class Archer : public Job {
public:
    Archer() = default;
    ~Archer() override = default;
    std::string getJobtoString() const override {
        return "Archer";
    }

    std::unique_ptr<Job> clone() const override {
        return std::make_unique<Archer>();
    }
};