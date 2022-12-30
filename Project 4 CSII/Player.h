//Rajit Goel CS 2337.002
//RXG210046
//player header with basic inline getter methods and definitions for complicated methods
#include <iostream>
#ifndef PLAYER_H
#define PLAYER_H

//for comparing doubles in player.cpp
const float epsilon = 0.0001f;

class Player{
    private:
        //private variables that store all the player object's data
        //all initialized to 0 and empty
        std::string name = "";
        char team = 'A';
        double hits = 0;
        double outs = 0;
        double strikeOuts = 0;
        double walks = 0;
        double hitByPitchs = 0;
        double sacrifices = 0;
        double errors = 0;
    
    public:
        //constructors
        Player(){}
        //constructor with actual variables
        Player(std::string name, char team);

        //basic getter methods that return private variables;
        //used by main to pass in double methods to hashmap so that
        //it is easier to grab values from a string rather than inputting it all
        std::string getName(){return name;}
        char getTeam(){return team;}
        double getHits(){return hits;}
        double getOuts(){return outs;}
        double getStrikeOuts(){return strikeOuts;}
        double getWalks(){return walks;}
        double getHitByPitchs(){return hitByPitchs;}
        double getSacrifices(){return sacrifices;}
        double getErrors(){return errors;}

        //method also used to get batting average but
        //is calculated everytime
        double calcBattingAverage();

        //method also used to get on base percentage but
        //is calculated everytime
        double calcOnBasePercentage();

        //method used to update a player that has already has a entry in the hashmap of players
        //called when findvalue of the player returns true, uses the char of the play made
        //and adds it to respective stat in player object
        void updatePlayer(char x);

        //method used to output player data in main with tabs and formatting
        std::string toString();
};

#endif // #define PLAYER_H