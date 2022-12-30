//Rajit Goel CS 2337.002
//RXG210046
//templated node class, everything is in the header
#ifndef NODE_H
#define NODE_H
#include <iostream>

//including the templated binary tree
//and declaring the templated node class
template <typename T> class BinTree;
template <typename T> 
class Node{
    //declaring private variables like left and right pointers pointer 
    //and the type T object that will be stored in the node
    //friending binary tree class, so that binary tree can access
    //node private variables
    private:
        Node<T> *left; 
        Node<T> *right;
        T obj;
        friend class BinTree<T>;
    //constructors are public
    public:
        //default constructor
        Node();
        //parametered constructor
        Node(T obj);
        //getters
        Node<T>* getLeft(){return left;}

        Node<T>* getRight(){return right;}

        //different getters for object if you want to get a copy of the object
        //versus getting a pointer to the object to modify it
        T getObj(){return obj;}

        T* getObjPointer(){return &obj;}

        //setters
        void setObj(T obj){this->obj=obj;}

        void setLeft(Node<T>* n){left=n;}

        void setRight(Node<T>* n){right=n;}

};

 //default constructor that sets left and right pointers to null
template <typename T>
Node<T>::Node(){
    this->left=NULL;
    this->right=NULL;
}

//parametered constructor that takes type T object and
//sets object in node to object passed in and
//left and right pointers to null
template <typename T>
Node<T>::Node(T obj){
    this->obj=obj;
    this->left=NULL;
    this->right=NULL;
}

#endif // #define NODE_H