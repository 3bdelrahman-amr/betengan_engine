#pragma once
#include"SomeDef.h"
#include<set>
//#include"Manager.h"
/// <summary>
/// every system will inherit from this class
/// it doesn't contain any pure virtual function 
/// so it is only inheritance not virtual
/// this will help the system manager to has a pointer
/// on every system
/// </summary>
class System
{
public:
	
	set<Entity> Entities; // list of entities the system will iterate over it
	
};

