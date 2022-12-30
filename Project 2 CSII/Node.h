//Rajit Goel CS 2337.002
//RXG210046
//templated node class, everything is in the header
//does NOT include player because we want it to be templated and be able to take everything
#ifndef NODE_H
#define NODE_H

//including the templated linklist
//and declaring the templated node class
template <typename T> class LinkList;
template <typename T> 
class Node{
    //declaring private variables like next pointer 
    //and the type T object that will be stored in the node
    //friending linklist class, so that linklist can access
    //node private variables
    private: 
        Node<T> *next;
        T obj;
        friend class LinkList<T>;
    //constructors are public
    public:
        //default constructor that sets next pointer to null
        Node(){next=NULL;}
        //parametered constructor
        Node(T obj);

};

//parametered constructor that takes type T object and
//sets object in node to object passed in and
//next pointer to null
template <typename T>
Node<T>::Node(T obj){
    this->obj=obj;
    this->next=NULL;
}

#endif // #define NODE_H