#include "CollisionVolumeBSphere.h"
#include <algorithm>
#include <array>
#include "CollisionVolumeOBB.h"
#include "Triangle.h"
#include "MathTools.h"
#include "VisualizerAttorney.h"

CollisionVolumeBSphere::CollisionVolumeBSphere()
	: _center(Vect(0.0f, 0.0f, 0.0f)),
	_radius(0.0f)
{}

void CollisionVolumeBSphere::computeData(Model* pModel, const Matrix& world)
{
	// Calculate Center
	_center = pModel->getCenter() * world;

	// Calculate Radius (assume uniform scale)
	_radius = pModel->getRadius() * MathTools::ExtractScaleX(world);
}

void CollisionVolumeBSphere::computeData(const CollisionVolumeOBB& OBB)
{
	// Calculate Center
	_center = OBB.getWorldCenter();

	// Calculate Radius (assume uniform scale)
	_radius = (OBB.getLocalHalfDiagonal() * MathTools::ExtractScaleX(OBB.getWorldMatrix())).mag();
}

void CollisionVolumeBSphere::computeData(const Triangle& triangle)
{
	Vect minValues = MathTools::Min(triangle.getVertex0(), triangle.getVertex1());
	Vect maxValues = MathTools::Max(triangle.getVertex0(), triangle.getVertex1());
	minValues = MathTools::Min(minValues, triangle.getVertex2());
	maxValues = MathTools::Max(maxValues, triangle.getVertex2());

	_center = (maxValues + minValues) * 0.5f;
	_radius = ((maxValues - minValues) * 0.5f).mag();
}

//-----------------------------------------------------------------------------------------------------------------------------
// Intersections
//-----------------------------------------------------------------------------------------------------------------------------
bool CollisionVolumeBSphere::intersectAccept(const CollisionVolume& collisionVolume) const
{
	return collisionVolume.intersectVisitor(*this);
}

bool CollisionVolumeBSphere::intersectVisitor(const CollisionVolumeBSphere& collisionBSphere) const
{
	return MathTools::Intersect(*this, collisionBSphere);
}

bool CollisionVolumeBSphere::intersectVisitor(const CollisionVolumeAABB& AABB) const
{
	return MathTools::Intersect(*this, AABB);
}

bool CollisionVolumeBSphere::intersectVisitor(const CollisionVolumeOBB& OBB) const
{
	return MathTools::Intersect(*this, OBB);
}

bool CollisionVolumeBSphere::intersectVisitor(const CollisionVolumeOctree& Octree) const
{
	return MathTools::Intersect(*this, Octree);
}

//-----------------------------------------------------------------------------------------------------------------------------
// Debugging
//-----------------------------------------------------------------------------------------------------------------------------
void CollisionVolumeBSphere::debugDraw(const Vect& color, int depth) const
{
	depth; // is ignored
	VisualizerAttorney::RenderAccess::ShowBSphere(*this, color);
}

//-----------------------------------------------------------------------------------------------------------------------------
// Getters
//-----------------------------------------------------------------------------------------------------------------------------
const Vect& CollisionVolumeBSphere::getCenter() const
{
	return _center;
}

float CollisionVolumeBSphere::getRadius() const
{
	return _radius;
}

int CollisionVolumeBSphere::getMaxDepth() const
{
	return 0;
}
