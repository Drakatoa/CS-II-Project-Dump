#include <string>
#ifndef SUPERVISOR_H
#define SUPERVISOR_H
#include "Employee.h"

class Supervisor : public Employee// child of Employee
//public base class access --> all access levels remain the same
//absence of base class access specifier - private base class access
//protected base class access --> private stays private
                                //everything else - protected
{

private:
    float bonus = 0;

public:
    Supervisor(){}
    Supervisor(std::string, std::string dep, int id, float sal, float b);

    float getBonus() {return bonus;}
    void setBonus(float b) { bonus = b;}

	//overridden function
    //virtual double getSalary() const {return salary + bonus;}


};


#endif // SUPERVISOR_H



