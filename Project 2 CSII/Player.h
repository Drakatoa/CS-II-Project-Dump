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
        double hits = 0;
        double outs = 0;
        double strikeOuts = 0;
        double walks = 0;
        double hitByPitchs = 0;
        double sacrifices = 0;
    
    public:
        //constructors
        Player(){}
        //constructor with actual variables
        Player(std::string name, double hits, double outs, double strikeOuts, double walks, double hitByPitchs, double sacrifices);

        //basic getter methods that return private variables;
        //used by main to pass in method to linklist classes so that
        //object can use the method for their own class
        std::string getName(){return name;}
        double getHits(){return hits;}
        double getOuts(){return outs;}
        double getStrikeOuts(){return strikeOuts;}
        double getWalks(){return walks;}
        double getHitByPitchs(){return hitByPitchs;}
        double getSacrifices(){return sacrifices;}

        //method also used to get batting average but
        //is calculated everytime
        double calcBattingAverage();

        //method also used to get on base percentage but
        //is calculated everytime
        double calcOnBasePercentage();

        //method used to update a player that has a duplicate entry in the file
        //called by player pointer if it doesn't return null, and takes the player object
        //created and combines the stats of the two.
        void updatePlayer(Player toBeAdded);

        //method used by recursive tostring method that returns a string that linklist
        //uses in order to recursively create a string of the whole dataset and return it
        //called by main and passed into linklist methods
        std::string toString();


};

#endif // #define PLAYER_H
