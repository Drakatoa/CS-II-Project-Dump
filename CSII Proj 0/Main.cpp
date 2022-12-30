//Rajit Goel CS 2337.002
//RXG210046
//This program takes input from a file of various different Nintendo characters and their batting records
//in the game Mario Super Sluggers. It then calculates their stats and who's the leader(s) in each stat and
//displays them.
//iostream for input and output to console
//vectors for storing initial values like for names and batting records, and for keeping track of highest names
//fstream for opening and taking input from a file
//iomanip for setting the output values to be truncated to 3 decimals
//math.h for absolute value and rounding
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <math.h>

using namespace std;

//global constant to compare doubles to precision of 3 decimals; threshold method
const float epsilon = 0.0001f;

//method to iterate through the record of the string given and calculates/parses it for that stat for the person which it is on
//switch statement to make sure there are no invalids and continues in the loop
void battingRecord(string wholeRecord, int i, double hits[], double outs[], double strikeOuts[], double walks[], double hitByPitchs[], double sacrifices[]){
    for(unsigned int j=0;j<wholeRecord.length();j++){
        switch (wholeRecord.at(j)){
            case 'H': 
                hits[i]++;
                continue;
            case 'O': 
                outs[i]++;
                continue;
            case 'K': 
                strikeOuts[i]++;
                continue;
            case 'W': 
                walks[i]++;
                continue;
            case 'P': 
                hitByPitchs[i]++;
                continue;
            case 'S': 
                sacrifices[i]++;
                continue;
            default:
                continue;
        }
    }
}

//method to display player data to console by iterating through each array index and vector for names 
//and casting/formatting each value respectively where needed
//fixed and setprecision to round to 3 places after decimal and round with the number multiplied by 1000 to catch when round() doesn't round 5 after the decimal up
void displayPlayerData(vector<string> names, double hits[], double walks[], double strikeOuts[], double hitByPitchs[], double battingAverage[], double onBasePercent[]){
    for(long unsigned int i=0;i<names.size();i++){
        cout<<names.at(i)<<endl;
        cout<<"BA: "<<fixed<<setprecision(3)<<(round(battingAverage[i]*1000))/1000<<endl;
        cout<<"OB%: "<<fixed<<setprecision(3)<<(round(onBasePercent[i]*1000))/1000<<endl;
        cout<<"H: "<<static_cast<int>(hits[i])<<endl;
        cout<<"BB: "<<static_cast<int>(walks[i])<<endl;
        cout<<"K: "<<static_cast<int>(strikeOuts[i])<<endl;
        cout<<"HBP: "<<static_cast<int>(hitByPitchs[i])<<endl<<endl;
    }
}

//method to calculate both the names needed to be displayed and highest value to return
//resets both highestNames and highestVal variables each time
static double findLeaderVal(double stat[], vector<string> names, vector<string> &highestNames){
    //passing vector through because we don't know how many names there will be
    //by reference in order to manipulate the vector itself
    highestNames.clear();
    double highestVal = stat[0];
    highestNames.push_back(names.at(0));
    for(long unsigned int i=1;i<names.size();i++){
        //checks if numbers are the same with the last using threshold method 
        //and adds name if they are the same 
        if(fabs(stat[i]-highestVal)<epsilon){
            highestNames.push_back(names.at(i));
        }else if(stat[i]>highestVal){
            //if finds a higher value, resets highestNames
            //and adds the name associated with the index value
            //also sets highestVal to the value
            highestNames.clear();
            highestNames.push_back(names.at(i));
            highestVal=stat[i];
        }
    }
    return highestVal;
}
//same method as findLeaderVal but variable name highestVal switched out for lowestVal
//and else if statement changed to stat[i]<lowestVal rather than stat[i]>highestVal to look for the minimum value
static double findMinVal(double stat[], vector<string> names, vector<string> &highestNames){
    //passing vector through because we don't know how many names there will be
    //by reference in order to manipulate the vector itself
    highestNames.clear();
    double lowestVal = stat[0];
    highestNames.push_back(names.at(0));
    for(long unsigned int i=1;i<names.size();i++){
        //checks if numbers are the same with the last using threshold method 
        //and adds name if they are the same 
        if(fabs(stat[i]-lowestVal)<epsilon){
            highestNames.push_back(names.at(i));
        }else if(stat[i]<lowestVal){
            //if finds a lower value, resets highestNames
            //and adds the name associated with the index value
            //also sets lowestVal to the value
            highestNames.clear();
            highestNames.push_back(names.at(i));
            lowestVal=stat[i];
        }
    }
    return lowestVal;
}

//method to help make sure each leader is properly displayed
//if only one leader, just add space
//if multiple, if last leader then add only space otherwise add comma and space
static void printLeaders(vector<string> highestNames){
    if(highestNames.size()>1){
        for(long unsigned int j = 0; j<highestNames.size();j++){
            if(j==(highestNames.size()-1)){
                cout<<highestNames.at(j)<<" ";
            }else{
                cout<<highestNames.at(j)<<", ";
            }
        }
    }else{
        cout<<highestNames.at(0)<<" ";
    }
}

//method to display leader data to console
void displayLeaderData(vector<string> names, vector<string> highestNames, double hits[], double walks[], double strikeOuts[], double hitByPitchs[], double battingAverage[], double onBasePercent[]){

    cout<<"LEAGUE LEADERS"<<endl;
    //using double variable and findLeaderVal method to find the highest value and the names associated with them
    //leadingVal resets each time for each category and so does highestNames
    double leadingVal = findLeaderVal(battingAverage, names, highestNames);
    cout<<"BA: ";
    //method to display the leaders correctly with comma and spaces 
    printLeaders(highestNames);
    //rest of the text is displayed and formatted properly as it should be
    cout<<fixed<<setprecision(3)<<(round(leadingVal*1000))/1000<<endl;

    leadingVal = findLeaderVal(onBasePercent, names, highestNames);
    cout<<"OB%: ";
    printLeaders(highestNames);
    cout<<fixed<<setprecision(3)<<(round(leadingVal*1000))/1000<<endl;

    leadingVal = findLeaderVal(hits, names, highestNames);
    cout<<"H: ";
    printLeaders(highestNames);
    cout<<(int)leadingVal<<endl;

    leadingVal = findLeaderVal(walks, names, highestNames);
    cout<<"BB: ";
    printLeaders(highestNames);
    cout<<(int)leadingVal<<endl;
    
    //special method for calculating least strikeouts
    leadingVal = findMinVal(strikeOuts, names, highestNames);
    cout<<"K: ";
    printLeaders(highestNames);
    cout<<(int)leadingVal<<endl;

    leadingVal = findLeaderVal(hitByPitchs, names, highestNames);
    cout<<"HBP: ";
    printLeaders(highestNames);
    cout<<(int)leadingVal<<endl;

}

//main method where all the magic happens (methods are called and such)
int main(){
    //declaring vectors to count number of players and records and to count the number of ties/highest names
    //using vectors to mostly count the number of players and to make sure I iterate through the right amount of players in the arrays
    vector<string> highestNames, names, records;
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
        //reads each line into the same string and separates the name and record into two vectors using find and substr
        while(getline(statsFile, recordString)){
            long unsigned int index = recordString.find(' ');
            names.push_back(recordString.substr(0, index));
            records.push_back(recordString.substr(index+1, recordString.length()-(index+1)));
        }
    //returns 1/error if file was not able to be opened
    }else{
        cout << "There was an error trying to open "<<fileName<<".";
        return 1;
    }
    //closes the input file
    statsFile.close();

    //declaring all stat arrays to be size 30 and initialize all values to 0 to prevent overflow
    double hits[30]={0.0}, outs[30]={0.0}, strikeOuts[30]={0.0}, walks[30]={0.0}, hitByPitchs[30]={0.0}, sacrifices[30]={0.0}, battingAverage[30]={0.0}, onBasePercent[30]={0.0};

    //calculates each persons batting record, batting average, and on-base percent and stores it in the above arrays
    //iterates through for each player there is in the file and by the size of the vector
    for(unsigned int i=0;i<records.size();i++){
        //calls method to parse batting record data
        battingRecord(records.at(i), i, hits, outs, strikeOuts, walks, hitByPitchs, sacrifices);
        //declaring variables for denominators of BA and OB% to check for division by 0
        double baDenom = hits[i]+outs[i]+strikeOuts[i];
        double obDenom = hits[i]+outs[i]+hitByPitchs[i]+strikeOuts[i]+walks[i]+sacrifices[i]; //A plate appearance is any valid result
        //if statements to check if dividing by zero using threshold method
        if(fabs(baDenom-0.0)<epsilon){
            battingAverage[i]=0.0;
        }else{
            battingAverage[i]=hits[i]/baDenom;
        }
        if(fabs(obDenom-0.0)<epsilon){
            onBasePercent[i]=0.0;
        }else{
            onBasePercent[i]=(hits[i]+walks[i]+hitByPitchs[i])/obDenom;
        }
    }
    //calls the methods to output to the console the data
    //passes all the arrays and vectors needed to calculate leaders and display the data
    displayPlayerData(names, hits, walks, strikeOuts, hitByPitchs, battingAverage, onBasePercent);
    displayLeaderData(names, highestNames, hits, walks, strikeOuts, hitByPitchs, battingAverage, onBasePercent);
    return 0;
}