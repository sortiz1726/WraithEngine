#ifndef _CollisionRegisterCommand
#define _CollisionRegisterCommand

#include "SceneRegistrationCommand.h"

class Collidable;

class CollisionRegisterCommand : public SceneRegistrationCommand
{
public:
	CollisionRegisterCommand() = delete;
	CollisionRegisterCommand(const CollisionRegisterCommand&) = default;
	CollisionRegisterCommand& operator=(const CollisionRegisterCommand&) = default;
	CollisionRegisterCommand(CollisionRegisterCommand&&) = default;
	CollisionRegisterCommand& operator=(CollisionRegisterCommand&&) = default;
	// Is it a base class? Should it be virtual?
	~CollisionRegisterCommand() = default;

	CollisionRegisterCommand(Collidable*);

	void execute();

private:
	Collidable* _pCollidable;
};
#endif // !_CollisionRegisterCommand

//-----------------------------------------------------------------------------------------------------------------------------
// CollisionRegisterCommand Comment Template
//-----------------------------------------------------------------------------------------------------------------------------