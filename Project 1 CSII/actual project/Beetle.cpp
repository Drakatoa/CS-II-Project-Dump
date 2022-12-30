//Rajit Goel CS 2337.002
//RXG210046
//vectors for keeping track of closest and farthest objects/walls
//inherits creature
#include <string>
#include <vector>
#include "Beetle.h"

//this method takes all the distances, number of adjacent ants, and codes and makes the beetle figure out where it wants to go
char Beetle::move(std::pair<int, int> distAndWallDistN, std::pair<int, int> distAndWallDistE, std::pair<int, int> distAndWallDistS, std::pair<int, int> distAndWallDistW, 
        std::pair<bool, int> codeAndAntsN, std::pair<bool, int> codeAndAntsE, std::pair<bool, int> codeAndAntsS, std::pair<bool, int> codeAndAntsW) const {
            
            //vectors for determining three cases, ants and nearest ants,
            //if multiple nearest ants, which has the most ant neighbours
            //if no ants, which is the farthest wall
            //vectors and pointers help sort through and keep track of which are the same and different
            std::vector<int*> areAnts;
            std::vector<int*> nearestAnts;
            std::vector<int*> antNeighbours;
            std::vector<int*> mostAntNeighbours;
            std::vector<int*> areWalls;
            std::vector<int*> farthestWalls;

            //using pointers in order to confirm that the two variables point to the same address distance/counter and returning respective character
            //initializing all pointers to ant distances
            int* codeNP = &distAndWallDistN.first; 
            int* codeEP = &distAndWallDistE.first; 
            int* codeSP = &distAndWallDistS.first; 
            int* codeWP = &distAndWallDistW.first;

            //initializing all pointers to adjacent ant neighbours
            int* adjAN = &codeAndAntsN.second; 
            int* adjAE = &codeAndAntsE.second; 
            int* adjAS = &codeAndAntsS.second; 
            int* adjAW = &codeAndAntsW.second;

            //initializing all pointers to wall distances
            int* wallDistN = &distAndWallDistN.second; 
            int* wallDistE = &distAndWallDistE.second; 
            int* wallDistS = &distAndWallDistS.second; 
            int* wallDistW = &distAndWallDistW.second;

            //if code saying that its a ant is true, add corresponding pointer to are ants vector
            if(codeAndAntsN.first){areAnts.push_back(codeNP);}
            if(codeAndAntsE.first){areAnts.push_back(codeEP);}
            if(codeAndAntsS.first){areAnts.push_back(codeSP);}
            if(codeAndAntsW.first){areAnts.push_back(codeWP);}

            //if there are no orthogonal ants
            //move towards farthest edge
            if(areAnts.size()==0){
                
                //adding all wall distance pointers to sort through it
                areWalls.push_back(wallDistN), areWalls.push_back(wallDistE), areWalls.push_back(wallDistS), areWalls.push_back(wallDistW);

                //adding first distance pointer to compare to
                farthestWalls.push_back(areWalls.at(0));

                //calculate farthest wall(s), and if there are multiple of them,
                //and stores it in a vector
                //iterates through all 4 wall distances  
                for(long unsigned int i=1;i<areWalls.size();i++){
                    //if the dereferenced distances are equal to each other
                    //add it to the vector of farthest walls
                    if(*areWalls.at(i)==*farthestWalls.at(0)){
                        farthestWalls.push_back(areWalls.at(i));
                    //else if the dereferenced distance of are walls at index value is more than current farthest wall value
                    //clear the vector and add the pointer to the vector
                    } else if(*areWalls.at(i)>*farthestWalls.at(0)){
                        farthestWalls.clear();
                        farthestWalls.push_back(areWalls.at(i));
                    }
                }

                //test case if only one wall is the farthest away, just move towards it
                //if the farthest wall in one direction, returns the direction towards it
                //otherwise returns don't move (if the vector and pointer point to the same thing, it returns it)
                if(farthestWalls.size()==1){
                    if(farthestWalls.at(0)==wallDistN){
                        return 'n';
                    } else if(farthestWalls.at(0)==wallDistE){
                        return 'e';
                    } else if(farthestWalls.at(0)==wallDistS){
                        return 's';
                    } else if(farthestWalls.at(0)==wallDistW){
                        return 'w';
                    } else {
                        return 't';
                    }
                //else if farthest walls if bigger than 1
                } else if(farthestWalls.size()>1){
                    //each for loop iterates through the size of farthest walls and takes
                    //north, east, south, west, priority and returns char to move towards based on if 
                    //the distance pointer and pointer in farthest walls point to the same thing
                    for(long unsigned int i=0;i<farthestWalls.size();i++){
                        if(farthestWalls.at(i)==wallDistN){
                            return 'n';
                        }
                    }
                    for(long unsigned int i=0;i<farthestWalls.size();i++){
                        if(farthestWalls.at(i)==wallDistE){
                            return 'e';
                        }
                    }
                    for(long unsigned int i=0;i<farthestWalls.size();i++){
                        if(farthestWalls.at(i)==wallDistS){
                            return 's';
                        }
                    }
                    for(long unsigned int i=0;i<farthestWalls.size();i++){
                        if(farthestWalls.at(i)==wallDistW){
                            return 'w';
                        }
                    }
                }
            }

            //test case if only one orthogonal ant, just move towards it
            //if an ant is in one direction, returns the direction towards it
            //otherwise returns don't move
            if(areAnts.size()==1){
                if(areAnts.at(0)==codeNP){
                    return 'n';
                } else if(areAnts.at(0)==codeEP){
                    return 'e';
                } else if(areAnts.at(0)==codeSP){
                    return 's';
                } else if(areAnts.at(0)==codeWP){
                    return 'w';
                } else {
                    return 't';
                }
            }

            //if more than one orthogonal ant exists, the rest of the code executes to go through cases
            //first we check if ants are near, and move towards the nearest ant
            //and then if that doesn't work, we check to move towards nearest ant with most ant neighbours
            //and if tied use NESW priority
            nearestAnts.push_back(areAnts.at(0));

            //same algorithm as discussed above with farthest walls except it does < (less than), instead of > (more than) for counting nearest ant(s)
            //calculates which ant(s) are the nearest and stores in a vector
            for(long unsigned int i=1;i<areAnts.size();i++){
                if(*areAnts.at(i)==*nearestAnts.at(0)){
                    nearestAnts.push_back(areAnts.at(i));
                } else if(*areAnts.at(i)<*nearestAnts.at(0)){
                    nearestAnts.clear();
                    nearestAnts.push_back(areAnts.at(i));
                }
            }

            //test case if only one nearest ant, just move it away from it
            //if the nearest ant is in one direction, returns the direction towards it
            //otherwise returns don't move (if the vector and pointer point to the same thing, it returns it)
            if(nearestAnts.size()==1){
                if(nearestAnts.at(0)==codeNP){
                    return 'n';
                } else if(nearestAnts.at(0)==codeEP){
                    return 'e';
                } else if(nearestAnts.at(0)==codeSP){
                    return 's';
                } else if(nearestAnts.at(0)==codeWP){
                    return 'w';
                } else {
                    return 't';
                }
            //else if nearest ants if bigger than 1
            } else if(nearestAnts.size()>1){
                //iterates through all the nearest ants, and if the pointers are equal, ant neighbours counter
                //is added to the vector
                for(long unsigned int i=0;i<nearestAnts.size();i++){
                    if(nearestAnts.at(i)==codeNP){
                        antNeighbours.push_back(adjAN);
                    } else if(nearestAnts.at(i)==codeEP){
                        antNeighbours.push_back(adjAE);
                    } else if(nearestAnts.at(i)==codeSP){
                        antNeighbours.push_back(adjAS);
                    } else if(nearestAnts.at(i)==codeWP){
                        antNeighbours.push_back(adjAW);
                    } 
                }

                //same algorithm as discussed above with farthest walls but with most ant neighbours ant(s)
                //calculates which ant(s) have the most ant neighbours and stores in a vector
                mostAntNeighbours.push_back(antNeighbours.at(0));
                for(long unsigned int i=1;i<antNeighbours.size();i++){
                    if(*antNeighbours.at(i)==*mostAntNeighbours.at(0)){
                        mostAntNeighbours.push_back(antNeighbours.at(i));
                    } else if(*antNeighbours.at(i)>*mostAntNeighbours.at(0)){
                        mostAntNeighbours.clear();
                        mostAntNeighbours.push_back(antNeighbours.at(i));
                    }
                }

                //test case if only one ant with most ant neighbours, just move towards it
                //if the one ant with most ant neighbours is in one direction, returns the direction towards it
                //otherwise returns don't move (if the vector and pointer point to the same thing, it returns it)
                if(mostAntNeighbours.size()==1){
                    if(mostAntNeighbours.at(0)==adjAN){
                        return 'n';
                    } else if(mostAntNeighbours.at(0)==adjAE){
                        return 'e';
                    } else if(mostAntNeighbours.at(0)==adjAS){
                        return 's';
                    } else if(mostAntNeighbours.at(0)==adjAW){
                        return 'w';
                    } else {
                        return 't';
                    }
                //else if ants with most ant neighbours if bigger than 1
                } else if(mostAntNeighbours.size()>1){
                    //each for loop iterates through the size of most ant neighbors and takes
                    //north, east, south, west, priority and returns char to move towards based on if 
                    //the distance pointer and pointer in most ant neighbors point to the same thing
                    for(long unsigned int i=0;i<mostAntNeighbours.size();i++){
                        if(mostAntNeighbours.at(i)==adjAN){
                            return 'n';
                        }
                    }
                    for(long unsigned int i=0;i<mostAntNeighbours.size();i++){
                        if(mostAntNeighbours.at(i)==adjAE){
                            return 'e';
                        }
                    }
                    for(long unsigned int i=0;i<mostAntNeighbours.size();i++){
                        if(mostAntNeighbours.at(i)==adjAS){
                            return 's';
                        }
                    }
                    for(long unsigned int i=0;i<mostAntNeighbours.size();i++){
                        if(mostAntNeighbours.at(i)==adjAW){
                            return 'w';
                        }
                    }
                }
            }
            //needed return value at end of function
            return 't';
        }

//this function makes the actual breeding decision the beetle has to make if multiple directions are open
char Beetle::breed(bool nOpen, bool eOpen, bool sOpen, bool wOpen) const {
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