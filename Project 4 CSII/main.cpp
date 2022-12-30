//Rajit Goel CS 2337.002
//RXG210046
//This program first takes input from a file of keys that have a type of play associated with each key, and stores them
//in a hashmap for quick lookup. The program then takes input for a file name and takes the file and parses out
//a list of turns/plays that happened in a game of Mario Super Sluggers and takes the team, player, and the play they did,
//and stores them in a hashmap and updating their batting records, by looking them up in the first hashmap.
//It then calculates their stats and who's the first, second, and third leaders, and if there are ties
//for each stat and displays them using another hashmap for getting each stat.
//iostream for input and output to console
//fstream for opening and taking input from a file
//iomanip for setting the output values to be truncated to 3 decimals
//math.h for absolute value and rounding
//vectors for storing player names to act as keys
//float.h for setting doubles to be max negative or positive value
//including generic hashmap, a hashmap of my design, that hashes by key input being a string and value being generic (did not use unordered_map)
//including player to create player objects to store and calculate stats
#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <vector>
#include <float.h>
#include "Player.h"
#include "GenericHashMap.h"

using namespace std;

//method called from displayLeagueLeaders; this method actually displays the leaders
//takes the strings constructed from calculateThreeStrings, and the values from findTopThree
//and prints both of them for each place when needed, also takes bool to make sure formatting is right
void displayLeaders(string first, string second, string third, double one, double two, double three, bool isFloat){
    //count variable for counting the number of commas in each string to make sure we are printing each place right
    int commaCount=0;
    //if it is float (BA and OBP), this goes
    if(isFloat){
        //outputs with correct precision and 3 decimals, first leader list is printed no matter what
        cout<<fixed<<setprecision(3)<<(round(one*1000))/1000<<"\t"<<first<<endl;
        //iterates through and counts number of commas
        for(long unsigned int i=0;i<first.length();i++){
            if(first.at(i)==','){
                commaCount++;
            }
        }
        //if the number of commas found is 2 or more, then we can stop
        if(commaCount>=2){
            return;
        //otherwise we keep going and output the second leader list    
        }else{
            cout<<fixed<<setprecision(3)<<(round(two*1000))/1000<<"\t"<<second<<endl;
        }
        //and check for commas again
        for(long unsigned int i=0;i<second.length();i++){
            if(second.at(i)==','){
                commaCount++;
            }
        }
        //if commas doesn't equal 0, we can print the third leader list and then we're done
        if(commaCount!=0){
            return;
        }else{
            cout<<fixed<<setprecision(3)<<(round(three*1000))/1000<<"\t"<<third<<endl;
        }
    //this is the same as above except numbers are cast to ints    
    }else{
        cout<<(int)one<<"\t"<<first<<endl;
        for(long unsigned int i=0;i<first.length();i++){
            if(first.at(i)==','){
                commaCount++;
            }
        }
        if(commaCount>=2){
            return;
        }else{
            cout<<(int)two<<"\t"<<second<<endl;
        }
        for(long unsigned int i=0;i<second.length();i++){
            if(second.at(i)==','){
                commaCount++;
            }
        }
        if(commaCount!=0){
            return;
        }else{
            cout<<(int)three<<"\t"<<third<<endl;
        }
    } 
}

//method called from displayLeagueLeaders; this method calculates the strings of the top
//three leaders of each category using the values from findTopThree and takes the strings 
//in by reference in order to change them, these strings will be used later in displayLeaders
//takes in the hashmap of players, hashmap of player methods, which all consist of returning 
//doubles and referencing them, strings by reference, vector of playernames, and numbers
//stat string for passing into hashmap of player methods to grab which value is needed
void calculateThreeStrings(string &first, string &second, string &third, double one, double two, double three, string stat, vector<string> playerNames, GenericHashMap<Player> hashPlayers, GenericHashMap<double(Player::*)()> hashPMethods){
    //declares double to keep track of the stat 
    double curNum;
    //resetting all strings to make them empty for next use
    first="";
    second="";
    third="";
    //iterate through all players in the array
    for(long unsigned int i=0;i<playerNames.size();i++){
        //since getValue() returns a reference, and i passed in the player methods by reference, I have to double dereference
        //the method returned by hashPMethods getting the value of the stat passed in, set double to whatever stat is passed in
        //and get the player stored with player name at i from hashmap of players, and grabbing the function that gets the value
        curNum = (((hashPlayers.getValue(playerNames.at(i)))->**hashPMethods.getValue(stat))());
        //if the stat is equal to the stat that is first
        if(one==curNum){
            //if the list is empty and is the first player, add just the name
            if(first==""){
                first+=(hashPlayers.getValue(playerNames.at(i)))->getName();
            //otherwise add a comma and their name
            }else{
                first+=", ";
                first+=(hashPlayers.getValue(playerNames.at(i)))->getName();
            }
        //same as above but for second place players
        }else if(two==curNum){
            if(second==""){
                second+=(hashPlayers.getValue(playerNames.at(i)))->getName();
            }else{
                second+=", ";
                second+=(hashPlayers.getValue(playerNames.at(i)))->getName();
            }
        //same as above but for third place players
        }else if(three==curNum){
            if(third==""){
                third+=(hashPlayers.getValue(playerNames.at(i)))->getName();
            }else{
                third+=", ";
                third+=(hashPlayers.getValue(playerNames.at(i)))->getName();
            }
        }
    }
}

//method called from displayLeagueLeaders; this method calculates the top three values
//of all the players of each category, passes in by reference 3 doubles to change them for later use, 
//stat string for passing into hashmap of player methods to grab which value is needed,
//takes in the hashmap of players, 
//hashmap of player methods, which all consist of returning doubles and referencing them, 
//doubles by reference, and vector of playernames
void findTopThree(double &one, double &two, double &three, string stat, vector<string> playerNames, GenericHashMap<Player> hashPlayers, GenericHashMap<double(Player::*)()> hashPMethods){
    //sets each variable equal to the lowest double value
    one = two = three = -DBL_MAX;
    //declares double to keep track of the stat 
    double curNum;
    //if we are calculating the minimum/least doubles for strikeouts
    if(stat=="SO"){
        //one two and three are set to the highest double value
        one = two = three = DBL_MAX;
        //iterates through list of players
        for(long unsigned int i=0;i<playerNames.size();i++){
            //since getValue() returns a reference, and i passed in the player methods by reference, I have to double dereference
            //the method returned by hashPMethods getting the value of the stat passed in, set double to whatever stat is passed in
            //and get the player stored with player name at i from hashmap of players, and grabbing the function that gets the value
            curNum = (((hashPlayers.getValue(playerNames.at(i)))->**hashPMethods.getValue(stat))());
            //if it is the least found so far, three and two get moved up to two and one's values
            //and one is set to curnum
            if(curNum<one){
                three=two;
                two=one;
                one=curNum;
            //if it is less than the second value and doesn't equal one
            //three gets moved up to two's value, and two is set to curnum
            } else if(curNum<two&&curNum!=one){
                three=two;
                two=curNum;
            //if it is less than third value and doesn't equal two
            //third is set to curnum
            } else if(curNum<three&&curNum!=two){
                three=curNum;
            }
        }
    //otherwise calculate the maximum/most doubles (not strikeouts)
    }else{
        //same algorithm as above but less thans are set to greater thans
        for(long unsigned int i=0;i<playerNames.size();i++){
            curNum = (((hashPlayers.getValue(playerNames.at(i)))->**hashPMethods.getValue(stat))());
            if(curNum>one){
                three=two;
                two=one;
                one=curNum;
            } else if(curNum>two&&curNum!=one){
                three=two;
                two=curNum;
            } else if(curNum>three&&curNum!=two){
                three=curNum;
            }
        }
    }
}

//this method is called from main to display all the league leaders, it passes in the vector of player names,
//and hashmap of players created from main, it basically calls all the functions for all stats to display for league leaders
//and also creates the hashmap of player methods that is passed into each function for calculating leaders
void displayLeagueLeaders(vector<string> playerNames, GenericHashMap<Player> hashPlayers){
    //declaring generic hashmap of a reference to player methods that return doubles
    GenericHashMap<double(Player::*)()> hashPMethods;
    //inserting all the player methods needed into the hashmap, each with its own string of what they represent
    hashPMethods.insert("BA", &Player::calcBattingAverage);
    hashPMethods.insert("OBP", &Player::calcOnBasePercentage);
    hashPMethods.insert("H", &Player::getHits);
    hashPMethods.insert("W", &Player::getWalks);
    hashPMethods.insert("SO", &Player::getStrikeOuts);
    hashPMethods.insert("HBP", &Player::getHitByPitchs);
    //declaring strings and doubles to be used to calculate league leaders
    double one=0, two=0, three=0;
    string first="", second="", third="";
    //outputting header and first stat which is batting average
    cout<<"LEAGUE LEADERS"<<endl<<"BATTING AVERAGE"<<endl;
    //passing in doubles, strings, the stat its for for getting the value from the hashmap, list of playernames to iterate through,
    //hashmap of players to get values from, and hashmap of player methods to use to pull references to functions from, and whether its a float or
    //not for outputting in display leaders

    //first function calculates the 3 best values it finds from the players in the hashmap
    findTopThree(one, two, three, "BA", playerNames, hashPlayers, hashPMethods);
    //second function concatenates each string using the values found
    calculateThreeStrings(first, second, third, one, two, three, "BA", playerNames, hashPlayers, hashPMethods);
    //third function displays the strings made and whether or they should be outputted based on number of players found in string
    displayLeaders(first, second, third, one, two, three, true);

    //repeats for every stat needed
    cout<<endl<<"ON-BASE PERCENTAGE"<<endl;
    findTopThree(one, two, three, "OBP", playerNames, hashPlayers, hashPMethods);
    calculateThreeStrings(first, second, third, one, two, three, "OBP", playerNames, hashPlayers, hashPMethods);
    displayLeaders(first, second, third, one, two, three, true);
    cout<<endl<<"HITS"<<endl;
    findTopThree(one, two, three, "H", playerNames, hashPlayers, hashPMethods);
    calculateThreeStrings(first, second, third, one, two, three, "H", playerNames, hashPlayers, hashPMethods);
    displayLeaders(first, second, third, one, two, three, false);
    cout<<endl<<"WALKS"<<endl;
    findTopThree(one, two, three, "W", playerNames, hashPlayers, hashPMethods);
    calculateThreeStrings(first, second, third, one, two, three, "W", playerNames, hashPlayers, hashPMethods);
    displayLeaders(first, second, third, one, two, three, false);
    cout<<endl<<"STRIKEOUTS"<<endl;
    findTopThree(one, two, three, "SO", playerNames, hashPlayers, hashPMethods);
    calculateThreeStrings(first, second, third, one, two, three, "SO", playerNames, hashPlayers, hashPMethods);
    displayLeaders(first, second, third, one, two, three, false);
    cout<<endl<<"HIT BY PITCH"<<endl;
    findTopThree(one, two, three, "HBP", playerNames, hashPlayers, hashPMethods);
    calculateThreeStrings(first, second, third, one, two, three, "HBP", playerNames, hashPlayers, hashPMethods);
    displayLeaders(first, second, third, one, two, three, false);
}

//function to display player data, takes in both vectors of away and home players in order to separate them out and 
//display the headers of each properly
void displayPlayerData(vector<string> playerNamesA, vector<string> playerNamesH, GenericHashMap<Player> hashPlayers){
    //prints out away and then iterates through list of player names from away
    //gets value using hashmap method and takes name from vector at i and calls its to string method
    cout<<"AWAY"<<endl;
    for(long unsigned int i=0;i<playerNamesA.size();i++){
        cout<<(hashPlayers.getValue(playerNamesA.at(i)))->toString();
    }
    //does the same for home players
    cout<<endl<<"HOME"<<endl;
    for(long unsigned int i=0;i<playerNamesH.size();i++){
        cout<<(hashPlayers.getValue(playerNamesH.at(i)))->toString();
    }
    //extra line to prepare for league leaders output
    cout<<endl;
}

//helper function used for finding the minimum value in the vector from the index indicated
long unsigned int findMinValIndex(long unsigned int index, vector<string> playerNames){
    //min index is declared and initialized to index passed in from sortAlphabetically()
    long unsigned int minValIndex = index;
    //iterates through rest of vector from index
    for(long unsigned int i=index;i<playerNames.size();i++){
        //if the player name of at current lowest index, is more than the current index player
        //set min val index to that
        if(playerNames.at(minValIndex)>playerNames.at(i)){
            minValIndex=i;
        }
    }
    //return min val
    return minValIndex;
}

//function used to sort names of away and home teams alphabetically
void sortAlphabetically(vector<string> &playerNames){
    //iterates through vector
    for(long unsigned int i=0; i<playerNames.size();i++){
        //when it reaches the end, you know it's done
        if(i==playerNames.size()-1){
            break;
        }
        //calls find min val index to get the index at which the minimum is at
        long unsigned int minValIndex = findMinValIndex(i, playerNames);
        //gets name of player at that index
        string minVal = playerNames.at(minValIndex);
        //if min val index and i are the same, we continue on
        if(minValIndex==i){
            continue;
        }
        //otherwise we erase the min val at the index and insert it at the beginning of the iteration
        playerNames.erase(playerNames.begin() + minValIndex);
        playerNames.insert(playerNames.begin() + i, minVal);
    }
}

//main function where all the parsing happens
int main(){
    //declaring two generic hashmaps of type player for storing players, and type char for storing what type of play a string corresponds to
    GenericHashMap<Player> hashPlayers;
    GenericHashMap<char> hashPlays;
    //declaring name and play for when parsing files for the plays that happened
    string name, play;
    //filename to be inputted
    string fileName;
    //getting input for filename and storing 
    getline(cin, fileName);
    //first, we open the key file for input
    ifstream keyFile("keyfile.txt");
    //declare line for the string to be input from the file
    string lineString;
    char currentChar;
    //checking if file is open
    if(keyFile.is_open()){
        //while there are still lines in the file
        while(getline(keyFile, lineString)){
            //accounting for empty new lines in between lines
            if(lineString==""){
                continue;
            //if the first character is pound we know that we will be reading for
            //types of plays that this title corresponds with
            }else if(lineString.at(0)=='#'){
                //find index where space before letter occurs
                long unsigned int index = lineString.find(' ');
                //switch statement for what's at the letter
                switch(lineString.at(index+1)){
                    //case if outs
                    case 'O':
                        currentChar='O';
                        break;
                    //case if strikeouts if it has a T after first letter,
                    //or if it is just sacrifices
                    case 'S':
                        if(lineString.at(index+2)=='T'){
                            currentChar='K';
                            break;
                        }else{
                            currentChar='S';
                            break;
                        }
                    //case if hit by pitches if character at the 5 position is B
                    //otherwise just hits
                    case 'H':
                        if(lineString.at(index+5)=='B'){
                            currentChar='P';
                            break;
                        }else{
                            currentChar='H';
                            break;
                        }
                    //case if walks
                    case 'W':
                        currentChar='W';
                        break;
                    //case if errors
                    case 'E':
                        currentChar='E';
                        break;
                    //otherwise do nothing
                    default:
                        break;
                }
            //switch statement stores char,
            //then rest of the lines after storing char is what the char corresponds to
            //so we insert it with the whole line and what char it is on
            }else{
                hashPlays.insert(lineString, currentChar);
            }
        }
    //if its not able to open, return error
    }else{
        cout << "There was an error trying to open keyfile.txt.";
        return 1;
    }
    //closing key file
    keyFile.close();
    //opening input file
    ifstream playsFile(fileName);
    //declaring two separate vectors for away and home players to be alphabetised separately
    vector<string> playerNamesAway;
    vector<string> playerNamesHome;
    //checking if input file is open
    if(playsFile.is_open()){
        //while there are still lines in the file
        while(getline(playsFile, lineString)){
            //accounting for empty line at the end of file
            if(lineString==""){
                continue;
            }
            //we always know the first character is going to be team
            char team = lineString.at(0);
            //then we can make a temp string from index 2 to the end of the line
            string temp = lineString.substr(2, lineString.length()-2);
            //finding space to split string along
            long unsigned int index = temp.find(' ');
            //name goes from beginning to space
            name=temp.substr(0, index);
            //play goes from after space to end
            play=temp.substr(index+1, temp.length()-(index+1));
            //we look up the play that was found in the hashmap we created
            //and dereference it since it is returned by reference, (for player objects)
            char storedChar=*(hashPlays.getValue(play));
            //if we do not find the value of the name we are currently on by looking for it
            if(!hashPlayers.findValue(name)){
                //create new player object using name and team
                Player P(name, team);
                //add the current play it just had using the char we found from the hashmap earlier
                P.updatePlayer(storedChar);
                //insert the name and the player with the hashmap
                hashPlayers.insert(name, P);
                //if the team is away, insert name into away names vector
                //otherwise insert name into home names vector
                if(team=='A'){
                    playerNamesAway.push_back(name);
                }else{
                    playerNamesHome.push_back(name);
                }
            //otherwise we return the value of the player from the hashmap and 
            //update the player using the char we got from the hashmap of plays
            }else{
                (hashPlayers.getValue(name))->updatePlayer(storedChar);
            }
        }
    //if its not able to open, return error
    }else{
        cout << "There was an error trying to open "<<fileName<<".";
        return 1;
    }
    //sort both vectors alphabetically
    sortAlphabetically(playerNamesAway);
    sortAlphabetically(playerNamesHome);
    //then use arrays to first display home and away teams in order
    displayPlayerData(playerNamesAway, playerNamesHome, hashPlayers);
    //then create a new vector to combine the two and 
    //reserve memory space for them to make it more efficient
    vector<string> playerNames;
    playerNames.reserve(playerNamesAway.size()+playerNamesHome.size());
    //use insert to append the two arrays to each other
    playerNames.insert(playerNames.end(),playerNamesAway.begin(),playerNamesAway.end());
    playerNames.insert(playerNames.end(),playerNamesHome.begin(),playerNamesHome.end());
    //then clear up memory taken up by the other two arrays to make program more efficient
    playerNamesAway.clear();
    playerNamesAway.shrink_to_fit();
    playerNamesHome.clear();
    playerNamesHome.shrink_to_fit();
    //finally display all league leaders using the final vector
    displayLeagueLeaders(playerNames, hashPlayers);
    return 0;
}