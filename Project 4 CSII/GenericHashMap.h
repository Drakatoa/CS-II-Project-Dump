//Rajit Goel CS 2337.002
//RXG210046
//generic hashmap header class for replacing unordered_map in STL
//generic value inputted, but string for key insertion
//iostream for printing hashmap and string
//math.h for square root and pow functions
#include <iostream>
#include <math.h>
#ifndef GENERICHASHMAP_H
#define GENERICHASHMAP_H

//declaring template type T
template<typename T>
class GenericHashMap{
    private:
        //struct bucket that stores the string key and generic value we insert
        struct bucket{
            std::string key;
            T value;
        };
        //counter of num buckets currently inserted
        //initial size of array of buckets is 11
        int numBuckets=0;
        int curSize=11;
        //dynamically allocated array of pointers to bucket structs
        bucket** hashmap = new bucket*[curSize];
        //load factor threshold needed to rehash
        const float lf=0.5;
    public:
        //default constructor
        GenericHashMap();
        //print function (not used in program, mostly used for testing)
        void print();
        //insert method
        void insert(string key, T value);
        //converting string to unique int hashcode
        int hashcode(string key);
        //returns whether hashmap has exceeded load factor or not
        bool checkLF();
        //rehashing function
        void rehash();
        //checking if number is prime for rehashing function
        bool isPrime(int x);
        //returns reference to value in bucket
        T* getValue(string key);
        //returns whether or not a key with a value exists for the given key
        bool findValue(string key);
};

//default constructor initializes hashmap to all null
template<typename T>
GenericHashMap<T>::GenericHashMap(){
    for (int i=0; i<curSize; i++){
        hashmap[i]=NULL;
    }
}

//print function
//iterates through entire hashmap,
//if null prints underscore
//else outputs the key at the index of hashmap and space
template<typename T>
void GenericHashMap<T>::print(){
    for(int i=0;i<curSize;i++){
        if(hashmap[i]==NULL){
            cout<<"_ ";
        }else{
            cout<<hashmap[i]->key<<" ";
        }
    }
    cout<<endl;
}

//insert function
//utilizes double hashing to insert buckets into hashmap
template<typename T>
void GenericHashMap<T>::insert(string key, T value){
    //first check if load factor has been exceeded,
    //if so, rehash
    if(checkLF()){
        rehash();
    }
    //then convert the key to a unique hashcode
    //using the hashcode algorithm
    int code=hashcode(key);
    //declare all other ints, j for increasing hprime
    //h is regular hash function that just takes hashcode and
    //modulo it by current size
    int j=0;
    int h = code%curSize;
    //h prime is second hash function that takes hashcode modulo 17,
    //a prime constant I came up with and subtracts it from 17
    int hPrime=17-(code%17);
    //while there is a value in the hashmap index selected
    //increase j which multiplies up the h prime value 
    //and adds it to h, utilizing two hash functions
    //modulo by cursize of hashmap incase the number becomes bigger than the hashmap
    //so that it loops back around
    while(hashmap[(h+j*hPrime)%curSize]!=NULL){
        j++;
    }
    //then we create a new bucket with the final value of j selected
    //set key and value to respective variables
    //increase number of buckets to keep count for checking load factor
    hashmap[(h+j*hPrime)%curSize]=new bucket;
    hashmap[(h+j*hPrime)%curSize]->key=key;
    hashmap[(h+j*hPrime)%curSize]->value=value;
    numBuckets++;
}

//hashcode algorithm for converting strings to int uniquely
template<typename T>
int GenericHashMap<T>::hashcode(string key){
    //first declare int to 0
    int code=0;
    //for each character in the string
    for(long unsigned int i=0;i<key.length();i++){
        //take ASCII value and multiply it by 31 (a common prime number used for hashing) 
        //to power of the length of the string - current index of string
        //cast to an int and add it
        code+=(key.at(i)*(int)pow(31, (key.length()-i)));
    }
    //return the absolute value of the code casted to an int
    return (int)fabs(code);
}

//function used for checking if load factor has exceeded
template<typename T>
bool GenericHashMap<T>::checkLF(){
    //returns whether the number of buckets over current size of the hashmap
    //has exceeded .5
    return ((float)numBuckets/(float)curSize)>=lf;
}

//rehashing function
template<typename T>
void GenericHashMap<T>::rehash(){
    //first we store the current size of the hashmap
    //in a separate variable
    int tempSize=curSize;
    //multiply cursize by 2
    curSize*=2;
    //then increase the size one by while the size isn't prime
    while(!isPrime(curSize)){
        curSize++;
    }
    //create new bucket array of that size
    bucket** newArray = new bucket*[curSize];
    //initialize all buckets to null
    for(int i=0;i<curSize;i++){
        newArray[i]=NULL;
    }
    //iterate through old hashmap using tempsize from earlier
    for(int i=0;i<tempSize;i++){
        //if null at index, skip
        if(hashmap[i]==NULL){
            continue;
        }
        //otherwise use same algorithm from insertion by hashing the key at the index
        int code=hashcode(hashmap[i]->key);
        //declare all the other ints the same way
        int j=0;
        int h = code%curSize;
        int hPrime=17-(code%17);
        //iterate until null array index is found
        while(newArray[(h+j*hPrime)%curSize]!=NULL){
            j++;
        }
        //create new bucket and copy over values from old hashmap bucket
        newArray[(h+j*hPrime)%curSize]=new bucket;
        newArray[(h+j*hPrime)%curSize]->key=hashmap[i]->key;
        newArray[(h+j*hPrime)%curSize]->value=hashmap[i]->value;
        //free up memory used by the old hashmap bucket
        delete hashmap[i];
    }
    hashmap=newArray;
    // print();
}

//returns reference to value using given key
template<typename T>
T* GenericHashMap<T>::getValue(string key){
    //hash the key given
    int code = hashcode(key);
    //declare all other ints the same as insertion algorithm
    int j=0;
    int h = code%curSize;
    int hPrime=17-(code%17);
    //while the keys don't equal each other at the index,
    //jump to the next index by increasing j
    while(hashmap[(h+j*hPrime)%curSize]->key!=key){
        j++;
    }
    //return reference to value at final index
    return &(hashmap[(h+j*hPrime)%curSize]->value);
}

//returns bool of whether a value exists in the hashmap for a given key
template<typename T>
bool GenericHashMap<T>::findValue(string key){
    //hash the key given
    int code = hashcode(key);
    //declare all other ints the same as insertion algorithm
    int j=0;
    int h = code%curSize;
    int hPrime=17-(code%17);
    //while hashmap index doesn't equal null and hashmap key doesn't equal the key given
    //increase j to jump to next index
    while(hashmap[(h+j*hPrime)%curSize]!=NULL&&hashmap[(h+j*hPrime)%curSize]->key!=key){
        j++;
    }
    //if loop stops because the index in the hashmap was null,
    //then it returns false because it did not find the bucket for the given key
    if(hashmap[(h+j*hPrime)%curSize]==NULL){
        return false;
    }
    //otherwise it does exist because key was found and returns true
    return true;
}

//basic algorithm for determining whether a number is prime or not
template<typename T>
bool GenericHashMap<T>::isPrime(int x){
    //goes from all the numbers from 2 to the square root of number entered to 
    //check if it has any multiples besides 1 and itself
    for (int i=2; i<=sqrt(x); i++){
        //if it does divide evenly by any integer between these two values,
        //then it is not prime
        if (x%i==0){
            return false;
        }
    }
    //otherwise if it gets through whole for loop without dividing evenly, return true
    return true;
}

#endif // #define GENERICHASHMAP_H