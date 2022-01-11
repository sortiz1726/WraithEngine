#ifndef _CollisionDeregisterCommand
#define _CollisionDeregisterCommand

#include "SceneRegistrationCommand.h"

class Collidable;

class CollisionDeregisterCommand : public SceneRegistrationCommand
{
public:
	CollisionDeregisterCommand() = delete;
	CollisionDeregisterCommand(const CollisionDeregisterCommand&) = default;
	CollisionDeregisterCommand& operator=(const CollisionDeregisterCommand&) = default;
	CollisionDeregisterCommand(CollisionDeregisterCommand&&) = default;
	CollisionDeregisterCommand& operator=(CollisionDeregisterCommand&&) = default;
	// Is it a base class? Should it be virtual?
	~CollisionDeregisterCommand() = default;

	CollisionDeregisterCommand(Collidable*);

	void execute();

private:
	Collidable* _pCollidable;
};
#endif // !_CollisionDeregisterCommand

//-----------------------------------------------------------------------------------------------------------------------------
// CollisionDeregisterCommand Comment Template
//-----------------------------------------------------------------------------------------------------------------------------