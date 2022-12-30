//Rajit Goel CS 2337.002
//RXG210046
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <math.h>

using namespace std;

// vector<string> highestNames, names, records;
double hits[30], outs[30], strikeOuts[30], walks[30], hitByPitchs[30], sacrifices[30], battingAverage[30], onBasePercent[30];
float epsilon = 0.0001f;

void battingRecord(string wholeRecord, int i){
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

void displayPlayerData(vector<string> names){
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

static double findLeaderVal(double stat[], vector<string> names, vector<string> &highestNames){
    //array list needed because we don't know how many names there will be
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

static double findMinVal(double stat[], vector<string> names, vector<string> &highestNames){
    //array list needed because we don't know how many names there will be
    highestNames.clear();
    double lowestVal = stat[0];
    highestNames.push_back(names.at(0));
    for(long unsigned int i=1;i<names.size();i++){
        //checks if numbers are the same with the last using threshold method 
        //and adds name if they are the same 
        if(fabs(stat[i]-lowestVal)<epsilon){
            highestNames.push_back(names.at(i));
        }else if(stat[i]<lowestVal){
            //if finds a higher value, resets highestNames
            //and adds the name associated with the index value
            //also sets highestVal to the value
            highestNames.clear();
            highestNames.push_back(names.at(i));
            lowestVal=stat[i];
        }
    }
    return lowestVal;
}

static void displayLeaders(vector<string> highestNames){
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

void displayLeaderData(vector<string> names, vector<string> highestNames){

    cout<<"LEAGUE LEADERS"<<endl;

    double leadingVal = findLeaderVal(battingAverage, names, highestNames);
    cout<<"BA: ";
    displayLeaders(highestNames);
    cout<<fixed<<setprecision(3)<<(round(leadingVal*1000))/1000<<endl;

    leadingVal = findLeaderVal(onBasePercent, names, highestNames);
    cout<<"OB%: ";
    displayLeaders(highestNames);
    cout<<fixed<<setprecision(3)<<(round(leadingVal*1000))/1000<<endl;

    leadingVal = findLeaderVal(hits, names, highestNames);
    cout<<"H: ";
    displayLeaders(highestNames);
    cout<<(int)leadingVal<<endl;

    leadingVal = findLeaderVal(walks, names, highestNames);
    cout<<"BB: ";
    displayLeaders(highestNames);
    cout<<(int)leadingVal<<endl;
    
    //special helper method for least strikeouts
    leadingVal = findMinVal(strikeOuts, names, highestNames);
    cout<<"K: ";
    displayLeaders(highestNames);
    cout<<(int)leadingVal<<endl;

    leadingVal = findLeaderVal(hitByPitchs, names, highestNames);
    cout<<"HBP: ";
    displayLeaders(highestNames);
    cout<<(int)leadingVal<<endl;

}

int main(){
    vector<string> highestNames, names, records;
    string fileName;
    cout<<"Enter file name: ";
    getline(cin, fileName);
    cout<<endl;
    ifstream statsFile (fileName);
    string recordString;
    if(statsFile.is_open()){
        while(getline(statsFile, recordString)){
            long unsigned int index = recordString.find(' ');
            names.push_back(recordString.substr(0, index));
            records.push_back(recordString.substr(index+1, recordString.length()-(index+1)));
        }
    } else {
        cout << "There was an error trying to open "<<fileName<<".";
        return 1;
    }
    statsFile.close();

    for(unsigned int i=0;i<records.size();i++){
        //calls method to parse batting record data
        battingRecord(records.at(i), i);
        //declaring variables for denominators of BA and OB% to check for division by 0
        double baDenom = hits[i]+outs[i]+strikeOuts[i];
        double obDenom = hits[i]+outs[i]+hitByPitchs[i]+strikeOuts[i]+walks[i]+sacrifices[i]; //A plate appearance is any valid result
        //if statements to check if dividing by zero using threshold method
        if(fabs(baDenom-0.0)<epsilon){
            battingAverage[i]=0.0;
        } else {
            battingAverage[i]=hits[i]/baDenom;
        }
        if(fabs(obDenom-0.0)<epsilon){
            onBasePercent[i]=0.0;
        } else {
            onBasePercent[i]=(hits[i]+walks[i]+hitByPitchs[i])/obDenom;
        }
    }
    displayPlayerData(names);
    displayLeaderData(names, highestNames);
    return 0;
}