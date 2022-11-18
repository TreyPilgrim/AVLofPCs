#include "PC.h"
// Setters
// setName
void PC::setName(string &str)
{
    name = str;
}

// setJob
void PC::setJob(string &str)
{
    job = str;
}

// setRace
void PC::setRace(string &str)
{
    race = str;
}

// setLevel
void PC::setLevel(int &num)
{
    level = num;
}

// Get the Name of the player object
string PC::getName() const
{
    return name;
}

//  Get the Race of the player object
string PC::getRace() const
{
    return race;
}

// Get the Job of the player object
string PC::getJob() const
{
    return job;
}

// Get the Level of the player object
int PC::getLevel() const
{
    return this->level;
}