#ifndef _CollisionTestTerrainCommand
#define _CollisionTestTerrainCommand

#include "CollisionTestCommand.h"

class CollidableGroup;
class CollisionDispatchBase;
class Collidable;
class Terrain;

class CollisionTestTerrainCommand : public CollisionTestCommand
{
public:
	CollisionTestTerrainCommand() = delete;
	CollisionTestTerrainCommand(const CollisionTestTerrainCommand&) = default;
	CollisionTestTerrainCommand& operator=(const CollisionTestTerrainCommand&) = default;
	CollisionTestTerrainCommand(CollisionTestTerrainCommand&&) = default;
	CollisionTestTerrainCommand& operator=(CollisionTestTerrainCommand&&) = default;
	~CollisionTestTerrainCommand();

	CollisionTestTerrainCommand(CollidableGroup*);

	// Inherited via CollisionTestCommand
	virtual void execute() override;

private:
	void testCollisionGroup(CollidableGroup*) const;
	void debugTestCollisionGroup(CollidableGroup*) const;
	void processCallback(Collidable* pCollidable) const;

private:
	CollidableGroup* _pCollidableGroup;

};
#endif // !_CollisionTestTerrainCommand

//-----------------------------------------------------------------------------------------------------------------------------
// CollisionTestTerrainCommand Comment Template
//-----------------------------------------------------------------------------------------------------------------------------