#pragma once
#include<queue>
#include<array>
#include"SomeDef.h"
using namespace std;

class EntityManager
{
private:
	// Queue of unused entity IDs
	queue<Entity> mAvailableEntities{}; //Queue of available Entities 
     array<Signature, MaxE> mSignatures{}; // array of signature where the index correspond to the entity ID that it belongs to
	 unsigned int  mLivingEntityCount{};  // counter for living Entities(Entities that have been created)
public:
	EntityManager();
	Entity CreateEntity();
    void DestroyEntity(Entity entity);
	void SetSignature(Entity entity, Signature signature);
    Signature GetSignature(Entity entity);

};
