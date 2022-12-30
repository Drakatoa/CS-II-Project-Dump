//Rajit Goel CS 2337.002
//RXG210046
//math.h for absolute value
//sstream to create a string object without having to +=
//each variable/text everytime
//iomanip and string to manipulate outputs to have decimal points correctly
//includes player header
#include <string>
#include <math.h>
#include <sstream>
#include <iomanip>
#include "Player.h"

//constructor sets all values passed to private variable values
Player::Player(std::string name, char team){
    this->name=name;
    this->team=team;
}

//method to calculate batting average, return it, and make sure its not dividing by 0
double Player::calcBattingAverage(){
    //declaring variable for denominator of BA to check for division by 0
    //errors are at bats appearances so those are added too
    double baDenom = hits+outs+strikeOuts+errors;
    //if statement to check if dividing by zero using threshold method
    if(fabs(baDenom-0.0)<epsilon){
        return 0.0;
    }else{
        return hits/baDenom;
    }
}

//method to calculate pn base percentage, return it, and make sure its not dividing by 0
double Player::calcOnBasePercentage(){
    //declaring variable for denominator of OBP to check for division by 0
    //errors are plate appearances so those are added too
    double obDenom = hits+outs+hitByPitchs+strikeOuts+walks+sacrifices+errors;
    //if statement to check if dividing by zero using threshold method
    if(fabs(obDenom-0.0)<epsilon){
        return 0.0;
    }else{
        return (hits+walks+hitByPitchs)/obDenom;
    }
}

//method used to update a player that has already has a entry in the hashmap of players
//also used when adding players after adding the play they have
void Player::updatePlayer(char x){
    //switch case for char passed in
    //chars passed in are based on the play gotten from the hashmap
    //of plays which returns a character of what stat to add to
    switch (x){
        //if stored char is H
        //add to hits
        case 'H': 
            hits++;
            break;
        //if stored char is O
        //add to outs
        case 'O': 
            outs++;
            break;
        //if stored char is K
        //add to strikeouts
        case 'K': 
            strikeOuts++;
            break;
        //if stored char is W
        //add to walks
        case 'W': 
            walks++;
            break;
        //if stored char is P
        //add to hit by pitches
        case 'P': 
            hitByPitchs++;
            break;
        //if stored char is S
        //add to sacrifices
        case 'S': 
            sacrifices++;
            break;
        //if stored char is E
        //add to errors
        case 'E':
            errors++; 
            break;
        //otherwise do nothing
        default:
            break;
    }
}

//tostring method for player that
//adds everything needed for a single data line and appends it
//to one stringstream and returns the string version of that
//called by main method to display player data
std::string Player::toString(){
    //declaring stringstream
    std::stringstream appendix;

    //adding all of the values that need not be rounded, but cast as ints
    //errors are at bats so they are added too
    appendix<<name<<"\t"<<(int)(hits+outs+strikeOuts+errors)<<"\t"<<(int)hits<<"\t"<<(int)walks<<"\t"<<(int)strikeOuts<<"\t"<<
    (int)hitByPitchs<<"\t"<<(int)sacrifices<<"\t";

    //adding values that need to be rounded to 3 decimal places like batting average and on base percentage
    appendix<<std::fixed<<std::setprecision(3)<<(round(calcBattingAverage()*1000))/1000<<"\t";
    appendix<<std::fixed<<std::setprecision(3)<<(round(calcOnBasePercentage()*1000))/1000<<std::endl;

    //converting the stringstream to string and returning it
    return appendix.str();
}