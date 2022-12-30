//Rajit Goel CS 2337.002
//RXG210046
//vectors for keeping track of closest and farthest objects/walls
#include <string>
#include <vector>
#include "Ant.h"

//this method takes all the distances and codes and makes the ant figure out where it wants to go
char Ant::move(std::pair<int, int> distAndWallDistN, std::pair<int, int> distAndWallDistE, std::pair<int, int> distAndWallDistS, std::pair<int, int> distAndWallDistW, 
        std::pair<bool, int> codeAndAntsN, std::pair<bool, int> codeAndAntsE, std::pair<bool, int> codeAndAntsS, std::pair<bool, int> codeAndAntsW) const {
            //vector to sort through which are beetles and which are not
            std::vector<int*> areBeetles;
            std::vector<int*> noBeetles;
            //using pointers in order to confirm that the two variables point to the same address distance and returning respective character
            int* codeNP = &distAndWallDistN.first; 
            int* codeEP = &distAndWallDistE.first; 
            int* codeSP = &distAndWallDistS.first; 
            int* codeWP = &distAndWallDistW.first;
            //if code saying that its a beetle is true, add corresponding pointer to are beetles vector,
            //otherwise add it to no beetles vector
            if(codeAndAntsN.first){areBeetles.push_back(codeNP);} else{noBeetles.push_back(codeNP);}
            if(codeAndAntsE.first){areBeetles.push_back(codeEP);} else{noBeetles.push_back(codeEP);}
            if(codeAndAntsS.first){areBeetles.push_back(codeSP);} else{noBeetles.push_back(codeSP);}
            if(codeAndAntsW.first){areBeetles.push_back(codeWP);} else{noBeetles.push_back(codeWP);}

            //test case if no orthogonal beetles
            if(areBeetles.size()==0){
                return 't';
            }
            //test case if only one orthogonal beetle, just move away from it
            //if a beetle is in one direction, returns the direction opposite from it
            //otherwise returns don't move
            if(areBeetles.size()==1){
                if(areBeetles.at(0)==codeNP){
                    return 's';
                } else if(areBeetles.at(0)==codeEP){
                    return 'w';
                } else if(areBeetles.at(0)==codeSP){
                    return 'n';
                } else if(areBeetles.at(0)==codeWP){
                    return 'e';
                } else {
                    return 't';
                }
            }

            //if more than one orthogonal beetle exists, the rest of the code executes to go through cases
            //first we check if beetles are near, and move away from nearest beetle
            //and then if that doesn't work, we check to move to no beetles in that direction, using NESW priority if tied
            //then farthest beetles is the last option if nothing else, where ant will move to farthest beetle, using NESW priority if tied
            std::vector<int*> nearestBeetles;
            std::vector<int*> farthestBeetles;
            nearestBeetles.push_back(areBeetles.at(0));
            farthestBeetles.push_back(areBeetles.at(0));

            //calculate nearest beetle(s), and if there are multiple of them,
            //and stores it in a vector
            //iterates through whichever are beetles
            for(long unsigned int i=1;i<areBeetles.size();i++){
                //if the dereferenced distances are equal to each other
                //add it to the vector
                if(*areBeetles.at(i)==*nearestBeetles.at(0)){
                    nearestBeetles.push_back(areBeetles.at(i));
                //else if the dereferenced distance of arebeetle at index value is less than current nearest beetle value
                //clear the vector and add the pointer to the vector
                } else if(*areBeetles.at(i)<*nearestBeetles.at(0)){
                    nearestBeetles.clear();
                    nearestBeetles.push_back(areBeetles.at(i));
                }
            }
            
            //same as above except calculates greatest/farthest distance beetle(s) and stores it in a vector using > (more than), instead of < (less than)
            for(long unsigned int i=1;i<areBeetles.size();i++){
                if(*areBeetles.at(i)==*farthestBeetles.at(0)){
                    farthestBeetles.push_back(areBeetles.at(i));
                } else if(*areBeetles.at(i)>*farthestBeetles.at(0)){
                    farthestBeetles.clear();
                    farthestBeetles.push_back(areBeetles.at(i));
                }
            }

            //test case if only one beetle is near, just move away from it
            //if the nearest beetle is in one direction, returns the direction opposite from it
            //otherwise returns don't move (if the vector and pointer point to the same thing, it returns it)
            if(nearestBeetles.size()==1){
                if(nearestBeetles.at(0)==codeNP){
                    return 's';
                } else if(nearestBeetles.at(0)==codeEP){
                    return 'w';
                } else if(nearestBeetles.at(0)==codeSP){
                    return 'n';
                } else if(nearestBeetles.at(0)==codeWP){
                    return 'e';
                } else {
                    return 't';
                }
            //else if nearest beetles if bigger than 1
            } else if(nearestBeetles.size()>1){
                //if there are directions with no beetles
                if(noBeetles.size()!=0){
                    //each for loop iterates through the size of no beetles and takes
                    //north, east, south, west, priority and returns char to move towards based on if 
                    //the distance pointer and pointer in no beetles point to the same thing
                    for(long unsigned int i=0;i<noBeetles.size();i++){
                        if(noBeetles.at(i)==codeNP){
                            return 'n';
                        }
                    }
                    for(long unsigned int i=0;i<noBeetles.size();i++){
                        if(noBeetles.at(i)==codeEP){
                            return 'e';
                        }
                    }
                    for(long unsigned int i=0;i<noBeetles.size();i++){
                        if(noBeetles.at(i)==codeSP){
                            return 's';
                        }
                    }
                    for(long unsigned int i=0;i<noBeetles.size();i++){
                        if(noBeetles.at(i)==codeWP){
                            return 'w';
                        }
                    }
                //else if there are directions with only farther beetles
                } else if(farthestBeetles.size()!=0){
                    //each for loop iterates through the size of farthest beetles and takes
                    //north, east, south, west, priority and returns char to move towards based on if 
                    //the distance pointer and pointer in farthest beetles point to the same thing
                    for(long unsigned int i=0;i<farthestBeetles.size();i++){
                        if(farthestBeetles.at(i)==codeNP){
                            return 'n';
                        }
                    }
                    for(long unsigned int i=0;i<farthestBeetles.size();i++){
                        if(farthestBeetles.at(i)==codeEP){
                            return 'e';
                        }
                    }
                    for(long unsigned int i=0;i<farthestBeetles.size();i++){
                        if(farthestBeetles.at(i)==codeSP){
                            return 's';
                        }
                    }
                    for(long unsigned int i=0;i<farthestBeetles.size();i++){
                        if(farthestBeetles.at(i)==codeWP){
                            return 'w';
                        }
                    }
                    //otherwise return don't move
                } else {
                    return 't';
                }
                
            }
            //needed return value at end of function
            return 't'; 
        }

//this function makes the actual breeding decision the ant has to make if multiple directions are open
char Ant::breed(bool nOpen, bool eOpen, bool sOpen, bool wOpen) const {
    //simple if this direction open return that direction
    //else if this direction open, etc.; goes by north east south west priority
    //otherwise if nothing is open return don't move
    if(nOpen){
        return 'n';
    }else if(eOpen){
        return 'e';
    }else if(sOpen){
        return 's';
    }else if(wOpen){
        return 'w';
    }else{
        return 't';
    }
}