#include <string>
#include "Supervisor.h"

    Supervisor::Supervisor(std::string n, std::string dep, int id, float sal, float b) : Employee(n, dep, id, sal)
	{
		//super(n, dep, id, sal);  -- no super keyword in c++
		bonus = b;
	}
