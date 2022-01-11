#include "DrawCollisionVolumes.h"
#include "Visualizer.h"


DrawCollisionVolumes::DrawCollisionVolumes()
{
	submitUpdateRegistration();
}

void DrawCollisionVolumes::addCollisionVolume(const CollisionVolumeOBB& collisionVolume)
{
	_collisionVolumes.push_back(collisionVolume);
}

void DrawCollisionVolumes::update()
{
	for (auto& collisionVolume : _collisionVolumes)
	{
		Visualizer::ShowCollisionVolume(collisionVolume);
	}
}
