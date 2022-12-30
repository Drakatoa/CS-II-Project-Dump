//Rajit Goel CS 2337.002
//RXG210046
//ant header with basic inline methods and definitions for complicated methods
//inherits creature
#include <string>
#ifndef ANT_H
#define ANT_H
#include "Creature.h"

class Ant : public Creature
{
    private:
        //private variables for checking if turn has passed and if they have breeded
        int turn = 1;
        bool haveBreeded = false;

    public:
        //constructor and destructor
        Ant(){}
        virtual ~Ant(){} 

        //move definition
        char move(std::pair<int, int> distAndWallDistN, std::pair<int, int> distAndWallDistE, std::pair<int, int> distAndWallDistS, std::pair<int, int> distAndWallDistW, 
        std::pair<bool, int> codeAndAntsN, std::pair<bool, int> codeAndAntsE, std::pair<bool, int> codeAndAntsS, std::pair<bool, int> codeAndAntsW) const override;

        //breed definition
        char breed(bool nOpen, bool eOpen, bool sOpen, bool wOpen) const override;

        //inline getter function for turn
        int getTurn(){
            return turn;
        }

        //inline function for increasing turn
        void increaseTurn(){
            turn+=1;
        }

        //inline setter function for turn
        void setTurn(int newTurn){
            turn=newTurn;
        }

        //inline getter function for breeding status
        int getBreedStatus(){
            return haveBreeded;
        }

        //inline setter function for breeding status
        void changeBreedStatus(bool newBreedingStatus){
            haveBreeded = newBreedingStatus;
        }

};

#endif // ANT_H