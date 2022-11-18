#pragma once
#include <string>

using std::string;

class PC
{
private:
    // attributes
    string name {"Trey Pilgrim"};
    string race {"PC"};
    string job {"Villager"};
    int level {1};

public:
    PC() = default;

    explicit PC(string &nameVal):
    name(nameVal)
    {}


    explicit PC(string& nameVal, int levelVal):
    name(nameVal), level(levelVal)
    {}

    PC(string &nameVal, string &raceVal, string &jobVal, int levelVal):
    name{nameVal}, race{raceVal}, job{jobVal}, level{levelVal} {}

    ~PC(){}

    // Setters
    void setName (string &str);
    void setRace (string &str);
    void setJob (string &str);
    void setLevel (int &num);

    // Getters
    string getName() const;
    string getRace() const;
    string getJob() const;

    int getLevel() const;
};
