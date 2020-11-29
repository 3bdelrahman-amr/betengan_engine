#pragma once
#include"AllComponents.h"
#include<unordered_map>
typedef long long ll;


/// <summary>
/// this is a generic component array that we can initialize severals ones 
/// for several components and access each entity components by thr entity's ID
/// 
/// </summary>


template<typename T>
class GenericArrayOfComponent:public AllComponents
{
private:
	

	array<T, MaxC> ComponentArray; // array thay contains generic componnents array 
	//we create array of the maximum coponents that we will use it
	
	unordered_map<Entity, ll> MapEntityToIndexMap; // map the entity id to the index ot the component that belongs to it

	
	unordered_map<ll, Entity> MapIndexToEntityMap; // mapt the component index to the entity that it belongs to it

	
	ll mSize;  // total size of the array of the coponents
public:
	
	void InsertData(Entity entity, T component)
	{
		//assert(MapEntityToIndexMap.find(entity) == MapEntityToIndexMap.end() && "Component added to same entity more than once.");

		// Put new entry at end and update the maps

		ll newIndex = mSize;
		MapEntityToIndexMap[entity] = newIndex;
		MapIndexToEntityMap[newIndex] = entity;
		ComponentArray[newIndex] = component;
		mSize++;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	void RemoveData(Entity entity)
	{
		assert(MapEntityToIndexMap.find(entity) != MapEntityToIndexMap.end() && "Removing non-existent component.");

		// Copy element at end into deleted element's place to maintain density
		ll indexOfRemovedEntity = MapEntityToIndexMap[entity];
		ll indexOfLastElement = mSize - 1;
		ComponentArray[indexOfRemovedEntity] = ComponentArray[indexOfLastElement];

		// Update map to point to moved spot
		Entity entityOfLastElement = MapIndexToEntityMap[indexOfLastElement];
		MapEntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
		MapIndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

		MapEntityToIndexMap.erase(entity);
		MapIndexToEntityMap.erase(indexOfLastElement);

		mSize--;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	T* GetData(Entity entity)
	{
		assert(MapEntityToIndexMap.find(entity) != MapEntityToIndexMap.end() && "Retrieving non-existent component.");

		// Return a reference to the entity's component
		return &ComponentArray[MapEntityToIndexMap[entity]];
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	void EntityDestroyed(Entity entity) override
	{
		if (MapEntityToIndexMap.find(entity) != MapEntityToIndexMap.end())
		{
			// Remove the entity's component if it existed
			RemoveData(entity);
		}
	}

	



};

