//Rajit Goel CS 2337.002
//RXG210046
//beetle header with basic inline methods and definitions for complicated methods
//inherits creature
#include <string>
#ifndef BEETLE_H
#define BEETLE_H
#include "Creature.h"

class Beetle : public Creature
{
    private:
        //private variables for checking if turn has passed, if they have breeded, and if they have starved or not
        int turn = 1;
        int starveTimer = 0;
        bool haveBreeded = false;

    public:
        //constructor and destructor
        Beetle(){}
        virtual ~Beetle(){} 

        //move definition
        char move(std::pair<int, int> distAndWallDistN, std::pair<int, int> distAndWallDistE, std::pair<int, int> distAndWallDistS, std::pair<int, int> distAndWallDistW, 
        std::pair<bool, int> codeAndAntsN, std::pair<bool, int> codeAndAntsE, std::pair<bool, int> codeAndAntsS, std::pair<bool, int> codeAndAntsW) const override;

        //breed definition
        char breed(bool nOpen, bool eOpen, bool sOpen, bool wOpen) const override;

        //inline function for resetting starve timer to 0
        void resetStarve(){
            starveTimer = 0;
        }

        //inline function for increasing starve timer by 1
        void increaseStarve(){
            starveTimer += 1;
        }

        //inline function for returning whether or not the beetle should starve that turn or not
        //if true, beetle is deleted and pointer is gone
        bool starve(){
            return starveTimer>=5;
        }

        //inline getter function for breeding status
        int getBreedStatus(){
            return haveBreeded;
        }

        //inline setter function for breeding status
        void changeBreedStatus(bool newBreedingStatus){
            haveBreeded = newBreedingStatus;
        }

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

};

#endif // BEETLE_H