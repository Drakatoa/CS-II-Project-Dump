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
Player::Player(std::string name, double hits, double outs, double strikeOuts, double walks, double hitByPitchs, double sacrifices){
    this->name=name;
    this->hits=hits;
    this->outs=outs;
    this->strikeOuts=strikeOuts;
    this->walks=walks;
    this->hitByPitchs=hitByPitchs;
    this->sacrifices=sacrifices;
}

//method to calculate batting average, return it, and make sure its not dividing by 0
double Player::calcBattingAverage(){
    //declaring variable for denominator of BA to check for division by 0
    double baDenom = hits+outs+strikeOuts;
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
    double obDenom = hits+outs+hitByPitchs+strikeOuts+walks+sacrifices;
    //if statement to check if dividing by zero using threshold method
    if(fabs(obDenom-0.0)<epsilon){
        return 0.0;
    }else{
        return (hits+walks+hitByPitchs)/obDenom;
    }
}

//method takes duplicate player as determined by name,
//and takes all stats from it and adds it to the object
//that was in the node originally
void Player::updatePlayer(Player toBeAdded){
    this->hits+=toBeAdded.hits;
    this->outs+=toBeAdded.outs;
    this->strikeOuts+=toBeAdded.strikeOuts;
    this->walks+=toBeAdded.walks;
    this->hitByPitchs+=toBeAdded.hitByPitchs;
    this->sacrifices+=toBeAdded.sacrifices;
}

//tostring method for player that
//adds everything needed for a single data line and appends it
//to one stringstream and returns the string version of that
//called by main method of static playertostring method that gets
//passed into the recursive tostring method in linklist
std::string Player::toString(){
    //declaring stringstream
    std::stringstream appendix;

    //adding all of the values that need not be rounded, but cast as ints
    appendix<<name<<"\t"<<(int)(hits+outs+strikeOuts)<<"\t"<<(int)hits<<"\t"<<(int)walks<<"\t"<<(int)strikeOuts<<"\t"<<
    (int)hitByPitchs<<"\t"<<(int)sacrifices<<"\t";

    //adding values that need to be rounded to 3 decimal places like batting average and on base percentage
    appendix<<std::fixed<<std::setprecision(3)<<(round(calcBattingAverage()*1000))/1000<<"\t";
    appendix<<std::fixed<<std::setprecision(3)<<(round(calcOnBasePercentage()*1000))/1000<<std::endl;

    //converting the stringstream to string and returning it
    return appendix.str();
}