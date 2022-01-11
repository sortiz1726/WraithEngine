#include "CollisionVolumeAttorney.h"
#include "CollisionVolume.h"

void CollisionVolumeAttorney::DebugDrawAccess::DebugDraw(const CollisionVolume& collisionVolume, const Vect& color, int depth)
{
	collisionVolume.debugDraw(color, depth);
}

bool CollisionVolumeAttorney::IntersectAccess::IntersectAccept(const CollisionVolume& collisionVolume_1, const CollisionVolume& collisionVolume_2)
{
	return collisionVolume_1.intersectAccept(collisionVolume_2);
}

bool CollisionVolumeAttorney::IntersectAccess::IntersectVisitor(const CollisionVolume& collisionVolume, const CollisionVolumeBSphere& BSphere)
{
	return collisionVolume.intersectVisitor(BSphere);
}

bool CollisionVolumeAttorney::IntersectAccess::IntersectVisitor(const CollisionVolume& collisionVolume, const CollisionVolumeAABB& AABB)
{
	return collisionVolume.intersectVisitor(AABB);
}
