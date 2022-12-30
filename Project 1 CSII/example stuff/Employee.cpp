
#include "Employee.h"
#include <cstring>

/*void*/ Employee::Employee()
{
    ID = 0;
    salary = 0.0;
}

/*void */ Employee::Employee(std::string n, std::string dept, int id, double sal)
{
    name = n;
    salary = sal;
    ID = id;
    department = dept;
}

/*Employee(Employee& obj)
{
    name = obj.name;
    salary = obj.salary;
    ID = obj.ID;
    department = obj.department
}*/
