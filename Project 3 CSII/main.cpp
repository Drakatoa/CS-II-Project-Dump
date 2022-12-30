//Rajit Goel CS 2337.002
//RXG210046
//This program takes input from a file of integrals, definite and indefinite, indefinite integrals can have trig functions.
//The program then parses each polynomial and its terms and sorts them by exponent and inserts them into a binary search tree.
//Each polynomial has a binary search tree dedicated to it and for each binary tree of terms stored in a vector, it will sort them from
//highest to lowest exponent and output their antiderivative. If it is definite, it will take the integral from the bounds provided and
//displays the bounds and value at the end.
//iostream for input and output to console
//fstream for opening and taking input from a file
//iomanip for setting the output values to be truncated to 3 decimals
//vector for storing term objects and binary trees of term objects
//math.h for absolute value and rounding
//cctype for determining type of character encountered while parsing
//sstream for creating string objects from multiple variables easily
//climits for access to max integer values
//including binary trees to store all term objects
//including term to create terms and store them in templated nodes
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <math.h>
#include <cctype>
#include <sstream>
#include <climits>
#include "BinTree.h"
#include "Term.h"

using namespace std;

//helper function for finding the minimum value of four int values
//compares two values to see if one is less than the other
//if first value less than second value return first otherwise return second
long unsigned int minHelper(long unsigned int x, long unsigned int y){
    if(x < y){
        return x;
    }else{
        return y;
    }
}

//function to find the minimum values of four ints
//used by my parsing method to find which character appears first after a coefficient is parsed
//whether the first character is d(dx), s(sin), c(cos), or x(general x term)
//takes min of first two elements and min of second two elements and compares the two mins to find the min of it 
//returns minimum value
long unsigned int findMinOfFour(long unsigned int a, long unsigned int b, long unsigned int c, long unsigned int d){
    long unsigned int lMin = minHelper(a, b);
    long unsigned int rMin = minHelper(c, d);
    long unsigned int final = minHelper(lMin, rMin);
    return final;
}

//used for parsing multiple character coefficients in trig functions and regular terms as well as for parsing longer bounds
//called if bounds or term coefficients are longer than one character
//basically takes index at which the first digit is at and adds it onto a string until it hits a character it needs to stop at
//character could be d, s, c, or x
//it then returns the whole number/coefficient it found as a string
string coefficientCalculator(char theChar, string toBeParsed, long unsigned int i){
    string final="";
    for(long unsigned int k=i; k<toBeParsed.length();k++){
        if(toBeParsed.at(k)==theChar){
            break;
        }
        final+=toBeParsed.at(k);
    }
    return final;
}

//specialized function for inserting trig functions 
//trig functions use an overloaded constructor that includes the coefficient inside trig function next to x and whether its sin (true) or cos (false) 
//passes in exponent by reference and vector of binary trees by reference and all the other things normally
void insertTrigTerm(int coefficient, int &exponent, int trigXCoefficient, bool isSin, vector<BinTree<Term>> &Polynomials, int j){
    //constructing trig term using 4 variables; default values for trigXCoefficient and isSin are 0 and false
    Term T(coefficient, exponent, trigXCoefficient, isSin);
    //bool used to determine if the trig terms searched for are actually the same
    bool isTheSame;
    //exponent for trig terms at the beginning of each line and polynomial are set to -11 because they are displayed at the end of the function
    //automatically inserted if it is the first trig term being inserted
    if(exponent==-11){
        (Polynomials.at(j)).insert(T);
    }else{
        //otherwise a for loop is initiated for each trig term in the tree, going down the list of -11 to -? exponents
        //creates a term to act as the term to search for out of the exponent
        //the term found in the tree then takes the object pointer and calls the update term trig function which returns whether or not
        //the objects are really the same based on the trigXCoefficient and isSin values, if it is, it returns true and breaks 
        //and the object is consequently updated if the objects are the same in the updatetermtrig function by adding its coefficients together
        //otherwise it keeps going through the for loop
        //if it doesn't find anything to be true, and returns false, the trig term will be inserted into the tree for that polynomial at j/line number
        for(int i=-11;i<exponent;i--){
            Term T1(1, i);
            Node<Term>* nSearch = (Polynomials.at(j)).search(T1);
            isTheSame= (nSearch->getObjPointer())->updateTermTrig(T);
            if(isTheSame){
                break;
            }
        }
    }
    if(!isTheSame){
        (Polynomials.at(j)).insert(T);
    }
    //after each term is inserted, whether or not the term was the same and updated or inserted
    //exponent is decreased and returned by reference for the next trig term as the trig terms are displayed in order
    exponent--;
    
}

//regular term insertion method
//uses regular constructor with coefficient and exponent found from parsing and passes in bin tree vector by reference
//int j for making sure we are accessing the right vector element so that we can access the right tree
void insertTerm(int coefficient, int exponent, vector<BinTree<Term>> &Polynomials, int j){
    //creates term/
    //searchs for the term in the tree
    //if search function doesn't return null
    //we access the pointer to the object in the node that it returned and update its object just by combining the coefficients
    //otherwise we just insert it into the tree
    Term T(coefficient, exponent);
    Node<Term>* nSearch = (Polynomials.at(j)).search(T);
    if(nSearch!=NULL){
        (nSearch->getObjPointer())->updateTerm(coefficient);
    }else{
        (Polynomials.at(j)).insert(T);
    }
    
}

//returns a string that doesn't have any spaces in it so it can easily be parsed character by character
//does a for loop for the whole strings length and if it encounters a space it continues in the loop
//otherwise it adds it onto the string and then it returns it at the end
//used for parsing the first part of definite bounds and then the actual integral at the end
string removeWhiteSpace(string toBeRemoved){
    string final="";
    for(long unsigned int i=0;i<toBeRemoved.length();i++){
        if(toBeRemoved.at(i)==' '){
            continue;
        } else {
            final+=toBeRemoved.at(i);
        }
    }
    return final;
}

//main function where all the parsing happens and I guess insertion
int main(){
    //declaring vectors for storing pairs of ints which are the bounds and for storing the binary tree of each polynomial encountered, with type Term
    vector<pair<int, int>> Bounds;
    vector<BinTree<Term>> Polynomials;
    //declaring coefficient and exponent values to be used in term insertion
    int coefficient=1, exponent=1;
    //declaring string for file input and taking in input for filename
    string fileName;
    cout<<"Enter file name: ";
    getline(cin, fileName);
    //declaring fstream variable and opening the file to connect it to a stream object
    ifstream integralsFile (fileName);
    //declaring string for reading file and storing in
    string lineString;
    //int to keep track of where we are on the vector, updates at the end of the while loop
    int j=0;
    //checks if file is open
    if(integralsFile.is_open()){
        //while there are lines in the file
        while(getline(integralsFile, lineString)){
            //declaring trig exponent to be passed in whenever trig term is inserted as trig terms are displayed at the end of the antiderivative
            int trigExponent = -11;
            //initializing a new templated tree of type term and pushing it back
            Polynomials.push_back(BinTree<Term>());
            //declaring string to be used to parse integral
            string integral;
            //if the integral is indefinite with no bounds
            if(lineString.at(0)=='|'){
                //we push back a pair of two 0s and find the space after the bar
                pair<int, int> zeroes(0, 0);
                Bounds.push_back(zeroes);
                long unsigned int index = lineString.find(' ');
                //we then take the substring from the space index plus one until the end of the string and remove the whitespace
                //so we can prepare it for parsing
                integral = removeWhiteSpace(lineString.substr(index+1, lineString.length()-(index+1)));
            } else {
                //if the integral does have bounds, we must parse the bounds out
                long unsigned int index = lineString.find(' ');
                //we first split the string into two different strings, one with the integral and one with the bounds
                integral = removeWhiteSpace(lineString.substr(index+1, lineString.length()-(index+1)));
                string bounds=removeWhiteSpace(lineString.substr(0, index));
                //we then declare a pair of ints to store the bounds
                pair<int, int> integralBounds;
                //bool to keep track of whether bar was reached or not
                bool bar =false;
                //string to store bounds calculated using coefficientCalculator method
                string boundAB;
                //iterates thru the string length of the bounds
                for(long unsigned int i=0;i<bounds.length(); i++){
                    //before the bar is found we focus on the first number/part of the pair
                    if(!bar){
                        //if it finds a number
                        if(isdigit(bounds.at(i))){
                            //check if the index doesn't equal 0 and there is a negative at the beginning (case if negative number)
                            if(i!=0&&bounds.at(i-1)=='-'){
                                //if it is more than one character
                                if(isdigit(bounds.at(i+1))){
                                    //store number in string that goes until bar
                                    boundAB=coefficientCalculator('|', bounds, 1);
                                    //convert to int
                                    int tempVal = stoi(boundAB);
                                    //bc it is negative convert to negative by taking value and subtracting 2 times itself from it and set to first part of pair
                                    integralBounds.first=tempVal-(2*tempVal);
                                    //then we skip i ahead to whereever it needs to be after that number by adding the length of the number calculated
                                    i+=boundAB.length();
                                //otherwise if it is one character
                                }else{
                                    //i just take the ascii value of the character at i in bounds and just subtract 48 because its the easiest way to just
                                    //convert numbers, then I take the value and subtract 2 times itself and set that to the first part of the pair
                                    int tempVal=bounds.at(i)-48;
                                    integralBounds.first=tempVal-(2*tempVal);
                                }
                            //case if the number is positive
                            }else{
                                //if it is more than one character
                                if(isdigit(bounds.at(i+1))){
                                    //store number in string that goes until bar
                                    boundAB=coefficientCalculator('|', bounds, 0);
                                    //convert to int and store in first pair of bounds
                                    integralBounds.first = stoi(boundAB);
                                    //then we skip i ahead to whereever it needs to be after that number by adding the length of the number calculated
                                    i+=boundAB.length();
                                //otherwise if it is one character
                                }else{
                                    //i just take the ascii value of the character at i in bounds and just subtract 48 because its the easiest way to just
                                    //convert numbers, and store it in first part of pair
                                    integralBounds.first=bounds.at(i)-48;
                                }
                            }
                        }
                    }
                    //then if it finds a bar, set to true
                    if(bounds.at(i)=='|'){
                        bar=true;
                    }
                    //after bar bound, bound b
                    if(bar){
                        //checks if length isn't being exceeded if it checks i+1 and if it is a digit at i
                        if(i!=bounds.length()-1&&isdigit(bounds.at(i))){
                            //checks if negative number 
                            if(bounds.at(i-1)=='-'){
                                //checks if number of multiple characters
                                if(isdigit(bounds.at(i+1))){
                                    //store number in string that goes until bar at i (although it wont reach bar it will just reach the end of the string)
                                    boundAB=coefficientCalculator('|', bounds, i);
                                    //convert to int
                                    int tempVal = stoi(boundAB);
                                    //bc it is negative convert to negative by taking value and subtracting 2 times itself from it and set to second part of pair
                                    integralBounds.second=tempVal-(2*tempVal);
                                    //then we skip i ahead to whereever it needs to be after that number by adding the length of the number calculated
                                    i+=boundAB.length()-1;
                                //otherwise if it is one character
                                }else{
                                    //i just take the ascii value of the character at i in bounds and just subtract 48 because its the easiest way to just
                                    //convert numbers, then I take the value and subtract 2 times itself and set that to the second part of the pair
                                    int tempVal=bounds.at(i)-48;
                                    integralBounds.second=tempVal-(2*tempVal);
                                }
                            //case if the number is positive
                            }else{
                                //if it is more than one character
                                if(i!=bounds.length()-1&&isdigit(bounds.at(i+1))){
                                    //store number in string that goes until bar (although it wont reach bar it will just reach the end of the string)
                                    boundAB=coefficientCalculator('|', bounds, i);
                                    //convert to int and store in second pair of bounds
                                    integralBounds.second = stoi(boundAB);
                                    //then we skip i ahead to whereever it needs to be after that number by adding the length of the number calculated
                                    i+=boundAB.length()-1;
                                //otherwise if it is one character
                                }else{
                                    //i just take the ascii value of the character at i in bounds and just subtract 48 because its the easiest way to just
                                    //convert numbers, and store it in second part of pair
                                    integralBounds.second=bounds.at(i)-48;
                                }
                            }
                        //special case if there is just a positive number at the end of the string for the second bound
                        }else if(i==bounds.length()-1&&bounds.at(i-1)!='-'){
                            integralBounds.second=bounds.at(i)-48;
                        //special case if there is just a single character negative number at the end of the string for second bound
                        }else{
                            int tempVal = bounds.at(i)-48;
                            integralBounds.second=tempVal-(2*tempVal);
                        }
                    }
                }
                //push back the bounds found 
                Bounds.push_back(integralBounds);
            }
                //parsing of the integral string
                //iterates thru every char of the string
                for(long unsigned int i=0; i<integral.length(); i++){
                    //if the character it finds is a sign, it doesn't matter because we will check signs once we encounter an exponent
                    //or coefficient, so we just continue
                    if(integral.at(i)=='+'||integral.at(i)=='-'){
                        continue;
                    //this case only occurs if the digit encountered is a coefficient so we will be checking only for coefficients
                    } else if(isdigit(integral.at(i))){
                        //first case if the coefficient is at the beginning, we assume it is of length one and positive and just set coefficient to that
                        //if we run into another digit later, we will set it to a different value
                        if(i==0){
                            coefficient=integral.at(i)-48;
                        }else{
                            //we still assume it is one digit long and if the character before is +, we set it positive int char -48
                            //otherwise we take the char value -48 and do it times 2 and subtract it from the original value and set coefficient to that
                            if(integral.at(i-1)=='+'){
                                coefficient=integral.at(i)-48;
                            }else if(integral.at(i-1)=='-'){
                                int tempVal = integral.at(i)-48;
                                coefficient=tempVal-(2*tempVal);
                            }
                        }
                        //we look for characters afterwards and see if it is equal to x, s, or c, and if it is, continue to next character
                        //else if its a digit we calculate the multiple digit coefficient
                        if(integral.at(i+1)=='x'||integral.at(i+1)=='s'||integral.at(i+1)=='c'){
                            continue;
                        }else if(isdigit(integral.at(i+1))){
                            //set all ints to max int possible because we are trying to find the lowest index to set the character to search for
                            long unsigned int indexD=INT_MAX;
                            long unsigned int indexX=INT_MAX;
                            long unsigned int indexS=INT_MAX;
                            long unsigned int indexC=INT_MAX;
                            //char to look for is determined based on what character besides a number is next
                            char toLookFor;
                            //we take all of the indexes where a character would be and compare them to each other 
                            if(integral.find('d', i+1)!=string::npos){
                                indexD=integral.find('d', i+1);
                            }
                            if(integral.find('x', i+1)!=string::npos){
                                indexX=integral.find('x', i+1);
                            }
                            if(integral.find('s', i+1)!=string::npos){
                                indexS=integral.find('s', i+1);
                            }
                            if(integral.find('c', i+1)!=string::npos){
                                indexC=integral.find('c', i+1);
                            }
                            //calls the function to see which is the minimum index out of the four
                            long unsigned int final = findMinOfFour(indexD, indexX, indexS, indexC);
                            //checks each value to see which index it lined up with
                            if(final==indexD){
                                toLookFor='d';
                            }else if(final==indexX){
                                toLookFor='x';
                            }else if(final==indexS){
                                toLookFor='s';
                            }else{
                                toLookFor='c';
                            }
                            //checks if coefficient is not index 0 and if it is negative by checking character behind
                            if(i!=0&&integral.at(i-1)=='-'){
                                //passes in string to coefficient calculator whatever character it's looking for and the index value at which the coefficient starts
                                string coefficientLong=coefficientCalculator(toLookFor, integral, i);
                                //converts to int from string
                                int tempVal = stoi(coefficientLong);
                                //we take the value times 2 and subtract it from the original value and set coefficient to that
                                coefficient=tempVal-(2*tempVal);
                                //we also set i to go up minus 1 so that it can get to x or sin or cos or dx
                                i+=coefficientLong.length()-1;
                            //otherwise if its positive
                            }else{
                                //we do basically the same thing as up top except we keep the value we get from converting string to int
                                string coefficientLong=coefficientCalculator(toLookFor, integral, i);
                                int tempVal = stoi(coefficientLong);
                                coefficient=tempVal;
                                i+=coefficientLong.length()-1;
                            }
                            //if the char to look for is d we know that it doesn't have an x after it so we just insert it as the last number and without an exponent
                            if(toLookFor=='d'){
                                insertTerm(coefficient, 0, Polynomials, j);
                            }
                        //otherwise we assume that there is nothing after besides maybe + or - so we insert term anyway with exponent 0
                        }else{
                            exponent=0;
                            insertTerm(coefficient, exponent, Polynomials, j);
                        }
                    //special case for inserting trig terms if the char comes up with s or c
                    }else if(integral.at(i)=='s'||integral.at(i)=='c'){
                        //declaring bool of whether or not it is sin
                        bool isSin=false;
                        //declaring x coefficient of trig value inside for use later
                        int trigXCoefficient=1;
                        //if the detected character was s, we make sin true otherwise leave it false for cos
                        if(integral.at(i)=='s'){
                            isSin=true;
                        }
                        //determing coefficient for trig function if it wasn't already determined
                        //if the trig function appears at the beginning of the integral we can assume the coefficient will be 1
                        if(i==0){
                            coefficient=1;
                        }
                        //if there isn't a digit before the trig function
                        if(i!=0&&!isdigit(integral.at(i-1))){
                            //if there is a plus, we set coefficient to 1
                            if(integral.at(i-1)=='+'){
                                coefficient=1;
                            //if -, coefficient =-1
                            }else if(integral.at(i-1)=='-'){
                                coefficient=-1;
                            //otherwise we assume the coefficient is 1
                            }else{
                                coefficient=1;
                            }
                        }
                        //determining coefficient inside trig function for x
                        //if the character just inside the trig function is x, we know the coefficient is 1
                        //we then advance the for loop 3 characters
                        if(integral.at(i+3)=='x'){
                            trigXCoefficient=1;
                            i+=3;
                        //if there is a digit, it gets more complicated
                        }else if(isdigit(integral.at(i+3))){
                            //if it's just one character and the next one is an x
                            //we know its a positive one digit int and we just take
                            //the character val -48, store it and advance the for loop 4 characters
                            if(integral.at(i+4)=='x'){
                                trigXCoefficient=integral.at(i+3)-48;
                                i+=4;
                            //otherwise we have to calculate the coefficient if its multiple digits
                            //so we call the function to calculate it and look for x and where it starts at (i+3)
                            //store the string to int value in trig coefficient and advance the for loop however long
                            //the coefficient string was plus 3
                            }else{
                                string coefficientLong=coefficientCalculator('x', integral, i+3);
                                int tempVal = stoi(coefficientLong);
                                trigXCoefficient=tempVal;
                                i+=coefficientLong.length()+3;
                            }
                        //this is basically the same function as above but with negatives and adding one more to i to 
                        //make up for negatives
                        //if negative
                        }else if(integral.at(i+3)=='-'){
                            //if the char after negative is x, we know its -1 and advance for loop accordingly
                            if(integral.at(i+4)=='x'){
                                trigXCoefficient=-1;
                                i+=4;
                            //if there is a digit and the next char after digit is x, we know
                            //its just that one digit and store it and advance for loop accordingly
                            }else if(isdigit(integral.at(i+4))&&integral.at(i+5)=='x'){
                                int tempVal=integral.at(i+4)-48;
                                trigXCoefficient=tempVal-(2*tempVal);
                                i+=5;
                            //otherwise we must calculate the multiple digit coefficient and store it as a negative
                            //and move loop forward
                            }else{
                                string coefficientLong=coefficientCalculator('x', integral, i+4);
                                int tempVal = stoi(coefficientLong);
                                trigXCoefficient=tempVal-(2*tempVal);
                                i+=coefficientLong.length()+4;
                            }
                        }
                        //since this else if statement is basically built to one shot trig functions, we just call insert trig function
                        //here and pass all our values to the function and trigexponent whatever its on
                        insertTrigTerm(coefficient, trigExponent, trigXCoefficient, isSin, Polynomials, j);
                    //if the character found is x, does not affect trig functions, only checking if exponent or coefficient = 1/-1 in some way
                    }else if(integral.at(i)=='x'){
                        //if its the first index and nothing before it, coefficient is 1
                        if(i==0){
                            coefficient=1;
                            //if there is a carrot afterwards continue
                            if(integral.at(i+1)=='^'){
                                continue;
                            //otherwise insert with exponent 1 since it is just an x
                            }else{
                                exponent=1;
                                insertTerm(coefficient, exponent, Polynomials, j);
                            }
                        //if not first index
                        }else{
                            //if there isn't a digit before x we know the digit is a one
                            if(!isdigit(integral.at(i-1))){
                                //if its a plus then 1
                                if(integral.at(i-1)=='+'){
                                    coefficient=1;
                                //if its a minus then -1
                                }else if(integral.at(i-1)=='-'){
                                    coefficient=-1;
                                //else assume 1
                                }else{
                                    coefficient=1;
                                }
                            }
                            //if somehow the program accesses the x after d in dx, we break the for loop
                            if(i+1==integral.length()){
                                break;
                            }
                            //if there is an exponent, we continue to the carrot
                            if(integral.at(i+1)=='^'){
                                continue;
                            //otherwise we insert the term with exponent 1
                            }else{
                                exponent=1;
                                insertTerm(coefficient, exponent, Polynomials, j);
                            }
                        }
                    //else if statement for calculating exponents
                    } else if(integral.at(i)=='^'){
                        //we first must check which sign after the exponent is closer, + or -
                        //so we declare 2 ints to check this
                        long unsigned int substrIndex=0;
                        long unsigned int tempSubstrIndex=0;
                        if(integral.find('+', i)!=string::npos&&integral.find('-', i+2)!=string::npos){
                            //if a plus exists and a minus exists after the exponent, we set each int equal to each 
                            //one respectively
                            substrIndex = integral.find('+', i);
                            tempSubstrIndex = integral.find('-', i+2);
                            //if - is closer than +, we set the index to the temp value that has the minus one
                            if(tempSubstrIndex<substrIndex){
                                substrIndex=tempSubstrIndex;
                            }
                        //otherwise if we can't find a minus, if we find a plus we just set it to that
                        }else if(integral.find('+', i)!=string::npos){
                            substrIndex = integral.find('+', i);
                        //if we can't find a plus, if we find a minus we just set it to that
                        }else if(integral.find('-', i+2)!=string::npos||integral.at(i+2)=='-'){
                            substrIndex = integral.find('-', i+2);
                        //otherwise we must be at the end of the polynomial and we can only find a d
                        }else{
                            substrIndex=integral.find('d');
                        }
                        //set the length equal to whatever index is found minus current character we are at minus 1
                        long unsigned int length = substrIndex-i-1;
                        string temp =integral.substr(i+1, length);
                        //if the character after the carrot is negative we know its negative
                        if(integral.at(i+1)=='-'){
                            //if the length of the string is 3, we know it can't be anything besides -10, we advance the for loop 3 forward
                            if(temp.length()==3){
                                exponent=-10;
                                i+=3;
                            //otherwise we take whatever character is after the negative -48 and convert it to a negative value
                            //and store it, and advance for loop 2 forward 
                            }else{
                                int tempVal = integral.at(i+2)-48;
                                exponent=tempVal-(2*tempVal);
                                i+=2;
                            }
                        //if there is a digit after carrot, we know it's positive
                        }else if(isdigit(integral.at(i+1))){
                            //if the length of the string is one, we take whatever the character there is,
                            //store it and advance for loop one
                            if(temp.length()==1){
                                exponent = integral.at(i+1)-48;
                                i++;
                            //otherwise we know the exponent is 10, and we just advance for loop twice
                            }else{
                                exponent=10;
                                i+=2;
                            }
                        }
                        //then we insert term
                        insertTerm(coefficient, exponent, Polynomials, j);
                    //if we get to d, we break out of the for loop
                    }else if(integral.at(i)=='d'){
                        break;
                    }
                }
            //advance the j forward so that we know which part of the vector we are on
            j++;
        }
    //if file isn't open then it returns an error message and ends with exit code 1
    }else{
        cout << "There was an error trying to open "<<fileName<<".";
        return 1;
    }
    //closing the file
    integralsFile.close();
    //we now iterate thru the whole vector of binary trees of type term
    //this is for printing out each antiderivative on each line
    for(long unsigned int i =0; i<Polynomials.size();i++){
        //declaring string variable to add onto and display at the end
        string antiderivedPolynomial="";
        //we call the function that returns all of the polynomials in the tree from highest exponent to lowest exponent
        vector<Term> polynomialTerms = (Polynomials.at(i)).returnHightoLow();
        //we then iterate through all the terms in the tree and add onto our string variable by calling the antiderive expression
        //on each term which returns a string in order
        for(long unsigned int j=0;j<polynomialTerms.size();j++){
            //we must pass in j in order to know if the term is first in the vector
            antiderivedPolynomial+=(polynomialTerms.at(j)).antiderive(j);
        }
        //if the bounds are not 0, 0 we must calculate the antiderivative value from the bounds
        if(!((Bounds.at(i)).first==0&&(Bounds.at(i)).second==0)){
            //so we declare a double
            double total=0;
            //and we go thru the terms again and add each double it returns to the total double, by calculating the antiderivative
            //of each term from b to a and subtracting the two
            for(long unsigned int j=0;j<polynomialTerms.size();j++){
                total+=(polynomialTerms.at(j)).antideriveAndCalc(Bounds.at(i).first,Bounds.at(i).second);
            }
            //we then declare a stringstream variable to add all our components for listing out antiderivative with bounds
            stringstream appendix;
            //adding all components and preparing the output for total by rounding and setting precision to 3 decimals
            appendix<<", "<<Bounds.at(i).first<<"|"<<Bounds.at(i).second<<" = "<<fixed<<setprecision(3)<<(round(total*1000))/1000;
            //adding on expression at the end and converting stringstream to string
            antiderivedPolynomial+=appendix.str();
        //otherwise we just add + C to the end
        }else{
            antiderivedPolynomial+=" + C";
        }
        //we then just output the final string and a new line
        cout<<antiderivedPolynomial<<endl;
    }
    return 0;
}