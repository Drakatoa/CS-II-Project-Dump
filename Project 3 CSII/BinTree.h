//Rajit Goel CS 2337.002
//RXG210046
//templated binary tree class, everything is in the header
//includes iostream for printing of names and strings
//includes vector for returning vectors of high to low values
//includes node in order to construct our binary search tree
#ifndef BINTREE_H
#define BINTREE_H
#include <iostream>
#include <vector>
#include "Node.h"

using namespace std;

//templated with typename T
template<typename T>
class BinTree {
    private:
        //has root pointer node
        Node<T> *root;
    public:
        //default constructor
        BinTree();

        //returns head pointer
        Node<T>* getRoot(){return root;}

        //sets head pointer
        void setRoot(Node<T>* n){root=n;}

        //inserts a node at a leaf of the binary search tree with object of type T
        void insert(T obj);
        Node<T>* insertHelper(Node<T>* N, T obj);

        //searches for the object passed in and if it finds it, it returns the node pointer found
        //otherwise it returns null
        Node<T>* search(T obj);
        Node<T>* searchHelper(Node<T>* N, T obj);

        //removes the node of the object requested and returns if it removed it otherwise returns null
        Node<T>* removeNode(T obj);
        Node<T>* removeHelper(Node<T>* N, Node<T>* Parent, T obj);

        //helper method for removeNode as we needed to find the minimum node of the right subtree if the node to be removed
        //has two children
        Node<T>* findMinNode(Node<T>* N, Node<T>* &parent);

        //returns all objects contained in binary search tree in vector form
        vector<T> returnHightoLow();
        void returnHightoLowHelper(Node<T>* N, vector<T> &highestToLowest);

        //prints all terms in order from right to left, greatest to least (this method isn't used at all, i just put it in for testing purposes)
        void printAllObjects();
        void printAllObjectsHelper(Node<T>* N);


};

//default constructor sets root pointer to null
template<typename T>
BinTree<T>::BinTree(){
    root=NULL;
}

//recursive insert function
//contains base case, if root is null
//root is the new node with the object
//otherwise call insert helper
template<typename T>
void BinTree<T>::insert(T obj){
    if(root==NULL){
        root = new Node<T>(obj);
    }
    insertHelper(root, obj);
}

//recursive insert helper function
template<typename T>
Node<T>* BinTree<T>::insertHelper(Node<T>* N, T obj){
    //base case if a null node to insert to is found
    //the current node N is set to a new node with the object and is returned
    if(N==NULL){
        N=new Node<T>(obj);
        return N;
    }
    //otherwise if the object bigger than the object contained in the node right now
    //call inserthelper and go right
    if(obj > N->obj){
        N->right = insertHelper(N->right,obj);
    //otherwise if the object smaller than the object contained in the node right now
    //call inserthelper and go left
    }else if(obj < N->obj){
        N->left = insertHelper(N->left,obj);
    }
    //base return N statement if the objects are the same
    return N;
}

//recursive search function
//calls search helper
//returns node pointer that could be null or the node the user was searching for with the object
template<typename T>
Node<T>* BinTree<T>::search(T obj){
    return searchHelper(root, obj);
}

//recursive search helper function
template<typename T>
Node<T>* BinTree<T>::searchHelper(Node<T>* N, T obj){
    //base case if node is null or the search function found the node with the object (if they are equal to each other)
    //returns node pointer
    if(N==NULL||obj==N->obj){
        return N;
    //otherwise is object is more than the object in the node
    //return search helper with right node
    }else if(obj > N->obj){
        return searchHelper(N->right,obj);
    //otherwise it must be less, so return search helper with left node
    }else{
        return searchHelper(N->left,obj);
    }
}

//recursive remove node function
//calls remove helper
//returns the node pointer that was removed or if it couldn't find it, it returns null
template<typename T>
Node<T>* BinTree<T>::removeNode(T obj){
    return removeHelper(root, NULL, obj);
}

//recursive remove helper function
//takes parent as an argument because we need to keep track of that 
template<typename T>
Node<T>* BinTree<T>::removeHelper(Node<T>* N, Node<T>* parent, T obj){
    //base case if remove function cannot find node to remove and it is null
    //returns null
    if(N==NULL){
        return N;
    //otherwise moves onto right node if object is more than node object
    }else if(obj > N->obj){
        return removeHelper(N->right, N, obj);
    //or moves onto left node if object is less than node object
    }else if(obj < N->obj){
        return removeHelper(N->left, N, obj);
    //this is the case where find that the node object is equal to the object we are searching for
    //so we have to remove it
    }else{
        //case if the node found has no children
        if(N->left==NULL&&N->right==NULL){
            //we hold the node that needs to be removed by creating a new one out of its object
            Node<T>* hold = new Node<T>(N->obj);
            //if parent isn't null
            //we set the parent's pointer to left or right null, depending on whether N is equal to the left pointer or not
            if (parent!=NULL){
                if(parent->left==N){
                    parent->setLeft(NULL);
                }
                else{
                    parent->setRight(NULL);
                }
            //if node we are removing is the root with no children, we just set root back to null
            }else{
                root = NULL;
            }
            //we delete the node
            //and return the one we are holding
            delete N;
            return hold;
        //case if the node found has one child and it's to the right
        }else if(N->left==NULL){
            //if parent isn't null
            //we set the parent's pointer to left or right to the current nodes right pointer, depending on whether N is equal to the left pointer or not
            if(parent!=NULL){
                if (parent->left==N){
                    parent->setLeft(N->right);
                }else{
                    parent->setRight(N->right);
                }
            //special case if root just has one child to the right and we are removing root
            }else{
                root = N->right;
            }
            //we hold the node that needs to be removed by creating a new one out of its object
            Node<T>* hold = new Node<T>(N->obj);
            //we delete the node
            //and return the one we are holding
            delete N;
            return hold;
        //same case as above case but for the left only child
        }else if(N->right==NULL){
            //if parent isn't null
            //we set the parent's pointer to left or right to the current nodes left pointer, depending on whether N is equal to the left pointer or not
            if(parent!=NULL){
                if (parent->left==N){
                    parent->setLeft(N->left);
                }else{
                    parent->setRight(N->left);
                }
            //special case if root just has one child to the left and we are removing root
            }else{
                root = N->left;
            }
            //we hold the node that needs to be removed by creating a new one out of its object
            Node<T>* hold = new Node<T>(N->obj);
            //we delete the node
            //and return the one we are holding
            delete N;
            return hold;
        }
        //case if node is found and has two children
        //hold node pointer is set to N
        //temp is to return at the end for node removed
        //parent is also set to N as we are going to pass in N's right pointer
        //to find min node which will recursively call itself to the left, until null
        //parent is passed in by reference
        Node<T>* hold = N;
        Node<T>* temp = new Node<T>(hold->obj);
        Node<T>* parent = N;

        //N will be set to the minimum node found
        N = findMinNode(N->right, parent);
        //N's hold pointer has its object set to the minimum node found on the right subtree
        hold->setObj(N->obj);
        //if the node was immediately null and found, parent's right will be set to the node's right
        //otherwise it'll set its left to the node's right after
        if(parent==hold){
            parent->setRight(N->right);
        }else{
            parent->setLeft(N->right);
        }
        //we delete N
        //and return the temp value we were holding the whole time
        delete N;
        return temp;
    }
}

//helper function for removeHelper
//takes node and parent of the node by reference
template<typename T>
Node<T>* BinTree<T>::findMinNode(Node<T>* N, Node<T>* &parent){
    //sets parent equal to the node passed in
    //sets a child pointer to left, since we passed in the right node
    parent = N;
    Node<T>* child = N->left;
    //if the childs left is null we return the child node since that is the minimum node of the right subtree
    if(child->left==NULL){
        return child;
    }
    //otherwise we recursively call the findminnode again for child and parent
    return findMinNode(child, parent);
}

//prints all objects recursively
//calls the helper so it can be done recursively
template<typename T>
void BinTree<T>::printAllObjects(){
    return printAllObjectsHelper(root);
}

//prints all objects helper recursive function
template<typename T>
void BinTree<T>::printAllObjectsHelper(Node<T>* N){
    //base case if the node is null, returns
    if(N==NULL){
        return;
    }
    //otherwise print reverse inorder traversal of all nodes' objects in the tree
    printAllObjectsHelper(N->right);
    cout<<N->obj<<endl;
    printAllObjectsHelper(N->left);
}

//recursive function that returns a vector of all the objects in the tree
//declares vector and passes it in by reference to helper function
//it then returns the vector
template<typename T>
vector<T> BinTree<T>::returnHightoLow(){
    vector<T> highestToLowest;
    returnHightoLowHelper(root, highestToLowest);
    return highestToLowest;
}

//return high to low helper recursive function
template<typename T>
void BinTree<T>::returnHightoLowHelper(Node<T>* N, vector<T> &highestToLowest){
    //base case if the node is null, return
    if(N==NULL){
        return;
    }
    //otherwise stores reverse inorder (high to low) traversal of all nodes' objects in the tree
    //in vector, and returns the helper function by passing the vector in by reference
    returnHightoLowHelper(N->right, highestToLowest);
    highestToLowest.push_back(N->obj);
    returnHightoLowHelper(N->left, highestToLowest);
}

#endif // #define BINTREE_H