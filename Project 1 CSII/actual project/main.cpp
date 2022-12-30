//Rajit Goel CS 2337.002
//RXG210046

/*This program takes input from a 10x10 world file of creatures called Ants and Beetles.
The main class then gives information to the ants and beetles, and the beetles
and ants must decide what to do when given that information either move one cardinal
direction or stay each turn. The Ants and Beetles are AI that play against each other,
and they also breed and the beetles will starve if they don't feast on the ants.
The output of each turn is then displayed based on what happened that turn.*/

//iostream for input and output to console
//vectors for keeping track of closest and farthest objects/walls
//fstream for opening and taking input from a file
//including derived class files to use them
#include "Ant.h"
#include "Beetle.h"
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

//This function calculates how many adjacent ants there, intakes grid, and coordinates of ant being calculated
//Called in the calculate distances method to pass in adjacent ants for each direction if there is an ant there
//takes the coordinates of the ant detected and returns an int for the adjacent ants
int calcAdjAnts(Creature*** gameGrid, int j, int i){
    int counter = 0;
    //all if loops check for edge cases where coordinates may be 0 or 9, otherwise accesses outside the array
    if(j!=0){
        if(dynamic_cast<Ant*>(gameGrid[j-1][i])){counter++;}
        if(i!=9){
            if(dynamic_cast<Ant*>(gameGrid[j-1][i+1])){counter++;}
        }
        if(i!=0){
            if(dynamic_cast<Ant*>(gameGrid[j-1][i-1])){counter++;}
        }
    }
    if(j!=9){
        if(dynamic_cast<Ant*>(gameGrid[j+1][i])){counter++;}
        if(i!=9){
            if(dynamic_cast<Ant*>(gameGrid[j+1][i+1])){counter++;}
        }
        if(i!=0){
            if(dynamic_cast<Ant*>(gameGrid[j+1][i-1])){counter++;}
        }
    }
    if(i!=9){
        if(dynamic_cast<Ant*>(gameGrid[j][i+1])){counter++;}
    }
    if(i!=0){
        if(dynamic_cast<Ant*>(gameGrid[j][i-1])){counter++;}
    }
    //returns how many ants counted
    return counter;
}

//this function calculates all the distances needed to pass into both functions, takes all dists, adjacent ant counters, and booleans as references 
//and whether its an object they need or not (beetles look for ants to go towards, and ants look for beetles to run away from)
//passes values from turn as reference so they can be used later in the turn function
void calculateDist(Creature*** gameGrid, int j, int i, int &nDist, int &eDist, int &sDist, int &wDist, bool &nCode, bool &eCode, bool &sCode, bool &wCode, int &nAdjAnts, int &eAdjAnts, int &sAdjAnts, int &wAdjAnts){
    
    //north vars calculations
    //edge case for northern wall, can't go up
    if(j==0){
        nDist=0;
        nCode=false;
    }else{
        //iterates through and increases distance up until desired object is found or a wall is hit
        //original coordinate minus distance travelled is set for northern and whether it was the desired object or not
        for(int k=1;k<j+1;k++){
            //if original object was a beetle, ignore everything and look for ant, and if ant set north dists and code to respective distance
            if(dynamic_cast<Beetle*>(gameGrid[j][i])){
                if(gameGrid[j-k][i]==nullptr){
                    continue;
                }else if(dynamic_cast<Beetle*>(gameGrid[j-k][i])){
                    continue;
                }else if(dynamic_cast<Ant*>(gameGrid[j-k][i])){
                    nDist=k;
                    nCode=true;
                    //if beetle found an ant, calls adj ants calc function to set adjacent ants north to the value returned by the function
                    nAdjAnts = calcAdjAnts(gameGrid, j-k, i);
                    break;
                }
            //if original object was an ant, ignore everything and look for beetle, and if ant set north dists and code to respective distance
            } else if(dynamic_cast<Ant*>(gameGrid[j][i])){
                if(gameGrid[j-k][i]==nullptr){
                    continue;
                }else if(dynamic_cast<Ant*>(gameGrid[j-k][i])){
                    continue;
                }else if(dynamic_cast<Beetle*>(gameGrid[j-k][i])){
                    nDist=k;
                    nCode=true;
                    break;
                }
            }
            //if reaches end of for loop and the right object isn't there distance is set and classified as a wall
            if(j==k){
                nDist=k;
                nCode=false;
                break;
            }
        }
    }

    //east vars calculations
    //edge case for east wall, can't go right
    if(i==9){
            eDist=0;
            eCode=false;
    }else{
        //iterates through and increases distance right until desired object is found or a wall is hit
        //distance travelled is set for eastern and whether it was the desired object or not
        for(int l=i+1;l<10;l++){
            //if original object was a beetle, ignore everything and look for ant, and if ant set east dists and code to respective distance
            if(dynamic_cast<Beetle*>(gameGrid[j][i])){
                if(gameGrid[j][l]==nullptr){
                    continue;
                }else if(dynamic_cast<Beetle*>(gameGrid[j][l])){
                    continue;
                } else if(dynamic_cast<Ant*>(gameGrid[j][l])){
                    eDist=l-i;
                    eCode=true;
                    //if beetle found an ant, calls adj ants calc function to set adjacent ants east to the value returned by the function
                    eAdjAnts = calcAdjAnts(gameGrid, j, l);
                    break;
                }
            //if original object was an ant, ignore everything and look for beetle, and if ant set east dists and code to respective distance
            } else if(dynamic_cast<Ant*>(gameGrid[j][i])){
                if(gameGrid[j][l]==nullptr){
                    continue;
                }else if(dynamic_cast<Ant*>(gameGrid[j][l])){
                    continue;
                } else if(dynamic_cast<Beetle*>(gameGrid[j][l])){
                    eDist=l-i;
                    eCode=true;
                    break;
                }
            }
            //if reaches end of for loop and the right object isn't there distance is set and classified as a wall
            if(l==9){
                eDist=l-i;
                eCode=false;
                break;
            }
        }
    }

    //south vars calculations
    //edge case for south wall, can't go down
    if(j==9){
        sDist=0;
        sCode=false;
    }else{
        //iterates through and increases distance down until desired object is found or a wall is hit
        //distance travelled is set for southern and whether it was the desired object or not
        for(int m=j+1;m<10;m++){
            //if original object was a beetle, ignore everything and look for ant, and if ant set south dists and code to respective distance
            if(dynamic_cast<Beetle*>(gameGrid[j][i])){
                if(gameGrid[m][i]==nullptr){
                    continue;
                }else if(dynamic_cast<Beetle*>(gameGrid[m][i])){
                    continue;
                }else if(dynamic_cast<Ant*>(gameGrid[m][i])){
                    sDist=m-j;
                    sCode=true;
                    //if beetle found an ant, calls adj ants calc function to set adjacent ants south to the value returned by the function
                    sAdjAnts = calcAdjAnts(gameGrid, m, i);
                    break;
                }
            //if original object was an ant, ignore everything and look for beetle, and if ant set south dists and code to respective distance
            } else if(dynamic_cast<Ant*>(gameGrid[j][i])){
                if(gameGrid[m][i]==nullptr){
                    continue;
                }else if(dynamic_cast<Ant*>(gameGrid[m][i])){
                    continue;
                }else if(dynamic_cast<Beetle*>(gameGrid[m][i])){
                    sDist=m-j;
                    sCode=true;
                    break;
                }
            }
            //if reaches end of for loop and the right object isn't there distance is set and classified as a wall
            if(m==9){
                sDist=m-j;
                sCode=false;
                break;
            }
        }
    }
    
    //west vars calculations
    //edge case for west wall, can't go left
    if(i==0){
            wDist=0;
            wCode=false;
    }else{
        //iterates through and increases distance down until desired object is found or a wall is hit
        //distance travelled is set for western and whether it was the desired object or not
        for(int n=1;n<i+1;n++){
            //if original object was a beetle, ignore everything and look for ant, and if ant set west dists and code to respective distance
            if(dynamic_cast<Beetle*>(gameGrid[j][i])){
                if(gameGrid[j][i-n]==nullptr){
                    continue;
                }else if(dynamic_cast<Beetle*>(gameGrid[j][i-n])){
                    continue;
                } else if(dynamic_cast<Ant*>(gameGrid[j][i-n])){
                    wDist=n;
                    wCode=true;
                    //if beetle found an ant, calls adj ants calc function to set adjacent ants west to the value returned by the function
                    wAdjAnts = calcAdjAnts(gameGrid, j, i-n);
                    break;
                }
            //if original object was an ant, ignore everything and look for beetle, and if ant set west dists and code to respective distance
            } else if(dynamic_cast<Ant*>(gameGrid[j][i])){
                if(gameGrid[j][i-n]==nullptr){
                    continue;
                }else if(dynamic_cast<Ant*>(gameGrid[j][i-n])){
                    continue;
                } else if(dynamic_cast<Beetle*>(gameGrid[j][i-n])){
                    wDist=n;
                    wCode=true;
                    break;
                }
            }
            //if reaches end of for loop and the right object isn't there distance is set and classified as a wall
            if(i==n){
                wDist=n;
                wCode=false;
                break;
            } 
        }
    }
}

//this function updates all parameters for the creature object if they are not able to move/don't need to move, intakes grid and coordinates
//called in movingmodifyarray, where main decides whether or not to move the creature to their desired direction
//if 't', default, or function decides that creature cannot move there, this function is called to update their parameter
void generalIncreaseTurn(Creature*** gameGrid, int j, int i){
    //if beetle, increase the beetles starve timer, its turn counter, and set its breeding status to false
    if(dynamic_cast<Beetle*>(gameGrid[j][i])){
        (dynamic_cast<Beetle*>(gameGrid[j][i]))->increaseTurn();
        (dynamic_cast<Beetle*>(gameGrid[j][i]))->increaseStarve();
        dynamic_cast<Beetle*>(gameGrid[j][i])->changeBreedStatus(false);
    } else if(dynamic_cast<Ant*>(gameGrid[j][i])){
        //if ant, increase its turn counter and set its breeding status to false
        (dynamic_cast<Ant*>(gameGrid[j][i]))->increaseTurn();
        dynamic_cast<Ant*>(gameGrid[j][i])->changeBreedStatus(false);
    }
}

//this function modifies the array by intaking the array, coordinates and the desired character to move to
//and makes all corresponding changes to creature's parameters as needed, as well as setting array values to null pointers
//and setting the pointer to point to that original object
//we set breeding status to false here because in the turn method, they become true and get checked so that they don't breed multiple times in a turn
//we also increase turn, so that when iterating through the loop, they get checked if their turn member variable is equal to the turn in the game or not,
//so that they don't move multiple times in a row
//we also increase starve timers if the beetles don't eat an ant, so that if they don't eat an ant in 5 turns they die
//reset starve timers if they eat an ant
void movingModifyArray(Creature*** gameGrid, int j, int i, char whereToMove){
    //switch statement to deal with which direction the creature wishes to go
    switch (whereToMove){
        case 'n': 
            //edge case if j is 0 and north is called
            if(j-1<0){
                generalIncreaseTurn(gameGrid, j, i);
                break;
            }
            //if beetle at coordinate
            if(dynamic_cast<Beetle*>(gameGrid[j][i])){
                //if space is open, no creature on it, set north space to point to old object
                //set original coordinate to nullptr
                //update parameters accordingly, bc empty, increase starve timer, increase turn counter, and change breeding status to false
                if(gameGrid[j-1][i]==nullptr){
                    gameGrid[j-1][i]=gameGrid[j][i];
                    gameGrid[j][i]=nullptr;
                    (dynamic_cast<Beetle*>(gameGrid[j-1][i]))->increaseTurn();
                    (dynamic_cast<Beetle*>(gameGrid[j-1][i]))->increaseStarve();
                    dynamic_cast<Beetle*>(gameGrid[j-1][i])->changeBreedStatus(false);
                    break;
                //if space is occupied by ant, set north space to point to old object
                //set original coordinate to nullptr
                //update parameters accordingly, bc has ant, reset starve timer, increase turn counter, and change breeding status to false
                }else if(dynamic_cast<Ant*>(gameGrid[j-1][i])){
                    gameGrid[j-1][i]=gameGrid[j][i];
                    gameGrid[j][i]=nullptr;
                    (dynamic_cast<Beetle*>(gameGrid[j-1][i]))->increaseTurn();
                    (dynamic_cast<Beetle*>(gameGrid[j-1][i]))->resetStarve();
                    dynamic_cast<Beetle*>(gameGrid[j-1][i])->changeBreedStatus(false);
                    break;
                //if space is beetle, call generalIncreaseTurn, so parameters get updated and they don't go anywhere
                }else{
                    generalIncreaseTurn(gameGrid, j, i);
                    break;
                }
            //if ant at coordinate
            } else if(dynamic_cast<Ant*>(gameGrid[j][i])){
                //if space is open, no creature on it, set north space to point to old object
                //set original coordinate to nullptr
                //update parameters accordingly, increase turn counter and change breeding status to false
                if(gameGrid[j-1][i]==nullptr){
                    gameGrid[j-1][i]=gameGrid[j][i];
                    gameGrid[j][i]=nullptr;
                    (dynamic_cast<Ant*>(gameGrid[j-1][i]))->increaseTurn();
                    dynamic_cast<Ant*>(gameGrid[j-1][i])->changeBreedStatus(false);
                    break;
                //if space is any type of creature, call generalIncreaseTurn, so parameters get updated and they don't go anywhere
                }else{
                    generalIncreaseTurn(gameGrid, j, i);
                    break;
                }
            } 
            break;
        case 'e': 
            //edge case if i is 9 and east is called
            if(i+1>9){
                generalIncreaseTurn(gameGrid, j, i);
                break;
            }
            //if beetle at coordinate
            if(dynamic_cast<Beetle*>(gameGrid[j][i])){
                //if space is open, no creature on it, set east space to point to old object
                //set original coordinate to nullptr
                //update parameters accordingly, bc empty, increase starve timer, increase turn counter, and change breeding status to false
                if(gameGrid[j][i+1]==nullptr){
                    gameGrid[j][i+1]=gameGrid[j][i];
                    gameGrid[j][i]=nullptr;
                    (dynamic_cast<Beetle*>(gameGrid[j][i+1]))->increaseTurn();
                    (dynamic_cast<Beetle*>(gameGrid[j][i+1]))->increaseStarve();
                    dynamic_cast<Beetle*>(gameGrid[j][i+1])->changeBreedStatus(false);
                    break;
                //if space is occupied by ant, set east space to point to old object
                //set original coordinate to nullptr
                //update parameters accordingly, bc has ant, reset starve timer, increase turn counter, and change breeding status to false
                }else if(dynamic_cast<Ant*>(gameGrid[j][i+1])){
                    gameGrid[j][i+1]=gameGrid[j][i];
                    gameGrid[j][i]=nullptr;
                    (dynamic_cast<Beetle*>(gameGrid[j][i+1]))->increaseTurn();
                    (dynamic_cast<Beetle*>(gameGrid[j][i+1]))->resetStarve();
                    dynamic_cast<Beetle*>(gameGrid[j][i+1])->changeBreedStatus(false);
                    break;
                //if space is beetle, call generalIncreaseTurn, so parameters get updated and they don't go anywhere
                }else{
                    generalIncreaseTurn(gameGrid, j, i);
                    break;
                }
            //if ant at coordinate
            } else if(dynamic_cast<Ant*>(gameGrid[j][i])){
                //if space is open, no creature on it, set east space to point to old object
                //set original coordinate to nullptr
                //update parameters accordingly, increase turn counter and change breeding status to false
                if(gameGrid[j][i+1]==nullptr){
                    gameGrid[j][i+1]=gameGrid[j][i];
                    gameGrid[j][i]=nullptr;
                    (dynamic_cast<Ant*>(gameGrid[j][i+1]))->increaseTurn();
                    dynamic_cast<Ant*>(gameGrid[j][i+1])->changeBreedStatus(false);
                    break;
                //if space is any type of creature, call generalIncreaseTurn, so parameters get updated and they don't go anywhere
                }else{
                    generalIncreaseTurn(gameGrid, j, i);
                    break;
                }
            } 
            break;
        case 's': 
            //edge case if j is 9 and south is called
            if(j+1>9){
                generalIncreaseTurn(gameGrid, j, i);
                break;
            }
            //if beetle at coordinate
            if(dynamic_cast<Beetle*>(gameGrid[j][i])){
                //if space is open, no creature on it, set south space to point to old object
                //set original coordinate to nullptr
                //update parameters accordingly, bc empty, increase starve timer, increase turn counter, and change breeding status to false
                if(gameGrid[j+1][i]==nullptr){
                    gameGrid[j+1][i]=gameGrid[j][i];
                    gameGrid[j][i]=nullptr;
                    (dynamic_cast<Beetle*>(gameGrid[j+1][i]))->increaseTurn();
                    (dynamic_cast<Beetle*>(gameGrid[j+1][i]))->increaseStarve();
                    dynamic_cast<Beetle*>(gameGrid[j+1][i])->changeBreedStatus(false);
                    break;
                //if space is occupied by ant, set south space to point to old object
                //set original coordinate to nullptr
                //update parameters accordingly, bc has ant, reset starve timer, increase turn counter, and change breeding status to false
                }else if(dynamic_cast<Ant*>(gameGrid[j+1][i])){
                    gameGrid[j+1][i]=gameGrid[j][i];
                    gameGrid[j][i]=nullptr;
                    (dynamic_cast<Beetle*>(gameGrid[j+1][i]))->increaseTurn();
                    (dynamic_cast<Beetle*>(gameGrid[j+1][i]))->resetStarve();
                    dynamic_cast<Beetle*>(gameGrid[j+1][i])->changeBreedStatus(false);
                    break;
                //if space is beetle, call generalIncreaseTurn, so parameters get updated and they don't go anywhere
                }else{
                    generalIncreaseTurn(gameGrid, j, i);
                    break;
                }
            //if ant at coordinate
            } else if(dynamic_cast<Ant*>(gameGrid[j][i])){
                //if space is open, no creature on it, set south space to point to old object
                //set original coordinate to nullptr
                //update parameters accordingly, increase turn counter and change breeding status to false
                if(gameGrid[j+1][i]==nullptr){
                    gameGrid[j+1][i]=gameGrid[j][i];
                    gameGrid[j][i]=nullptr;
                    (dynamic_cast<Ant*>(gameGrid[j+1][i]))->increaseTurn();
                    dynamic_cast<Ant*>(gameGrid[j+1][i])->changeBreedStatus(false);
                    break;
                //if space is any type of creature, call generalIncreaseTurn, so parameters get updated and they don't go anywhere
                }else{
                    generalIncreaseTurn(gameGrid, j, i);
                    break;
                }
            } 
            break;
        case 'w': 
            //edge case if j is 9 and south is called
            if(i-1<0){
                generalIncreaseTurn(gameGrid, j, i);
                break;
            }
            //if beetle at coordinate
            if(dynamic_cast<Beetle*>(gameGrid[j][i])){
                //if space is open, no creature on it, set west space to point to old object
                //set original coordinate to nullptr
                //update parameters accordingly, bc empty, increase starve timer, increase turn counter, and change breeding status to false
                if(gameGrid[j][i-1]==nullptr){
                    gameGrid[j][i-1]=gameGrid[j][i];
                    gameGrid[j][i]=nullptr;
                    (dynamic_cast<Beetle*>(gameGrid[j][i-1]))->increaseTurn();
                    (dynamic_cast<Beetle*>(gameGrid[j][i-1]))->increaseStarve();
                    dynamic_cast<Beetle*>(gameGrid[j][i-1])->changeBreedStatus(false);
                    break;
                //if space is occupied by ant, set west space to point to old object
                //set original coordinate to nullptr
                //update parameters accordingly, bc has ant, reset starve timer, increase turn counter, and change breeding status to false
                }else if(dynamic_cast<Ant*>(gameGrid[j][i-1])){
                    gameGrid[j][i-1]=gameGrid[j][i];
                    gameGrid[j][i]=nullptr;
                    (dynamic_cast<Beetle*>(gameGrid[j][i-1]))->increaseTurn();
                    (dynamic_cast<Beetle*>(gameGrid[j][i-1]))->resetStarve();
                    dynamic_cast<Beetle*>(gameGrid[j][i-1])->changeBreedStatus(false);
                    break;
                //if space is beetle, call generalIncreaseTurn, so parameters get updated and they don't go anywhere
                }else{
                    generalIncreaseTurn(gameGrid, j, i);
                    break;
                }
            //if ant at coordinate
            } else if(dynamic_cast<Ant*>(gameGrid[j][i])){
                //if space is open, no creature on it, set west space to point to old object
                //set original coordinate to nullptr
                //update parameters accordingly, increase turn counter and change breeding status to false
                if(gameGrid[j][i-1]==nullptr){
                    gameGrid[j][i-1]=gameGrid[j][i];
                    gameGrid[j][i]=nullptr;
                    (dynamic_cast<Ant*>(gameGrid[j][i-1]))->increaseTurn();
                    dynamic_cast<Ant*>(gameGrid[j][i-1])->changeBreedStatus(false);
                    break;
                //if space is any type of creature, call generalIncreaseTurn, so parameters get updated and they don't go anywhere
                }else{
                    generalIncreaseTurn(gameGrid, j, i);
                    break;
                }
            } 
            break;
        //if creature can't go anywhere, call generalIncreaseTurn, so parameters get updated and they don't go anywhere
        case 't': 
            generalIncreaseTurn(gameGrid, j, i);
            break;
        //required default case
        default:
            generalIncreaseTurn(gameGrid, j, i);
            break;
    }
}

//this function modifies the array by intaking the array, and the desired character to breed to, as well as turn number, and coordinates
//and makes all corresponding changes to creature's parameters as needed, as well as setting array values to new Creature objects
//two switch statements, one for ants, one for beetles
//changes breed status to true so that they don't get repeating breeding throughout, and sets child/new creature to true to not repeat
//and sets turn to one ahead so that they are caught up for next turn
void breedingModifyArray(Creature*** gameGrid, int j, int i, char dirToBreed, int z){
    //if ant at coordinate
    if(dynamic_cast<Ant*>(gameGrid[j][i])){
        switch(dirToBreed){
            case 'n':
                //if north, east, south, or west, create new ant in respective direction
                //and change both breeding statuses to true, and new ant to turn+1
                (dynamic_cast<Ant*>(gameGrid[j][i]))->changeBreedStatus(true);
                gameGrid[j-1][i] = new Ant;
                (dynamic_cast<Ant*>(gameGrid[j-1][i]))->changeBreedStatus(true);
                (dynamic_cast<Ant*>(gameGrid[j-1][i]))->setTurn(z+1);
                break;
            case 'e':
                (dynamic_cast<Ant*>(gameGrid[j][i]))->changeBreedStatus(true);
                gameGrid[j][i+1] = new Ant;
                (dynamic_cast<Ant*>(gameGrid[j][i+1]))->changeBreedStatus(true);
                (dynamic_cast<Ant*>(gameGrid[j][i+1]))->setTurn(z+1);
                break;
            case 's':
                (dynamic_cast<Ant*>(gameGrid[j][i]))->changeBreedStatus(true);
                gameGrid[j+1][i] = new Ant;
                (dynamic_cast<Ant*>(gameGrid[j+1][i]))->changeBreedStatus(true);
                (dynamic_cast<Ant*>(gameGrid[j+1][i]))->setTurn(z+1);
                break;
            case 'w':
                (dynamic_cast<Ant*>(gameGrid[j][i]))->changeBreedStatus(true);
                gameGrid[j][i-1] = new Ant;
                (dynamic_cast<Ant*>(gameGrid[j][i-1]))->changeBreedStatus(true);
                (dynamic_cast<Ant*>(gameGrid[j][i-1]))->setTurn(z+1);
                break;
            case 't':
                //if can't breed in any direction, change breeding status to true and move on
                (dynamic_cast<Ant*>(gameGrid[j][i]))->changeBreedStatus(true);
                break;
            default:
                //required default case
                (dynamic_cast<Ant*>(gameGrid[j][i]))->changeBreedStatus(true);
                break;
        }
    //if beetle at coordinate
    } else if(dynamic_cast<Beetle*>(gameGrid[j][i])){
        switch(dirToBreed){
            case 'n':
                //if north, east, south, or west, create new ant in respective direction
                //and change both breeding statuses to true, and new beetle to turn+1
                (dynamic_cast<Beetle*>(gameGrid[j][i]))->changeBreedStatus(true);
                gameGrid[j-1][i] = new Beetle;
                (dynamic_cast<Beetle*>(gameGrid[j-1][i]))->changeBreedStatus(true);
                (dynamic_cast<Beetle*>(gameGrid[j-1][i]))->setTurn(z+1);
                break;
            case 'e':
                (dynamic_cast<Beetle*>(gameGrid[j][i]))->changeBreedStatus(true);
                gameGrid[j][i+1] = new Beetle;
                (dynamic_cast<Beetle*>(gameGrid[j][i+1]))->changeBreedStatus(true);
                (dynamic_cast<Beetle*>(gameGrid[j][i+1]))->setTurn(z+1);
                break;
            case 's':
                (dynamic_cast<Beetle*>(gameGrid[j][i]))->changeBreedStatus(true);
                gameGrid[j+1][i] = new Beetle;
                (dynamic_cast<Beetle*>(gameGrid[j+1][i]))->changeBreedStatus(true);
                (dynamic_cast<Beetle*>(gameGrid[j+1][i]))->setTurn(z+1);
                break;
            case 'w':
                (dynamic_cast<Beetle*>(gameGrid[j][i]))->changeBreedStatus(true);
                gameGrid[j][i-1] = new Beetle;
                (dynamic_cast<Beetle*>(gameGrid[j][i-1]))->changeBreedStatus(true);
                (dynamic_cast<Beetle*>(gameGrid[j][i-1]))->setTurn(z+1);
                break;
            case 't':
                //if can't breed in any direction, change breeding status to true and move on
                (dynamic_cast<Beetle*>(gameGrid[j][i]))->changeBreedStatus(true);
                break;
            default:
                //required default case
                (dynamic_cast<Beetle*>(gameGrid[j][i]))->changeBreedStatus(true);
                break;
        }
    }
}

//this function performs all the actions needed to be done in one turn, takes grid and turn number
//iterates and performs moving of beetles, then ants, then checks for starving beetles after turn 5,
//then checks for breeding ants every 3 turns and breeding beetles every 8 turns
void turn(int z, Creature*** gameGrid){
    //nested for loop to iterate through whole grid and move beetles as needed
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            //if coordinates points toward nullptr continue through loop
            if(gameGrid[j][i]==nullptr){
                continue;
            //if coordinates find beetle and beetle has not already taken a turn
            //make all required variables needed to pass through, distances to object location,
            //distances to each wall, how many ants surround the ant if object located is an ant,
            //and the code to whether the object is an ant or not
            }else if(dynamic_cast<Beetle*>(gameGrid[j][i])&&z==(dynamic_cast<Beetle*>(gameGrid[j][i]))->getTurn()){
                int nDist=0,eDist=0,sDist=0,wDist=0,
                nWall=j,eWall=9-i,sWall=9-j,wWall=i,
                nAdjAnts=0,eAdjAnts=0,sAdjAnts=0,wAdjAnts=0;

                bool nCode=false,eCode=false,sCode=false,wCode=false;
                
                //passes all variables except for distance to wall vars by reference to modify variables directly
                calculateDist(gameGrid, j, i, nDist, eDist, sDist, wDist, nCode, eCode, sCode, wCode, nAdjAnts, eAdjAnts, sAdjAnts, wAdjAnts);

                //creates pairs of values that are to be passed into move function for beetle, so beetle can decide where to go
                pair<int, int> distAndWallDistN(nDist, nWall), distAndWallDistE(eDist, eWall), distAndWallDistS(sDist, sWall), distAndWallDistW(wDist, wWall);
                pair<bool, int> codeAndAntsN(nCode, nAdjAnts), codeAndAntsE(eCode, eAdjAnts), codeAndAntsS(sCode, sAdjAnts), codeAndAntsW(wCode, wAdjAnts);

                //calls beetle move function, and returns a directional char of where it wants to go or if it wants to stay
                char whereToMove = gameGrid[j][i]->move(distAndWallDistN, distAndWallDistE, distAndWallDistS, distAndWallDistW, codeAndAntsN, codeAndAntsE, codeAndAntsS, codeAndAntsW);

                //uses char and grid to decides if the space requested by the beetle can be moved to or not and update the turn/breeding/starve timers and parameters
                movingModifyArray(gameGrid, j, i, whereToMove);

            }
        }
    }
    //nested for loop to iterate through whole grid and move ants as needed
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            //if coordinates points toward nullptr continue through loop
            if(gameGrid[j][i]==nullptr){
                continue;
            //if coordinates find ant and ant has not already taken a turn
            //make all required variables needed to pass through, distances to object location,
            //distances to walls and adjAnts isn't needed for ants, but I set them to the default values
            //and pass them anyway because it is required
            //and then the code to whether the object is an beetle or not
            }else if(dynamic_cast<Ant*>(gameGrid[j][i])&&z==(dynamic_cast<Ant*>(gameGrid[j][i]))->getTurn()){
                
                int nDist=0,eDist=0,sDist=0,wDist=0,
                nWall=j,eWall=9-i,sWall=9-j,wWall=i,
                nAdjAnts=0,eAdjAnts=0,sAdjAnts=0,wAdjAnts=0;
                
                bool nCode=false,eCode=false,sCode=false,wCode=false;

                //passes all variables except for distance to wall vars by reference to modify variables directly
                calculateDist(gameGrid, j, i, nDist, eDist, sDist, wDist, nCode, eCode, sCode, wCode, nAdjAnts, eAdjAnts, sAdjAnts, wAdjAnts);

                //creates pairs of values that are to be passed into move function for ant, so ant can decide where to go
                //the second value in each pair isn't needed for ant, but is needed for beetles
                pair<int, int> distAndWallDistN(nDist, nWall), distAndWallDistE(eDist, eWall), distAndWallDistS(sDist, sWall), distAndWallDistW(wDist, wWall);
                pair<bool, int> codeAndAntsN(nCode, nAdjAnts), codeAndAntsE(eCode, eAdjAnts), codeAndAntsS(sCode, sAdjAnts), codeAndAntsW(wCode, wAdjAnts);

                //calls ant move function, and returns a directional char of where it wants to go or if it wants to stay
                char whereToMove = gameGrid[j][i]->move(distAndWallDistN, distAndWallDistE, distAndWallDistS, distAndWallDistW, codeAndAntsN, codeAndAntsE, codeAndAntsS, codeAndAntsW);

                //uses char and grid to decides if the space requested by the ant can be moved to or not and update the turn/breeding timers and parameters
                movingModifyArray(gameGrid, j, i, whereToMove);
            }
        }
    }
    //once turn hits 5, every turn 5 and after, the loop iterates through, find beetles,
    //and if their starve timer is 5 or above, they die
    if(z>=5){
        for(int i=0;i<10;i++){
            for(int j=0;j<10;j++){
                //if coordinates empty, move on
                if(gameGrid[j][i]==nullptr){
                    continue;
                //if beetle found
                }else if(dynamic_cast<Beetle*>(gameGrid[j][i])){
                    //calls starve function, which returns a bool of whether or not their starve timer is 5 or above
                    if((dynamic_cast<Beetle*>(gameGrid[j][i]))->starve()){
                        //their coordinates are set to null
                        gameGrid[j][i]=nullptr;
                    }
                }
            }
        }
    }
    //ant breeding function
    //if turn number is divisible into 3 evenly, ants breed
    if(z%3==0){
        //iterates through grid and finds ants
        for(int i=0;i<10;i++){
            for(int j=0;j<10;j++){
                if(gameGrid[j][i]==nullptr){
                    continue;
                //if ant and has not breeded already
                }else if(dynamic_cast<Ant*>(gameGrid[j][i])&&!(dynamic_cast<Ant*>(gameGrid[j][i]))->getBreedStatus()){
                    //booleans to pass into breed function to make ant decide
                    bool nOpen, eOpen, sOpen, wOpen;
                    //if statements checks for edge case, so no accessing outside the array
                    if(j==0){
                        nOpen=false;
                    //sets truth value to whether or not the space up is a nullptr or not
                    }else{
                        nOpen=(gameGrid[j-1][i]==nullptr);
                    }
                    if(i==9){
                        eOpen=false;
                    //sets truth value to whether or not the space right is a nullptr or not
                    }else{
                        eOpen=(gameGrid[j][i+1]==nullptr);
                    }
                    if(j==9){
                        sOpen=false;
                    //sets truth value to whether or not the space down is a nullptr or not
                    }else{
                        sOpen=(gameGrid[j+1][i]==nullptr);
                    }
                    if(i==0){
                        wOpen=false;
                    }else{
                    //sets truth value to whether or not the space left is a nullptr or not
                        wOpen=(gameGrid[j][i-1]==nullptr);
                    }

                    //calls breed function for ants which returns which direction the ant wants to go
                    char dirToBreed = gameGrid[j][i]->breed(nOpen,eOpen,sOpen,wOpen);

                    //calls to modify the array after breeding for the ant, and updates breeding status as well as the new ant's
                    //breeding status and turn number
                    breedingModifyArray(gameGrid, j, i, dirToBreed, z);
                }
            }
        }
    }
    //beetle breeding function
    //if turn number is divisible into 8 evenly, beetles breed
    if(z%8==0){
        //iterates through grid and finds beetles
        for(int i=0;i<10;i++){
            for(int j=0;j<10;j++){
                if(gameGrid[j][i]==nullptr){
                    continue;
                //if beetle and has not breeded already
                }else if(dynamic_cast<Beetle*>(gameGrid[j][i])&&!(dynamic_cast<Beetle*>(gameGrid[j][i]))->getBreedStatus()){
                    //booleans to pass into breed function to make beetle decide
                    bool nOpen, eOpen, sOpen, wOpen;
                    //if statements checks for edge case, so no accessing outside the array
                    if(j==0){
                        nOpen=false;
                    //sets truth value to whether or not the space up is a nullptr or not
                    }else{
                        nOpen=(gameGrid[j-1][i]==nullptr);
                    }
                    if(i==9){
                        eOpen=false;
                    //sets truth value to whether or not the space right is a nullptr or not
                    }else{
                        eOpen=(gameGrid[j][i+1]==nullptr);
                    }
                    if(j==9){
                        sOpen=false;
                    //sets truth value to whether or not the space down is a nullptr or not
                    }else{
                        sOpen=(gameGrid[j+1][i]==nullptr);
                    }
                    if(i==0){
                        wOpen=false;
                    //sets truth value to whether or not the space left is a nullptr or not
                    }else{
                        wOpen=(gameGrid[j][i-1]==nullptr);
                    }

                    //calls breed function for beetles which returns which direction the ant wants to go
                    char dirToBreed = gameGrid[j][i]->breed(nOpen,eOpen,sOpen,wOpen);

                    //calls to modify the array after breeding for the beetle, and updates breeding status as well as the new beetle's
                    //breeding status and turn number
                    breedingModifyArray(gameGrid, j, i, dirToBreed, z);
                }
            }
        }
    }
}

//this function prints the output for one turn after all actions in turn have been completed
//intakes turn number, grid, and what characters to output for ants and beetles
void printOutput(int z, Creature*** gameGrid, char a, char b){
    //outputs turn header
    cout<<"TURN "<<z<<endl;
    //nested for loop to iterate thru grid
    for(int i = 0;i<10;i++){
        for(int j =0; j<10;j++){
            //if coordinates empty, print space, else if ant, print char a
            //else if beetle, print char b
            if(gameGrid[i][j]==nullptr){
                cout<<" ";
            }
            else if(dynamic_cast<Ant*>(gameGrid[i][j])){
                cout<<a;
            }else if(dynamic_cast<Beetle*>(gameGrid[i][j])){
                cout<<b;
            }
        }
        //new line after every row
        cout<<endl;
    }
    //new line after turn is done printing
    cout<<endl;
}

//main function
int main(){
    //string to get input filename, input chars for ant and beetle, and input how turns to play
    string fileName;
    char a, b;
    int numTurns;
    cout<<"Enter file name: ";
    getline(cin, fileName);
    cout<<endl;
    cout<<"What character would you like for the ant? ";
    cin>>a;
    cout<<endl;
    cout<<"What character would you like for the beetle? ";
    cin>>b;
    cout<<endl;
    cout<<"How many turns should be played? ";
    cin>>numTurns;
    cout<<endl;

    //declaring fstream variable and opening the world file to connect it to a stream object
    ifstream worldFile (fileName);
    //string to get each line from worldfile
    string recordString;
    //declaring array of pointers
    Creature ***gameGrid = new Creature**[10];
    //setting each array pointer to another array of pointers to make grid
    for(int i = 0 ; i < 10 ; i++)
    {       
        gameGrid[i] = new Creature*[10];   
    }   
    //to update and read the next line of world file
    int j = 0;
    //checks if worldfile is open, otherwise returns error code 1 with message
    if(worldFile.is_open()){
        //reads in file line by line and records it in grid dependent on what character what read
        //if not a or B, then grid was set to nullptr
        while(getline(worldFile, recordString)){
            for(int i = 0;i<10;i++){
                if(recordString.at(i)=='a'){
                    gameGrid[j][i]=new Ant;
                }else if(recordString.at(i)=='B'){
                    gameGrid[j][i]=new Beetle;
                } else{
                    gameGrid[j][i]=nullptr;
                }
            }
            j++;
        }
    }else{
        cout << "There was an error trying to open "<<fileName<<".";
        return 1;
    }
    //closes input world file
    worldFile.close();

    //play the game, inputting the turn number and grid for turn function and printing the output of the turn, using the beetle and ant chars
    for(int i=1;i<numTurns+1;i++){
        turn(i, gameGrid);
        printOutput(i, gameGrid, a, b);
    }
    return 0;
}