#pragma once
//#include<memory>
#include<unordered_map>
//#include"SomeDef.h"
#include"System.h"
using namespace std;
class SystemManager
{
private:
	// Map from system type string pointer to a signature
	unordered_map<const char*, Signature> mSignatures{};

	// Map from system type string pointer to a system pointer
	unordered_map<const char*, shared_ptr<System>> mSystems{};
public:
	//shared_ptr<System> abdo;
	//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
	//make_shared<system>
	template<typename T>
	shared_ptr<T> RegisterSystem()
	{
		const char* typeName = typeid(T).name();

		//assert(Systems.find(typeName) == mSystems.end() && "Registering system more than once.");
		
		// Create a pointer to the system and return it so it can be used externally
		auto system = make_shared<T>();
		mSystems.insert({ typeName, system });
		return system;
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename T>
	void SetSignature(Signature signature)
	{
		const char* typeName = typeid(T).name();

		assert(mSystems.find(typeName) != mSystems.end() && "System used before registered.");

		// Set the signature for this system
		mSignatures.insert({ typeName, signature });
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	void EntityDestroyedd(Entity entity)
	{
		// Erase a destroyed entity from all system lists
		// Entities is a set so no check needed
		for (auto const& pair : mSystems)
		{
			auto const& system = pair.second;

			system->Entities.erase(entity);
		}
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	void EntitySignatureChanged(Entity entity, Signature entitySignature)
	{
		// Notify each system that an entity's signature changed
		for (auto const& pair : mSystems)
		{
			auto const& type = pair.first;
			auto const& system = pair.second;
			auto const& systemSignature = mSignatures[type];

			// Entity signature matches system signature - insert into set
			if ((entitySignature & systemSignature) == systemSignature)
			{
				system->Entities.insert(entity);
			}
			// Entity signature does not match system signature - erase from set
			else
			{
				system->Entities.erase(entity);
			}
		}

	}
};

