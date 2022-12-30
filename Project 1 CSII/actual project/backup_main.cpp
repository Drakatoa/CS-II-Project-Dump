#include "Ant.h"
#include "Beetle.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <math.h>
using namespace std;

void turn(int z, Creature*** gameGrid){
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            if(gameGrid[j][i]==nullptr){
                continue;
            }else if(gameGrid[j][i]->getType()=='b'){
                int nDist=0,eDist=0,sDist=0,wDist=0,nCode=1,eCode=1,sCode=1,wCode=1;
                /*nWall=0,eWall=0,sWall=0,wWall=0,
                nAdjAnts=0,eAdjAnts=0,sAdjAnts=0,wAdjAnts=0;*/
                //calculateDist(int j, int i, int &nDist, int &eDist, int &sDist, int &wDist, int &nCode, int &eCode, int)
                if(j==0){
                    nDist=0;
                    nCode=1;
                }else{
                    for(int k=1;k<j+1;k++){
                        if(j==k){
                            nDist=k;
                            nCode=1;
                            break;
                        }
                        if(gameGrid[j-k][i]==nullptr){
                            continue;
                        }else if(gameGrid[j-k][i]->getType()=='b'){
                            // nDist=k;
                            // nCode=2;
                            // break;
                            continue;
                        }else if(gameGrid[j-k][i]->getType()=='a'){
                            nDist=k;
                            nCode=2;
                            break;
                        }
                    }
                }

                if(i==9){
                        eDist=0;
                        eCode=1;
                }else{
                    for(int l=i+1;l<10;l++){
                        if(l==9){
                            eDist=l-i;
                            eCode=1;
                            break;
                        }
                        if(gameGrid[j][l]==nullptr){
                            continue;
                        }else if(gameGrid[j][l]->getType()=='b'){
                            // eDist=l-i;
                            // eCode=2;
                            // break;
                            continue;
                        } else if(gameGrid[j][l]->getType()=='a'){
                            eDist=l-i;
                            eCode=2;
                            break;
                        }
                    }
                }

                if(j==9){
                    sDist=0;
                    sCode=1;
                }else{
                    for(int m=j+1;m<10;m++){
                        if(m==9){
                            sDist=m-j;
                            sCode=1;
                            break;
                        }
                        if(gameGrid[m][i]==nullptr){
                            continue;
                        }else if(gameGrid[m][i]->getType()=='b'){
                            // sDist=m-j;
                            // sCode=2;
                            // break;
                            continue;
                        }else if(gameGrid[m][i]->getType()=='a'){
                            sDist=m-j;
                            sCode=2;
                            break;
                        }
                    }
                }
                
                if(i==0){
                        wDist=0;
                        wCode=1;
                }else{
                    for(int n=1;n<i+1;n++){
                        if(i==n){
                            wDist=n;
                            wCode=1;
                            break;
                        }
                        if(gameGrid[j][i-n]==nullptr){
                            continue;
                        }else if(gameGrid[j][i-n]->getType()=='b'){
                            // wDist=n;
                            // wCode=2;
                            // break;
                            continue;
                        } else if(gameGrid[j][i-n]->getType()=='a'){
                            wDist=n;
                            wCode=2;
                            break;
                        }
                    }
                }
                char whereToMove = gameGrid[j][i]->move(nDist,eDist,sDist,wDist,nCode,eCode,sCode,wCode);
                switch (whereToMove){
                    case 'n': 
                        //check if available, and if beetle or not then move
                        if(gameGrid[j-1][i]==nullptr){
                            gameGrid[j-1][i]=gameGrid[j][i];
                            gameGrid[j][i]=nullptr;
                            break;
                        }else if(gameGrid[j-1][i]->getType()=='a'){
                            gameGrid[j-1][i]=gameGrid[j][i];
                            gameGrid[j][i]=nullptr;
                            //check and do starvetimer=0;
                            break;
                        }else{
                            break;
                        }
                        continue;
                    case 'e': 
                        if(gameGrid[j][i+1]==nullptr){
                            gameGrid[j][i+1]=gameGrid[j][i];
                            gameGrid[j][i]=nullptr;
                            break;
                        }else if(gameGrid[j][i+1]->getType()=='a'){
                            gameGrid[j][i+1]=gameGrid[j][i];
                            gameGrid[j][i]=nullptr;
                            //check and do starvetimer=0;
                            break;
                        }else{
                            break;
                        }
                    case 's': 
                        if(gameGrid[j+1][i]==nullptr){
                            gameGrid[j+1][i]=gameGrid[j][i];
                            gameGrid[j][i]=nullptr;
                            break;
                        }else if(gameGrid[j+1][i]->getType()=='a'){
                            gameGrid[j+1][i]=gameGrid[j][i];
                            gameGrid[j][i]=nullptr;
                            //check and do starvetimer=0;
                            break;
                        }else{
                            break;
                        }
                        continue;
                    case 'w': 
                        if(gameGrid[j][i-1]==nullptr){
                            gameGrid[j][i-1]=gameGrid[j][i];
                            gameGrid[j][i]=nullptr;
                            break;
                        }else if(gameGrid[j][i-1]->getType()=='a'){
                            gameGrid[j][i-1]=gameGrid[j][i];
                            gameGrid[j][i]=nullptr;
                            //check and do starvetimer=0;
                            break;
                        }else{
                            break;
                        }
                    case 't': 
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

int main(){
    string fileName;
    // cout<<"Enter file name: ";
    // getline(cin, fileName);
    // cout<<endl;
    ifstream worldFile ("world.txt");
    string recordString;
    Creature ***gameGrid = new Creature**[10];
    for(int i = 0 ; i < 10 ; i++)
    {       
        gameGrid[i] = new Creature*[10];   
    }   
    int j = 0;
    if(worldFile.is_open()){
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
    worldFile.close();
    for(int i=1;i<6;i++){
        turn(i, gameGrid);
        // printOutput(i, gameGrid);
    }
    // for(int i = 0;i<10;i++){
    //     for(int j =0; j<10;j++){
    //         if(gameGrid[i][j]==nullptr){
    //             cout<<" ";
    //         }
    //         else if(gameGrid[i][j]->getType()=='a'){
    //             cout<<"a";
    //         }else if(gameGrid[i][j]->getType()=='b'){
    //             cout<<"B";
    //         }
    //     }
    //     cout<<endl;
    // }
    return 0;
}