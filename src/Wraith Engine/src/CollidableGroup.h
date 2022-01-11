#ifndef _CollidableGroup
#define _CollidableGroup

#include <list>

class Collidable;
class CollisionVolumeAABB;

/**********************************************************************************************//**
 * <summary> A collidable group holding collidables of a specific type</summary>
 *
 * <remarks> </remarks>
 **************************************************************************************************/
class CollidableGroup
{
public:
	typedef std::list<Collidable*> Collection;
	typedef Collection::iterator StorageReference;

public:
	CollidableGroup();
	CollidableGroup(const CollidableGroup&) = default;
	CollidableGroup& operator=(const CollidableGroup&) = default;
	CollidableGroup(CollidableGroup&&) = default;
	CollidableGroup& operator=(CollidableGroup&&) = default;
	~CollidableGroup();

	/**********************************************************************************************//**
	 * <summary> Registers the entity.</summary>
	 *
	 * <remarks> </remarks>
	 *
	 * <param name="pCollidable"> the collidable.</param>
	 * <param name="rStorageReference"> [in,out] The storage reference.</param>
	 **************************************************************************************************/
	void registerEntity(Collidable* pCollidable, StorageReference& rStorageReference);

	/**********************************************************************************************//**
	 * <summary> Deregisters the entity described by StorageReference.</summary>
	 *
	 * <remarks> </remarks>
	 *
	 * <param name="StorageReference"> The storage reference.</param>
	 **************************************************************************************************/
	void deregisterEntity(const StorageReference& StorageReference);

	void updateGroupAABB();

	// Getting Collider Collection
	const Collection& getColliderCollection() const;

	const CollisionVolumeAABB& getGroupAABB() const;

	bool isEmpty() const;

private:
	Collection _registeredEntities;
	CollisionVolumeAABB* _pGroupAABB;
};
#endif // !_CollidableGroup

//-----------------------------------------------------------------------------------------------------------------------------
// CollidableGroup Comment Template
//-----------------------------------------------------------------------------------------------------------------------------