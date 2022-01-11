#include "CollisionDeregisterCommand.h"
#include "CollidableAttorney.h"

CollisionDeregisterCommand::CollisionDeregisterCommand(Collidable* pCollidable)
	: _pCollidable(pCollidable)
{}

void CollisionDeregisterCommand::execute()
{
	CollidableAttorney::RegistrationAccess::DeregisterFromScene(_pCollidable);
}
