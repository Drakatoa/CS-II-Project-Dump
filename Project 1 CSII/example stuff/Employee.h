
#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <string>

class Employee
{
protected:
    std::string name;
    std::string department;
    int ID=0;
    double salary=0.0;

public:
    //constructors
    Employee();
    Employee(std::string, std::string, int, double);

    // accessors
    int getID() const {return ID;}
    std::string getName() const {return name;}  //inline function

    //to make abstract class
    //create a pure virtual function
    virtual double getSalary() const = 0;
    std::string getDepartment() const {return department;}

    //mutators
    void setName(std::string n) {name = n;}
    void setID(int id) {ID = id;}
    void setSalary(double s) {salary = s;}
    void setDepartment(std::string d) {department = d;}
};

#endif // EMPLOYEE_H
