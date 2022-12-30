//Rajit Goel CS 2337.002
//RXG210046
//This program takes input from a file of various different Nintendo characters and their batting records
//in the game Mario Super Sluggers. It then calculates their stats and who's the first, second, and third leaders, and if there are ties
//for each stat and displays them using linked lists.
//iostream for input and output to console
//fstream for opening and taking input from a file
//iomanip for setting the output values to be truncated to 3 decimals
//math.h for absolute value and rounding
//including linked lists to store all objects
//including player to create players and store them in templated nodes
#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include "LinkList.h"
#include "Player.h"

using namespace std;

//these static methods are used when calling linklist methods as
//we needed to make the linklist methods as generic as possible
//in order to make sure all objects passed into the linkedlist
//are able to use the class
//this also makes sure there are no references to player in node.h or linklist.h
//the methods basically are passed into other functions in linklist in main and the
//linklist methods use these functions by calling it on the object in the node

//this basically allows linklist to get data from the object in order to perform actions needed,
//allowing the user to pass in any function of the type they need to use the method in linklist
static double playerGetHits(Player P){
    return P.getHits();
}
static double playerGetBA(Player P){
    return P.calcBattingAverage();
}
static double playerGetOBP(Player P){
    return P.calcOnBasePercentage();
}
static double playerGetWalks(Player P){
    return P.getWalks();
}
static double playerGetStrikeouts(Player P){
    return P.getStrikeOuts();
}
static double playerGetHitByPitches(Player P){
    return P.getHitByPitchs();
}
static string playerGetName(Player P){
    return P.getName();
}
//this is used in the recursive tostring method, in order to 
//grab data and compile a string that can be used to print out the dataset
//of all players
static string playerToString(Player P){
    return P.toString();
}

//this performs all actions required to print the leaders to the console
//takes four linklists by reference: original linklist of players, and 3 new linklists that will contain all of the players for each
//stat needed. these 3 linklists will be added to, displayed, and then cleared for each stat.
void displayLeaders(LinkList<Player> &Players, LinkList<Player> &First, LinkList<Player> &Second, LinkList<Player> &Third){
    
    //declaring doubles to keep track of 3 highest values
    double one=0.0, two=0.0, three=0.0;

    //prints out category name
    cout<<"BATTING AVERAGE"<<endl;
    //calls linklist method on players to find out the 3 highest batting average values, passes in
    //doubles by reference, a reference to the static main method to retrive batting average values
    //from the player object, and bool of whether it is calculating minimum values or not
    Players.calculateThreeBest(one, two, three, &playerGetBA, false);
    //all three lists are filled by calling linklist method on players and
    //matching each double value to the object's value of batting average in each of the nodes of players,
    //and if it does match, add it to the list. passing in a reference to the static main method to
    //retrieve object's double/batting average value needed to compare
    Players.fillList(First, one, &playerGetBA);
    Players.fillList(Second, two, &playerGetBA);
    Players.fillList(Third, three, &playerGetBA);
    //first value and list is printed no matter what, and formatted so that floating point values
    //are printed to 3 decimals
    cout<<fixed<<setprecision(3)<<(round(one*1000))/1000<<"\t";
    //prints a list of names separated by commas and gets names, by passing in reference to
    //static string main method that retrive's objects string/name value
    First.printListOfNames(&playerGetName);
    //performs checks here to check if the length/number of nodes in first is less than 3 and
    //the number of players is more than one, then it will print whatever it has in
    //the second list in the same way that it did the first.
    if(First.getLength()<3&&Players.getLength()>1){
        cout<<fixed<<setprecision(3)<<(round(two*1000))/1000<<"\t";
        Second.printListOfNames(&playerGetName);
    }
    //performs checks here to check if the length/number of nodes in first and second is less than 3 and
    //the number of players is more than two, then it will print whatever it has in
    //the third list in the same way that it did the second and first.
    if(First.getLength()+Second.getLength()<3&&Players.getLength()>2){
        cout<<fixed<<setprecision(3)<<(round(three*1000))/1000<<"\t";
        Third.printListOfNames(&playerGetName);
    }
    //adds another new line in order to separate out categories
    cout<<endl;
    //clears list for next category use
    //basically runs through list and frees up memory use by nodes and removes it from the list
    First.clearList();
    Second.clearList();
    Third.clearList();

    //prints out category name 
    cout<<"ON-BASE PERCENTAGE"<<endl;
    //calls linklist method on players to find out the 3 highest on base percentage values, passes in
    //doubles by reference, a reference to the static main method to retrive on base percentage values
    //from the player object, and bool of whether it is calculating minimum values or not
    Players.calculateThreeBest(one, two, three, &playerGetOBP, false);
    //all three lists are filled by calling linklist method on players and
    //matching each double value to the object's value of on base percentage in each of the nodes of players,
    //and if it does match, add it to the list. passing in a reference to the static main method to
    //retrieve object's double/on base percentage value needed to compare
    Players.fillList(First, one, &playerGetOBP);
    Players.fillList(Second, two, &playerGetOBP);
    Players.fillList(Third, three, &playerGetOBP);
    //first value and list is printed no matter what, and formatted so that floating point values
    //are printed to 3 decimals
    cout<<fixed<<setprecision(3)<<(round(one*1000))/1000<<"\t";
    //prints a list of names separated by commas and gets names, by passing in reference to
    //static string main method that retrive's objects string/name value
    First.printListOfNames(&playerGetName);
    //performs checks here to check if the length/number of nodes in first is less than 3 and
    //the number of players is more than one, then it will print whatever it has in
    //the second list in the same way that it did the first.
    if(First.getLength()<3&&Players.getLength()>1){
        cout<<fixed<<setprecision(3)<<(round(two*1000))/1000<<"\t";
        Second.printListOfNames(&playerGetName);
    }
    //performs checks here to check if the length/number of nodes in first and second is less than 3 and
    //the number of players is more than two, then it will print whatever it has in
    //the third list in the same way that it did the second and first.
    if(First.getLength()+Second.getLength()<3&&Players.getLength()>2){
        cout<<fixed<<setprecision(3)<<(round(three*1000))/1000<<"\t";
        Third.printListOfNames(&playerGetName);
    }
    //adds another new line in order to separate out categories
    cout<<endl;
    //clears list for next category use
    //basically runs through list and frees up memory use by nodes and removes it from the list
    First.clearList();
    Second.clearList();
    Third.clearList();

    //prints out category name 
    cout<<"HITS"<<endl;
    //calls linklist method on players to find out the 3 highest hits values, passes in
    //doubles by reference, a reference to the static main method to retrive hits values
    //from the player object, and bool of whether it is calculating minimum values or not
    Players.calculateThreeBest(one, two, three, &playerGetHits, false);
    //all three lists are filled by calling linklist method on players and
    //matching each double value to the object's value of hits in each of the nodes of players,
    //and if it does match, add it to the list. passing in a reference to the static main method to
    //retrieve object's double/hits value needed to compare
    Players.fillList(First, one, &playerGetHits);
    Players.fillList(Second, two, &playerGetHits);
    Players.fillList(Third, three, &playerGetHits);
    //first value and list is printed no matter what, and formatted so that these non-floating
    //point values are cast to ints and printed as such
    cout<<(int)one<<"\t";
    //prints a list of names separated by commas and gets names, by passing in reference to
    //static string main method that retrive's objects string/name value
    First.printListOfNames(&playerGetName);
    //performs checks here to check if the length/number of nodes in first is less than 3 and
    //the number of players is more than one, then it will print whatever it has in
    //the second list in the same way that it did the first.
    if(First.getLength()<3&&Players.getLength()>1){
        cout<<(int)two<<"\t";
        Second.printListOfNames(&playerGetName);
    }
    //performs checks here to check if the length/number of nodes in first and second is less than 3 and
    //the number of players is more than two, then it will print whatever it has in
    //the third list in the same way that it did the second and first.
    if(First.getLength()+Second.getLength()<3&&Players.getLength()>2){
        cout<<(int)three<<"\t";
        Third.printListOfNames(&playerGetName);
    }
    //adds another new line in order to separate out categories
    cout<<endl;
    //clears list for next category use
    //basically runs through list and frees up memory use by nodes and removes it from the list
    First.clearList();
    Second.clearList();
    Third.clearList();

    //prints out category name 
    cout<<"WALKS"<<endl;
    //calls linklist method on players to find out the 3 highest walks values, passes in
    //doubles by reference, a reference to the static main method to retrive walks values
    //from the player object, and bool of whether it is calculating minimum values or not
    Players.calculateThreeBest(one, two, three, &playerGetWalks, false);
    //all three lists are filled by calling linklist method on players and
    //matching each double value to the object's value of walks in each of the nodes of players,
    //and if it does match, add it to the list. passing in a reference to the static main method to
    //retrieve object's double/walks value needed to compare
    Players.fillList(First, one, &playerGetWalks);
    Players.fillList(Second, two, &playerGetWalks);
    Players.fillList(Third, three, &playerGetWalks);
    //first value and list is printed no matter what, and formatted so that these non-floating
    //point values are cast to ints and printed as such
    cout<<(int)one<<"\t";
    //prints a list of names separated by commas and gets names, by passing in reference to
    //static string main method that retrive's objects string/name value
    First.printListOfNames(&playerGetName);
    //performs checks here to check if the length/number of nodes in first is less than 3 and
    //the number of players is more than one, then it will print whatever it has in
    //the second list in the same way that it did the first.
    if(First.getLength()<3&&Players.getLength()>1){
        cout<<(int)two<<"\t";
        Second.printListOfNames(&playerGetName);
    }
    //performs checks here to check if the length/number of nodes in first and second is less than 3 and
    //the number of players is more than two, then it will print whatever it has in
    //the third list in the same way that it did the second and first.
    if(First.getLength()+Second.getLength()<3&&Players.getLength()>2){
        cout<<(int)three<<"\t";
        Third.printListOfNames(&playerGetName);
    }
    //adds another new line in order to separate out categories
    cout<<endl;
    //clears list for next category use
    //basically runs through list and frees up memory use by nodes and removes it from the list
    First.clearList();
    Second.clearList();
    Third.clearList();

    //prints out category name 
    cout<<"STRIKEOUTS"<<endl;
    //calls linklist method on players to find out the 3 lowest strikeouts values, passes in
    //doubles by reference, a reference to the static main method to retrive strikeouts values
    //from the player object, and bool of whether it is calculating minimum values or not
    //in this case, it is
    Players.calculateThreeBest(one, two, three, &playerGetStrikeouts, true);
    //all three lists are filled by calling linklist method on players and
    //matching each double value to the object's value of strikeouts in each of the nodes of players,
    //and if it does match, add it to the list. passing in a reference to the static main method to
    //retrieve object's double/strikeouts value needed to compare
    Players.fillList(First, one, &playerGetStrikeouts);
    Players.fillList(Second, two, &playerGetStrikeouts);
    Players.fillList(Third, three, &playerGetStrikeouts);
    //first value and list is printed no matter what, and formatted so that these non-floating
    //point values are cast to ints and printed as such
    cout<<(int)one<<"\t";
    //prints a list of names separated by commas and gets names, by passing in reference to
    //static string main method that retrive's objects string/name value
    First.printListOfNames(&playerGetName);
    //performs checks here to check if the length/number of nodes in first is less than 3 and
    //the number of players is more than one, then it will print whatever it has in
    //the second list in the same way that it did the first.
    if(First.getLength()<3&&Players.getLength()>1){
        cout<<(int)two<<"\t";
        Second.printListOfNames(&playerGetName);
    }
    //performs checks here to check if the length/number of nodes in first and second is less than 3 and
    //the number of players is more than two, then it will print whatever it has in
    //the third list in the same way that it did the second and first.
    if(First.getLength()+Second.getLength()<3&&Players.getLength()>2){
        cout<<(int)three<<"\t";
        Third.printListOfNames(&playerGetName);
    }
    //adds another new line in order to separate out categories
    cout<<endl;
    //clears list for next category use
    //basically runs through list and frees up memory use by nodes and removes it from the list
    First.clearList();
    Second.clearList();
    Third.clearList();

    //prints out category name 
    cout<<"HIT BY PITCH"<<endl;
    //calls linklist method on players to find out the 3 highest hit by pitches values, passes in
    //doubles by reference, a reference to the static main method to retrive hit by pitches values
    //from the player object, and bool of whether it is calculating minimum values or not
    Players.calculateThreeBest(one, two, three, &playerGetHitByPitches, false);
    //all three lists are filled by calling linklist method on players and
    //matching each double value to the object's value of hit by pitches in each of the nodes of players,
    //and if it does match, add it to the list. passing in a reference to the static main method to
    //retrieve object's double/hit by pitches value needed to compare
    Players.fillList(First, one, &playerGetHitByPitches);
    Players.fillList(Second, two, &playerGetHitByPitches);
    Players.fillList(Third, three, &playerGetHitByPitches);
    //first value and list is printed no matter what, and formatted so that these non-floating
    //point values are cast to ints and printed as such
    cout<<(int)one<<"\t";
    //prints a list of names separated by commas and gets names, by passing in reference to
    //static string main method that retrive's objects string/name value
    First.printListOfNames(&playerGetName);
    //performs checks here to check if the length/number of nodes in first is less than 3 and
    //the number of players is more than one, then it will print whatever it has in
    //the second list in the same way that it did the first.
    if(First.getLength()<3&&Players.getLength()>1){
        cout<<(int)two<<"\t";
        Second.printListOfNames(&playerGetName);
    }
    //performs checks here to check if the length/number of nodes in first and second is less than 3 and
    //the number of players is more than two, then it will print whatever it has in
    //the third list in the same way that it did the second and first.
    if(First.getLength()+Second.getLength()<3&&Players.getLength()>2){
        cout<<(int)three<<"\t";
        Third.printListOfNames(&playerGetName);
    }
    //adds another new line in order to separate out categories
    cout<<endl;
    //clears list for next category use
    //basically runs through list and frees up memory use by nodes and removes it from the list
    First.clearList();
    Second.clearList();
    Third.clearList();

}

//method to iterate through the record of the string given and calculates/parses it for that stat for the person which it is on
//it then makes a player object out of the stats and name, checks if there is a duplicate name in the linklist, and if there is,
//it combines the two objects, otherwise it creates a new node with player object
//switch statement to make sure there are no invalids and continues in the loop
//method takes name and batting record from the vector, and takes in the new players linklist by reference
void battingRecord(string name, string wholeRecord, LinkList<Player> &Players){
    //declares and sets all variables to 0
    double hits=0, outs=0, strikeOuts=0, walks=0, hitByPitchs=0, sacrifices=0; 
    //iterates through record string and adds to each stat
    for(unsigned int j=0;j<wholeRecord.length();j++){
        switch (wholeRecord.at(j)){
            case 'H': 
                hits++;
                continue;
            case 'O': 
                outs++;
                continue;
            case 'K': 
                strikeOuts++;
                continue;
            case 'W': 
                walks++;
                continue;
            case 'P': 
                hitByPitchs++;
                continue;
            case 'S': 
                sacrifices++;
                continue;
            default:
                continue;
        }
    }

    //player pointer created by calling players linklist method and checking if the name of the node
    //is equal to a name in any of the nodes in the list, passes in get name method to allow the linklist
    //method to retrieve the string from the player obj
    Player* ifExists=Players.checkName(name, &playerGetName);
    //player object created using name and stats calculated
    Player P(name, hits, outs, strikeOuts, walks, hitByPitchs, sacrifices);

    //if the player pointer doesn't return null,
    //player pointer calls method to combine its own player object with the new player object 
    //created and combines all the stats needed.
    if(ifExists!=NULL){
        ifExists->updatePlayer(P);
    //if the player pointer does return null,
    //just create and insert node at the end of linklist
    } else {
        Players.insertEnd(P);
    }

}

//main method where all the magic happens
int main(){

    //create templated linklist of players of player class type
    LinkList<Player> Players;
    //create strings in order to separate and calculate stats from the file
    string name, record;
    //taking filename input and separating it with a new line from the rest of the data
    string fileName;
    cout<<"Enter file name: ";
    getline(cin, fileName);
    cout<<endl;
    //declaring fstream variable and opening the file to connect it to a stream object
    ifstream statsFile (fileName);
    //declaring string to read file
    string recordString;
    //checking if file is reachable/opened and if not, returning exit code 1
    if(statsFile.is_open()){
        //reads each line into the same string and separates and sets the name and record into two different strings using find and substr
        while(getline(statsFile, recordString)){
            long unsigned int index = recordString.find(' ');
            name=recordString.substr(0, index);
            record=recordString.substr(index+1, recordString.length()-(index+1));
            battingRecord(name, record, Players);
        }
    //returns 1/error if file was not able to be opened
    }else{
        cout << "There was an error trying to open "<<fileName<<".";
        return 1;
    }
    //closes the input file
    statsFile.close();

    //calls linklist method to alphabetically sort players,
    //passes in getplayername method by reference in order to allow 
    //method to retrieve string values from templated object/in this case
    //the player object
    Players.sortAlphabetically(&playerGetName);

    //calls the recursive tostring method which passes in the head node, the reference to player tostring, which calls the 
    //players tostring method which returns a string of a data line with name and each stat tabbed over
    //and an empty string to keep recursively adding on to the string
    //outputs that, and then the league leaders header, and another newline to let the categories separate out from the header
    cout<<Players.toString(Players.getHead(), &playerToString, "")<<"LEAGUE LEADERS"<<endl;

    //creating 3 player linklists to be passed into displayleader function by reference
    LinkList<Player> First, Second, Third;
    //calls function to perform calculation of leaders and display them
    displayLeaders(Players, First, Second, Third);
    
    return 0;
}