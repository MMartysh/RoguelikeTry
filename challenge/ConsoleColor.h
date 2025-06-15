#ifndef CONSOLE_COLOR_H
#define CONSOLE_COLOR_H

#include <string>

struct Enemy
{
    short id;
    int health;
    int damage;
    int gold;
};
struct Item
{
    std::string name;
    int defense;
    int damage;
    int cost;
    double weight;
};
struct Needs
{
    int thirst;
    int tiredness;
    int hunger;
    Needs()
    {
        hunger = 120;
        thirst = 55;
        tiredness = 200;
    }
};
struct Resources
{
    int wood;
    int rock;
    int crystal;
    int seed;
    int gold;
    int water;
    int food;
    Resources()
    {
        crystal = 0;
        food = 0;
        gold = 0;
        rock = 0;
        seed = 0;
        water = 0;
        wood = 0;
    }
};
struct Armour
{
    Item head;
    Item torso;
    Item legs;
    Item foot;
    Item hands;
};
enum UnrendSymbols
{
    Wall = 0,
    Tree = 1,
    Rock = 2,
    Crystal = 3,
    Grass = 4,
    Water = 5,
    Foe = 6,
    Player = 7

};
#endif
