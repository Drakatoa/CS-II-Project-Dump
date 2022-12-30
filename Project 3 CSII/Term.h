//Rajit Goel CS 2337.002
//RXG210046
//term header with basic inline getter methods and definitions for complicated methods
//includes support for regular terms, and trig terms with different variables for each
//iostream for overloading ostream operator in case we want to print it (we don't print it here)
#include <iostream>
#ifndef TERM_H
#define TERM_H

class Term{
    //private variables coefficient and exponent for regular terms and trig terms (although exponent isn't really, its in the constructor)
    //isSin and trigXCoefficient are used for trig terms
    private:
        int coefficient = 1;
        int exponent = 1;
        bool isSin = false;
        int trigXCoefficient = 0;
    
    public:
        //constructors
        //default constructor
        Term(){}
        //constructor for regular terms
        Term(int coefficient, int exponent);
        //constructor for trig terms
        Term(int coefficient, int exponent, int trigXCoefficient, bool isSin);

        //getters and setters for each variable
        int getCoefficient(){return coefficient;}
        int getExponent(){return exponent;}
        bool getIfSin(){return isSin;}
        int getTrigXCoefficient(){return trigXCoefficient;}
        void setCoefficient(int x){coefficient=x;}
        void setExponent(int x){exponent=x;}
        void setIfSin(bool x){isSin=x;}
        void setTrigXCoefficient(int x){trigXCoefficient=x;}

        //antiderive that return a string for both regular terms and trig terms
        std::string antiderive(long unsigned int index);
        std::string antideriveTrig(long unsigned int index);

        //function that calculates antiderivative value of the regular term and returns double
        double antideriveAndCalc(int a, int b);

        //different update term functions for each because of how they are inserted differently
        //one just takes coefficient, other takes the whole term
        void updateTerm(int coefficient);
        bool updateTermTrig(Term T);

        //simplify method using euclidean algorithm; helper function to antiderive and antideriveTrig
        //passes in by reference so they can be used in those functions
        void simplify(int &numerator, int &denominator);

        //overloaded operators for comparing terms in binary tree
        bool operator<(Term rs);
        bool operator>(Term rs);
        bool operator==(Term rs);

        //overloaded ostream operator that outputs coefficient and exponent of the term outputted
        friend std::ostream& operator<<(std::ostream &out, const Term &t);
};

#endif // #define TERM_H
