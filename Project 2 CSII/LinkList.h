//Rajit Goel CS 2337.002
//RXG210046
//templated linklist class, everything is in the header
//includes iostream for printing of names and strings
//includes float.h for setting doubles to be max negative or positive value
//in order to compare them
//includes node for obvious reasons
#include <iostream>
#ifndef LINKLIST_H
#define LINKLIST_H
#include <float.h>
#include "Node.h"

using namespace std;

//templated with typename T
template<typename T>
class LinkList {
    private:
        //has head and tail pointer nodes
        Node<T> *head;
        Node<T> *tail;
    public:
        //default constructor
        LinkList();

        //returns head pointer
        Node<T>* getHead(){return head;}

        //returns tail pointer
        Node<T>* getTail(){return tail;}

        //inserts a node at the end of the linklist with object of type T
        void insertEnd(T obj);

        //returns number of nodes in linklist
        int getLength();

        //sorts linklist alphabetically by name/string function passed into the function
        //insertion sort
        void sortAlphabetically(string (*getName)(T object));

        //prints linklist names, based off of name/string function passed into the function
        void printListOfNames(string (*getName)(T object));
        
        //recursive tostring method that returns a string that contains the dataset of all players
        //uses string/tostring function of object that is passed into it, the current node it's at,
        //and current string of data used
        string toString(Node<T>* curNode, string (*dataFill)(T object), string data);

        //removes the node after the node that is passed into the function and connects the node to the node
        //after the removed node
        void removeAfter(Node<T>* curNode);

        //inserts the requested node into the beginning of the linkedlist
        //by setting the new nodes next node to head and setting head to new node
        void prepend(Node<T>* newNode);

        //inserts the requested new node after the node in the first parameter
        void insertAfter(Node<T>* position, Node<T>* newNode);

        //clears the list and frees up any memory used by the nodes 
        void clearList();

        //returns a pointer to T object, if the string matches the string function passed in of the object
        //used to check if dupe names exist, and update object accordingly in main
        T* checkName(string name, string (*getName)(T object));
        
        //calculates the three best variables in an object, by taking 3 doubles as reference, a double function to pass in by reference
        //for the object, and bool of whether or not it is calculating min
        void calculateThreeBest(double &one, double &two, double &three, double (*getNum)(T object), bool calculatingMin);

        //fills lists passed in with objects that have the same value by the double function passed in
        //in order to grab the value from the proper variable of the object needed to compare
        //same values get added to list, other values get skipped
        void fillList(LinkList<T> &place, double val, double (*getNum)(T object));

};

//default constructor sets head and tail pointers to null
template<typename T>
LinkList<T>::LinkList(){
    head=NULL;
    tail=NULL;
}

//method that inserts a node at the end of the linklist 
//with the object of type T
template<typename T>
void LinkList<T>::insertEnd(T obj){
    //creating newnode to insert with object of type T
    Node<T>* newNode=new Node<T>(obj);
    //creating cur to keep track of where node is at to insert
    Node<T>* curNode=head;

    //base case if head is null
    if (curNode==NULL) {
        head=newNode;
        return;
    }
    
    //iterates until next node of cur is null
    while (curNode->next!=NULL) {
        curNode=curNode->next;
    }

    //when next cur node is null
    //next cur node is the newnode and also the tail
    curNode->next=newNode;
    tail=newNode;
    return;
}

//method that returns number of nodes in linklist
template<typename T>
int LinkList<T>::getLength(){
    //counter set to 0 and curnode to head
    int count=0;
    Node<T>* curNode=head;
    //iterates through every node that isn't null and adds
    //to counter
    while(curNode!=NULL){
        count++;
        curNode=curNode->next;
    }
    //returns how many nodes there are
    return count;
}

//method that removes the node after the node that is passed into the function and 
//connects the node to the node after the removed node
template<typename T>
void LinkList<T>::removeAfter(Node<T>* curNode){
    //base case if statement for removing node at the beginning; head node
    if(curNode==NULL&&head!=NULL){
        //sets head to node after head
        Node<T>* afterCur = head->next;
        head = afterCur;
        //sets tail to null if head is set to null
        if(afterCur==NULL){
            tail=NULL;
        }
    //regular case if node after the one you want to remove is existant
    }else if(curNode->next!=NULL){
        //grabs node that is after the node after the one you want to remove
        Node<T>* afterCur = curNode->next->next;
        //sets next pointer of curnode to point towards the one after you want to remove
        curNode->next=afterCur;
        //case if the node after node to be removed is null
        if(afterCur==NULL){
            //sets tail to curnode
            tail=curNode;
        }
    }
}

//method that inserts the requested node into the beginning of the linkedlist
//by setting the new nodes next node to head and setting head to new node
template<typename T>
void LinkList<T>::prepend(Node<T>* newNode){
    //base case if there is no linklist (head is null)
    //head and tail both point to newnode
    if(head==NULL){
        head=newNode;
        tail=newNode;
    //otherwise regular case,
    //new node's next pointer is set to head
    //and head is set to new node
    }else{
        newNode->next=head;
        head=newNode;
    }
}

//method that inserts the requested new node after the node in the first parameter
template<typename T>
void LinkList<T>::insertAfter(Node<T>* position, Node<T>* newNode){
    //base case if there is no linklist (head is null)
    //head and tail both point to newnode
    if(head==NULL){
        head=newNode;
        tail=newNode;
    //2nd case if position is at the end of linklist
    //tail's next pointer points to new node
    //tail is set to new node
    }else if(position==tail){
        tail->next=newNode;
        tail=newNode;
    //otherwise new node's next pointer is set to node after position
    //and new node is inserted after position node
    }else{
        newNode->next=position->next;
        position->next=newNode;
    }
}

//method that sorts linklist alphabetically by name/string function passed into the function
//insertion sort
template<typename T>
void LinkList<T>::sortAlphabetically(string (*getName)(T object)){
    //keeping track of three nodes, beforecur, curnode, and aftercur, which are all initialized to head,
    //head's next and curnode's next node respectively
    Node<T>* beforeCur = head;
    Node<T>* curNode = head->next;
    //insertion sort happens for every node in linklist
    while(curNode!=NULL){
        //aftercur is set to curnode next pointer 
        Node<T>* afterCur = curNode->next;
        //temp nodes for comparison
        Node<T>* N1 = NULL;
        Node<T>* N2 = head;
        Node<T>* position = NULL;

        //starts from head of linklist and loops through until it finds a name that is
        //"larger" or ahead alphabetically on the node it is currently on in the first while loop,
        //and N1 will keep track of the position before N2.
        //position then gets set to the node before N2

        //name/strings come from the function that is passed into function which allows this function
        //to call the passed in function on the obj the node is currently holding, which will return a string
        //from the class from which the object was originally from
        while(N2!=NULL&&getName(curNode->obj)>getName(N2->obj)){
            N1=N2;
            N2=N2->next;
        }
        position=N1;
        //base case if the node found was just before curnode in the first while loop
        //sets beforecur to equal the curnode
        if(position==beforeCur){
            beforeCur=curNode;
        //otherwise it will remove the curnode and place it somewhere else
        }else{
            removeAfter(beforeCur);
            //if the second while loop never occured, the first statement will execute, just
            //putting the curNode at the beginning as it is smaller than the first node
            if(position==NULL){
                prepend(curNode);
            //otherwise it will take the position found from the second while loop
            //and insert curNode after that positional node
            }else{
                insertAfter(position, curNode);
            }
        }
        //curnode is set to curnode next pointer
        curNode=afterCur;
    }
}

//method prints all of the names in the linklist, based off of name/string function passed into the function
template<typename T>
void LinkList<T>::printListOfNames(string (*getName)(T object)){
    //curnode pointer to keep track
    Node<T>* curNode=head;
    //while curnode isn't null
    while(curNode!=NULL){
        //base case if curnode reaches end of list
        //just print getname/string function and a new line,
        //and break
        if(curNode->next==NULL){
            cout<<getName(curNode->obj)<<endl;
            break;
        }
        //otherwise just print the string function of the object in the node with
        //a comma and space and continue on
        cout<<getName(curNode->obj)<<", ";
        curNode=curNode->next;
    }
}

//method that returns a pointer to T object, if the string matches the string function passed in of the object
//used to check if dupe names exist, and update object accordingly in main
template<typename T>
T* LinkList<T>::checkName(string name, string (*getName)(T object)){
    //curnode pointer to keep track
    Node<T>* curNode=head;
    //while curnode isn't null
    while(curNode!=NULL){
        //if there exists a name that is already in one of node objects, by checking using
        //string function passed into from main, return a pointer to the object in node
        if(name==getName(curNode->obj)){
            return &(curNode->obj);
        }
        //otherwise continue on in the list
        curNode=curNode->next;
    }
    //if it did not return anything in the while loop
    //return null
    return NULL;
}

//method that clears the list and frees up any memory used by the nodes 
template<typename T>
void LinkList<T>::clearList(){
    //curnode pointer to keep track
    Node<T>* curNode;
    //while a head node still exists and is not null
    //curnode is set to head, head is set to the node after,
    //and curnode is freed
    while(head!=NULL){
        curNode=head;
        head=head->next;
        free(curNode);
    }
    //head and tail are then set to null
    head=NULL;
    tail=NULL;
}

//recursive tostring method that returns a string that contains the dataset of all players
//uses string/tostring function of object that is passed into it, the current node it's at,
//and current string of data used
template<typename T>
string LinkList<T>::toString(Node<T>* curNode, string (*dataFill)(T object), string data){
    //pointer for nextnode of curnode
    Node<T>* nextNode=curNode->next;

    //uses the string method passed into tostring method to grab the string
    //returned by the object's class method that was passed in by main
    //adds to current dataset string
    data+=dataFill(curNode->obj);
    
    //if curnode's next node is null
    if(nextNode==NULL){
        //add a new line, and end the recursion by returning data
        data+="\n";
        return data;
    }
    //otherwise return tostring method with curnode's next node, the string function that was passed in,
    //and the current data string
    return toString(nextNode, dataFill, data);
}

//method that calculates the three best variables in an object, by taking 3 doubles as reference, a double function to pass in by reference
//for the object, and bool of whether or not it is calculating min
template<typename T>
void LinkList<T>::calculateThreeBest(double &one, double &two, double &three, double (*getNum)(T object), bool calculatingMin){

    //sets each variable equal to the lowest double value
    one = two = three = -DBL_MAX;
    //curnode pointer to keep track
    Node<T>* curNode = head;

    //if we are calculating the minimum/least doubles
    if(calculatingMin){
        //one two and three are set to the highest double value
        one = two = three = DBL_MAX;
        //iterates through linklist
        while(curNode!=NULL){
            //sets num equal to the double function of the object, whichever double number,
            //it needs from the object, passed in by main
            //algorithm to find bottom 3 values ensues
            double curNum = (getNum(curNode->obj));
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
            //continue to next node
            curNode=curNode->next;
        }
    //otherwise calculate the maximum/most doubles
    }else{
        //iterates through linklist
        while(curNode!=NULL){
            //sets num equal to the double function of the object, whichever double number,
            //it needs from the object, passed in by main
            //algorithm to find top 3 values ensues
            //same as above but less thans are set to greater thans
            double curNum = (getNum(curNode->obj));
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
            curNode=curNode->next;
        }
     }
}

//method that fills lists passed in with objects that have the same value by the double function passed in
//in order to grab the value from the proper variable of the object needed to compare
//same values get added to list, other values get skipped
template<typename T>
void LinkList<T>::fillList(LinkList<T> &place, double val, double (*getNum)(T object)){
    //curnode pointer to keep track
    Node<T>* curNode = head;

    //iterates through linklist
    while(curNode!=NULL){
        //the num grabbed by the function, passed in by main and accesses the object's class,
        //of the object stored in the current node is stored as a double
        double curNum = (getNum(curNode->obj));
        //if the num is equal to the double called by the function
        //the linklist that was passed inserts a node at the end of it
        //with the same object
        if(curNum==val){
            place.insertEnd(curNode->obj);
        }
        //continue onwards in the while loop
        curNode=curNode->next;
    }
}

#endif // #define LINKLIST_H
