#include "Employee.h"
#include <iostream>
using namespace std;

void fillEmployee(Employee& obj, char* n, int i, float s, char* d)
{
    obj.setID(i);
    obj.setName(n);
    obj.setSalary(s);
    obj.setDepartment(d);

}

int main()
{


    Employee E1;
    cout << " E1 name: " << E1.getName() << endl;
    cout << " E1 salary: " << E1.getSalary() << endl;
    cout << " E1 ID: " << E1.getID() << endl;
    cout << " E1 department: " << E1.getDepartment() << endl << endl;



    Employee E2("Jane Doe", "IT", 54321, 50000);
    cout << " E2 name: " << E2.getName() << endl;
    cout << " E2 salary: " << E2.getSalary() << endl;
    cout << " E2 ID: " << E2.getID() << endl;
    cout << " E2 department: " << E2.getDepartment() << endl<<endl;

    Employee *E3 = new Employee;
    cout << " E3 name: " << E3->getName() << endl;
    cout << " E3 salary: " << E3->getSalary() << endl;
    cout << " E3 ID: " << E3->getID() << endl;
    cout << " E3 department: " << E3->getDepartment() << endl<<endl;


    Employee *E4 = new Employee("Jane Doe", "IT", 4321, 45000);
    cout << " E4 name: " << E4->getName() << endl;
    cout << " E4 salary: " << E4->getSalary() << endl;
    cout << " E4 ID: " << E4->getID() << endl;
    cout << " E4 department: " << E4->getDepartment() << endl<<endl;


    //dynamic array of objects
    Employee *EArray = new Employee[5];
    for (int i = 0; i < 5; i++)
        //workaround for overloaded constructor
        fillEmployee(EArray[i], "name", 6789, 50000, "IT");

    //dynamic array of dynamic objects
    Employee **EArray2 = new Employee*[5];
    for (int i = 0; i < 5; i++)
        EArray2[i] = new Employee;

    for (int i = 0; i < 5; i++)
        cout << EArray[i].getID() << " ";
    cout << endl;

    for (int i = 0; i < 5; i++)
        cout << EArray2[i]->getID() << " ";
    cout << endl;



    delete E3;
    delete E4;

    delete [] EArray;
    for (int i = 0; i < 5; i++)
    {
        delete EArray2[i];
    }
    delete [] EArray2;

    return 0;
}

