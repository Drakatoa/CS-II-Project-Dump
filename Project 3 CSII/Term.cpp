//Rajit Goel CS 2337.002
//RXG210046
//math.h for absolute value
//sstream for creating string objects from multiple variables easily
//each variable/text everytime
//includes term header
#include <iostream>
#include <math.h>
#include <sstream>
#include "Term.h"

//constructor for regular terms; sets coefficient and exponent
Term::Term(int coefficient, int exponent){
    this->coefficient=coefficient;
    this->exponent=exponent;
}

//constructor for trig terms; sets coefficient, exponent, trigXCoefficient, and whether or not it is sin
Term::Term(int coefficient, int exponent, int trigXCoefficient, bool isSin){
    this->coefficient=coefficient;
    this->exponent=exponent;
    this->trigXCoefficient=trigXCoefficient;
    this->isSin=isSin;
}

//antiderive for regular terms
//takes index to make sure first term is properly constructed
std::string Term::antiderive(long unsigned int index){
    //since default value of trigXCoefficient is 0 if a trig term is inserted
    //it will automatically not be 0 so we return whatever is in the antideriveTrig function
    if(trigXCoefficient!=0){
        return antideriveTrig(index);
    }
    //standard antiderivation; coefficient is divided by exponent+1
    //declaring ints to differentiate and simplify the fraction that will result from dividing them
    int newExponent = exponent+1;
    int newCoefficient = coefficient;
    //strings to store coefficient and exponent terms and combine them later to return them
    std::string coefficientS, exponentS;
    //passes in newcoefficient and newexponent by reference in order to simplify their fraction down
    simplify(newCoefficient, newExponent);
    //case if the coefficient given is just 0, then everything after is just 0
    if(newCoefficient==0){
        return "0";
    }
    //if it turns out the simplified fraction is 1/1, we use a xor operator to determine if its
    //negative, if both are negative or if both are positive then we set the coefficient to nothing
    //otherwise the coefficient is negative
    if(fabs(newExponent)==1&&fabs(newCoefficient)==1){
        if((newExponent<0)^(newCoefficient<0)){
            coefficientS="-";
        }else{
            coefficientS="";
        }
    //if only the denominator/newexponent is one then we can just drop the denominator and make
    //the coefficient string just the new coefficient
    }else if(newExponent==1){
        std::stringstream appendix;
        appendix<<newCoefficient;
        coefficientS=appendix.str();
    //otherwise if it remains fractional, then it gets put into parentheses format (num/den)
    }else{
        std::stringstream appendix;
        appendix<<"("<<newCoefficient<<"/"<<newExponent<<")";
        coefficientS=appendix.str();
    }
    //if the exponent is 0
    //set exponent string to x
    if(exponent+1==1){
        exponentS="x";
    //otherwise exponent string is x^(exponent+1)
    }else{
        std::stringstream appendix;
        appendix<<"x"<<"^"<<exponent+1;
        exponentS=appendix.str();
    }
    //if everything is positive and index is equal to 0,
    //return coefficient and exponent string together as is
    if(index==0&&newCoefficient>0&&newExponent>0){
        return coefficientS+exponentS;
    //else if only positive but not index 0, return + and coefficient exponent
    }else if(newCoefficient>0&&newExponent>0){
        return " + "+coefficientS+exponentS;
    }
    //otherwise set up a for loop that removes negative from the string and stores in a new coefficient string
    //we do this so that we can position the negative in the right place and also to get rid of negatives in weird places
    //iterate thru string, if it has negative continue otherwise add it to string
    std::string newCoefficientS="";
    for(long unsigned int i=0;i<coefficientS.length();i++){
        if(coefficientS.at(i)=='-'){
            continue;
        }else{
            newCoefficientS+=coefficientS.at(i);
        }
    }
    //checking if the coefficient is at the beginning and if it has a parentheses
    //if it does inserts the negative inside the parentheses next to the first number
    if(index==0&&newCoefficientS.length()!=0&&newCoefficientS.at(0)=='('){
        newCoefficientS.insert(newCoefficientS.begin()+1, '-');
        return newCoefficientS+exponentS;
    //otherwise if just index = 0 and doesn't have parenthetical coefficient
    //return negative with no spacing
    }else if(index==0){
        return "-"+newCoefficientS+exponentS;
    }
    //otherwise return negative with spacing
    return " - "+newCoefficientS+exponentS;
}

//antiderive for trig terms
//takes index to make sure first term is properly constructed
//called from regular antiderive function
std::string Term::antideriveTrig(long unsigned int index){
    //coefficient outside trig function is divided by the coefficient inside the trig function
    //so we create two new variables out of the variables contained in the terms and pass
    //them in by reference to the simplify function
    int newTrigCoefficient = trigXCoefficient;
    int newCoefficient = coefficient;
    //we also create the coefficient and trig strings that we will make and combine to return
    //newCoefficientS is used if negatives need to be parsed such as converting from sin to cos
    std::string coefficientS, insideTrig;
    std::string newCoefficientS="";
    simplify(newCoefficient, newTrigCoefficient);
    //same thing if coefficient is equal to 0, everything is 0
    if(newCoefficient==0){
        return "0";
    }
    //same thing as first antiderive, if both have abs val of 1, and xor (only one number is negative), then coefficient string is -,
    //otherwise it's nothing
    if(fabs(newTrigCoefficient)==1&&fabs(newCoefficient)==1){
        if((newTrigCoefficient<0)^(newCoefficient<0)){
            coefficientS="-";
        }else{
            coefficientS=" ";
        }
    //same thing if denominator is 1, coefficient is just the numerator
    }else if(newTrigCoefficient==1){
        std::stringstream appendix;
        appendix<<newCoefficient;
        coefficientS=appendix.str();
    //otherwise it is formatted with parentheses
    }else{
        std::stringstream appendix;
        appendix<<"("<<newCoefficient<<"/"<<newTrigCoefficient<<")";
        coefficientS=appendix.str();
    }
    //case if trig function was simple and didn't have any coefficients besides 1
    if(coefficientS==" "&&fabs(trigXCoefficient)==1){
        //if it is sin, we must return a negative version of cos depending on whether it is the first index or not
        if(isSin){
            if(index==0){
                return "-cos x";
            }else{
                return " - cos x";
            }
        //otherwise if it cos, we just return positive sin depending on first index or not
        }else{
            if(index==0){
                return "sin x";
            }else{
                return " + sin x";
            }
        }
    }
    //making sure coefficient string isn't empty
    if(coefficientS.length()!=0){
        //if a negative sign is found, we have to reformat it and remove it from the string and place it at the beginning
        //because when we convert to sin, it would be hard to know if there is a double negative without having the minuses
        //next to each other
        if(coefficientS.find("-")!=std::string::npos){
        //iterate thru string and if there is a negative continue, otherwise add it to the new string
        for(long unsigned int i=0;i<coefficientS.length();i++){
            if(coefficientS.at(i)=='-'){
                continue;
            }else{
                newCoefficientS+=coefficientS.at(i);
            }
        }
        //place negative at the beginning of new string
        newCoefficientS="-"+newCoefficientS;
        //otherwise if no negative is found, we know its positive and just set the new coefficient string to the old one
        }else{
            newCoefficientS=coefficientS;
        }
    }
    //so here we are dealing with sin functions in this if statements
    if(isSin){
        //we insert a negative sign at the beginning of the new coefficient string
        newCoefficientS.insert(newCoefficientS.begin(), '-');
        //if we find a double negative, we remove the double negative
        //so it becomes positive and if the index doesn't equal 0
        //then we add a plus sign
        if(newCoefficientS.find("--")!=std::string::npos){
            newCoefficientS=newCoefficientS.substr(2, newCoefficientS.length()-2);
            if(index!=0){
                newCoefficientS= " + "+newCoefficientS;
            }
        //otherwise if its just negative, we remove the negative at the beginning again
        //and reformat it so that the negative is in the right place
        }else{
            //removing negative
            newCoefficientS=newCoefficientS.substr(1, newCoefficientS.length()-1);
            //checking if parenthetical and index is 0, then negative goes inside parentheses
            if(index==0&&newCoefficientS.length()!=0&&newCoefficientS.at(0)=='('){
                newCoefficientS.insert(newCoefficientS.begin()+1, '-');
            //if index is 0 then there is no spacing
            }else if(index==0){
                newCoefficientS= "-"+newCoefficientS;
            //otherwise there is spacing between the negative
            }else{
                newCoefficientS= " - "+newCoefficientS;
            }
        }
        //we declare stringstream here to concatenate all variables here
        //for what's inside the trig function
        std::stringstream appendix;
        //if its one, we just make cos x and add that, -1 = cos -x, and anything else we just stick
        //it onto the beginning of x
        if(trigXCoefficient==1){
            appendix<<"cos "<<"x";
        }else if(trigXCoefficient==-1){
            appendix<<"cos "<<"-x";
        }else{
            appendix<<"cos "<<trigXCoefficient<<"x";   
        }
        //convert it to string and set it to the insidetrig string
        insideTrig =appendix.str();
    //if the function is cos
    }else{
        //if there is a negative at the beginning
        //we don't have to deal with converting to negative and doubles negatives,
        //which makes this a lot easier
        if(newCoefficientS.at(0)=='-'){
            //we chop off the negative to reformat it correctly
            newCoefficientS=newCoefficientS.substr(1, newCoefficientS.length()-1);
            //if its parenthetical and the first term, we insert the negative inside the parentheses
            if(index==0&&newCoefficientS.length()!=0&&newCoefficientS.at(0)=='('){
                newCoefficientS.insert(newCoefficientS.begin()+1, '-');
            //otherwise if its just index 0, negative with no spacing
            }else if(index==0){
                newCoefficientS= "-"+newCoefficientS;
            //otherwise negative with spacing
            }else{
                newCoefficientS= " - "+newCoefficientS;
            }
        //if its positive all the way through
        //then we add a positive on if index doesn't equal 0 and both num and den are positive
        }else{
            if(newCoefficient>0&&newTrigCoefficient>0&&index!=0){
                newCoefficientS= " + "+newCoefficientS;
            }
        }
        //we declare another stringstream and do the same process as in the sin block
        std::stringstream appendix;
        //if its one, sin x, -1, sin -x, otherwise trig coefficient goes into the sin function with x
        if(trigXCoefficient==1){
            appendix<<"sin "<<"x";
        }else if(trigXCoefficient==-1){
            appendix<<"sin "<<"-x";
        }else{
            appendix<<"sin "<<trigXCoefficient<<"x";
        }
        //convert it to string and set it to the insidetrig string
        insideTrig =appendix.str();
    }
    //if for some reason there ends up being a double space in the coefficient string returned which does happen
    //we just erase one of those space characters whereever it ends up being found
    if(newCoefficientS.find("  ")!=std::string::npos){
        newCoefficientS.erase(newCoefficientS.begin()+newCoefficientS.find("  "));
    }
    //we then just return the whole expression, coefficient plus trig expression
    return newCoefficientS+insideTrig;
}

//special update trig term function
//returns a bool to main so that it doesn't accidentally insert an duplicate object that already
//exists and can be combined with, takes term because we need to compare the trig coefficients and 
//if it is a sin or not
bool Term::updateTermTrig(Term T){
    //we set a boolean of whether or not the sin bool values and trig coefficients are equal to each other
    bool isSame = trigXCoefficient==T.trigXCoefficient&&isSin==T.isSin;
    //if they are, we simply update the term called on by adding the two coefficients together
    if(isSame){
        coefficient+=T.coefficient;
    }
    //returning the boolean allows main to break out of the loop searching for trig terms
    //and not insert the duplicate node
    return isSame;
}

//calculates the antiderivative of the term passed in with the two bounds
//returns their difference
double Term::antideriveAndCalc(int a, int b){
    //we create two doubles, one out of exponent+1, and one by dividing
    //the coefficient by the new exponent
    double newExp = (double)(exponent+1);
    double newCoef= (double)(coefficient)/newExp;
    //we then just return the power of the first x, b, to the new exponent times the new coefficient
    //minus the power of the second x, a, to the new exponent times the new coefficient
    return ((pow(b, newExp))*newCoef) - ((pow(a, newExp))*newCoef);
}

//simplify function that takes variables by reference
//uses the euclidean algorithm to simplify fractions down
void Term::simplify(int &numerator, int &denominator){
    int x=numerator, y=denominator;
    //while modulus of den over num doesn't equal 0
    //set temp value to x, x = to y modulus x
    //y equal to temp value
    while(x!=0){
        int z=x;
        x=y%x;
        y=z;
    }
    //then divide both numerator and denominator by y, the GCD found by the algorithm
    numerator=numerator/y;
    denominator=denominator/y;
}

//update term function for regular terms
//just increments the coefficient of the term up by 
//the coefficient passed into the function
void Term::updateTerm(int coefficient){
    this->coefficient+=coefficient;
}

//overloaded less than operator
//just compares the exponents of two terms, if the first is less than the second
bool Term::operator<(Term rs){
    return exponent<rs.exponent;
}

//overloaded greater than operator
//just compares the exponents of two terms, if the first is greater than the second
bool Term::operator>(Term rs){
    return exponent>rs.exponent;
}

//overloaded equal to operator
//just compares the exponents of two terms, if they are equal
bool Term::operator==(Term rs){
    return exponent==rs.exponent;
}

//overloaded output operator
//not used in the main program
//but if anybody ever wanted to print of the exponent and coefficient of the terms, they can
std::ostream& operator<<(std::ostream &out, const Term &t){
    std::cout<<"exponent: "<<t.exponent<<" coefficient: "<<t.coefficient<<std::endl;
    return out;
}