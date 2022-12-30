//Rajit Goel CS 2337.002
//RXG210046
//abstract creature class full of pure virtual methods, for holding creatures in one array
#ifndef CREATURE_H
#define CREATURE_H
#include <string>

class Creature
{
public:
    //constructor and virtual destructor
    Creature(){};
    virtual ~Creature(){} 

    //virtual move function with pairs of values passed in
    virtual char move(std::pair<int, int> distAndWallDistN, std::pair<int, int> distAndWallDistE, std::pair<int, int> distAndWallDistS, std::pair<int, int> distAndWallDistW, 
        std::pair<bool, int> codeAndAntsN, std::pair<bool, int> codeAndAntsE, std::pair<bool, int> codeAndAntsS, std::pair<bool, int> codeAndAntsW) const = 0;

    //virtual breed function with bools to check if spots are open
    virtual char breed(bool nOpen, bool eOpen, bool sOpen, bool wOpen) const = 0;
};

#endif // CREATURE_H