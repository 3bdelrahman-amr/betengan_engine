#pragma once
#include"SomeDef.h"
/// <summary>
/// base class for all components
/// just to destroy a component by calling the virtual function EntityDestroy to all components
/// </summary>
class AllComponents
{
        public:
		virtual ~AllComponents() = default;
		virtual void EntityDestroyed(Entity entity) = 0;
	
};

