#include "CollisionRegisterCommand.h"
#include "CollidableAttorney.h"

CollisionRegisterCommand::CollisionRegisterCommand(Collidable* pCollidable)
	: _pCollidable(pCollidable)
{}

void CollisionRegisterCommand::execute()
{
	CollidableAttorney::RegistrationAccess::RegisterToScene(_pCollidable);
}
