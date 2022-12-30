// #include <iostream>
// #include <math.h>
// #include <iomanip>
// #include <sstream>
// #include <float.h>
// #include <map>
// #include "LinkList.h"

// using namespace std;


// void LinkList::insertEnd(Player P){
//     Node* newNode=new Node(P);
//     Node* curNode=head;

//     if (curNode==NULL) {
//         head=newNode;
//         return;
//     }
  
//     while (curNode->next!=NULL) {
//         curNode=curNode->next;
//     }

//     curNode->next=newNode;
//     tail=newNode;
//     return;
// }

// int LinkList::getLength(){
//     int count=0;
//     Node* curNode=head;
//     while(curNode!=NULL){
//         count++;
//         curNode=curNode->next;
//     }
//     return count;
// }

// void LinkList::removeAfter(Node* curNode){
//     if(curNode==NULL&&head!=NULL){
//         Node* afterCur = head->next;
//         head = afterCur;
//         if(afterCur==NULL){
//             tail=NULL;
//         }
//     }else if(curNode->next!=NULL){
//         Node* afterCur = curNode->next->next;
//         curNode->next=afterCur;
//         if(afterCur==NULL){
//             tail=curNode;
//         }
//     }
// }

// void LinkList::prepend(Node* newNode){
//     if(head==NULL){
//         head=newNode;
//         tail=newNode;
//     }else{
//         newNode->next=head;
//         head=newNode;
//     }
// }

// void LinkList::insertAfter(Node* position, Node* newNode){
//     if(head==NULL){
//         head=newNode;
//         tail=newNode;
//     }else if(position==tail){
//         tail->next=newNode;
//         tail=newNode;
//     }else{
//         newNode->next=position->next;
//         position->next=newNode;
//     }
// }

// void LinkList::sortAlphabetically(){
//     Node* beforeCur = head;
//     Node* curNode = head->next;
//     while(curNode!=NULL){
//         Node* afterCur = curNode->next;
//         Node* N1 = NULL;
//         Node* N2 = head;
//         Node* position = NULL;
//         while(N2!=NULL&&*curNode>*N2){
//             N1=N2;
//             N2=N2->next;
//         }
//         position=N1;
//         if(position==beforeCur){
//             beforeCur=curNode;
//         }else{
//             removeAfter(beforeCur);
//             if(position==NULL){
//                 prepend(curNode);
//             }else{
//                 insertAfter(position, curNode);
//             }
//         }
//         curNode=afterCur;
//     }
// }

// void LinkList::printListOfNames(){
//     Node* curNode=head;
//     while(curNode!=NULL){
//         if(curNode->next==NULL){
//             cout<<curNode->P.getName()<<endl;
//             break;
//         }
//         cout<<curNode->P.getName()<<", ";
//         curNode=curNode->next;
//     }
// }

// Node* LinkList::checkName(std::string name){
//     Node* curNode=head;
//     while(curNode!=NULL){
//         if(name==curNode->P.getName()){
//             return curNode;
//         }
//         curNode=curNode->next;
//     }
//     return NULL;
// }

// void LinkList::clearList(){
//     Node* curNode;
//     while(head!=NULL){
//         curNode=head;
//         head=head->next;
//         free(curNode);
//     }
//     head=NULL;
// }

// string LinkList::toString(Node* curNode, string playerData){
//     stringstream appendix;
//     Node* nextNode=curNode->next;

//     appendix<<curNode->P.getName()<<"\t"<<(int)(curNode->P.getHits()+curNode->P.getOuts()+curNode->P.getStrikeOuts())
//     <<"\t"<<(int)curNode->P.getHits()<<"\t"<<(int)curNode->P.getWalks()<<"\t"<<(int)curNode->P.getStrikeOuts()<<"\t"<<
//     (int)curNode->P.getHitByPitchs()<<"\t"<<(int)curNode->P.getSacrifices()<<"\t";

//     appendix<<fixed<<setprecision(3)<<(round(curNode->P.calcBattingAverage()*1000))/1000<<"\t";
    
//     appendix<<fixed<<setprecision(3)<<(round(curNode->P.calcOnBasePercentage()*1000))/1000<<endl;
    
//     playerData+=appendix.str();
    
//     if(nextNode==NULL){
//         playerData+="\n";
//         return playerData;
//     }
//     return toString(nextNode, playerData);
// }

// void LinkList::calculateThreeBest(double &one, double &two, double &three, string stat){
//     map<string, double(Player::*)()> getMap =
//     {{"BA", &Player::calcBattingAverage},
//     {"OBP", &Player::calcOnBasePercentage},
//     {"H", &Player::getHits},
//     {"W", &Player::getWalks},
//     {"SO", &Player::getStrikeOuts},
//     {"HBP", &Player::getHitByPitchs}};

//     one = two = three = -DBL_MAX;
//     Node* curNode = head;

//     if(stat=="SO"){
//         one = two = three = DBL_MAX;
//         while(curNode!=NULL){
//             double curNum = ((curNode->P.*getMap[stat])());
//             if(curNum<one){
//                 three=two;
//                 two=one;
//                 one=curNum;
//             } else if(curNum<two&&curNum!=one){
//                 three=two;
//                 two=curNum;
//             } else if(curNum<three&&curNum!=two){
//                 three=curNum;
//             }
//             curNode=curNode->next;
//         }
//     }else{
//         while(curNode!=NULL){
//             double curNum = ((curNode->P.*getMap[stat])());
//             if(curNum>one){
//                 three=two;
//                 two=one;
//                 one=curNum;
//             } else if(curNum>two&&curNum!=one){
//                 three=two;
//                 two=curNum;
//             } else if(curNum>three&&curNum!=two){
//                 three=curNum;
//             }
//             curNode=curNode->next;
//         }
//     }
// }

// void LinkList::fillList(LinkList &place, double val, string stat){
//     map<string, double(Player::*)()> getMap =
//     {{"BA", &Player::calcBattingAverage},
//     {"OBP", &Player::calcOnBasePercentage},
//     {"H", &Player::getHits},
//     {"W", &Player::getWalks},
//     {"SO", &Player::getStrikeOuts},
//     {"HBP", &Player::getHitByPitchs}};

//     Node* curNode = head;

//     while(curNode!=NULL){
//         double curNum = ((curNode->P.*getMap[stat])());
//         if(curNum==val){
//             place.insertEnd(curNode->P);
//         }
//         curNode=curNode->next;
//     }
// }