#pragma once
#include"EntityManager.h"
#include"ComponentsManager.h"
#include"SystemManager.h"
//#include<memory>
#include<unordered_map>
#include"SomeDef.h"
//#include"System.h"
//extern class SystemManager;
class Manager
{
private:
	// here the manager has a pointer for ever
	unique_ptr<ComponentsManager> mComponentManager;
	unique_ptr<EntityManager> mEntityManager;
	unique_ptr<SystemManager> mSystemManager;
public:
	void Manager::Init()
	{
		// Create pointers to each manager
		mComponentManager = make_unique<ComponentsManager>();
		mEntityManager = make_unique<EntityManager>();
		mSystemManager = make_unique<SystemManager>();
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Entity functions
	Entity Manager::CreateEntity()
	{
		return mEntityManager->CreateEntity();
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	void Manager::DestroyEntity(Entity entity)
	{
		mEntityManager->DestroyEntity(entity);

		mComponentManager->EntityDestroyed(entity);

		mSystemManager->EntityDestroyedd(entity);
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Component functions
	template<typename T>
	void RegisterComponent()
	{
		mComponentManager->RegisterComponent<T>();
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T>
	void AddComponent(Entity entity, T component)
	{
		mComponentManager->AddComponent<T>(entity, component);

		auto signature = mEntityManager->GetSignature(entity);
		signature.set(mComponentManager->GetComponentType<T>(), true);
		mEntityManager->SetSignature(entity, signature);

		mSystemManager->EntitySignatureChanged(entity, signature);
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T>
	void RemoveComponent(Entity entity)
	{
		mComponentManager->RemoveComponent<T>(entity);

		auto signature = mEntityManager->GetSignature(entity);
		signature.set(mComponentManager->GetComponentType<T>(), false);
		mEntityManager->SetSignature(entity, signature);

		mSystemManager->EntitySignatureChanged(entity, signature);
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T>
	T* GetComponent(Entity entity)
	{
		return mComponentManager->GetComponent<T>(entity);
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T>
	Components GetComponentType()
	{
		return mComponentManager->GetComponentType<T>();
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	// System functions
	template<typename T>
	shared_ptr<T> RegisterSystem()
	{
		return mSystemManager->RegisterSystem<T>();
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T>
	void SetSystemSignature(Signature signature)
	{
		mSystemManager->SetSignature<T>(signature);
	}



};

