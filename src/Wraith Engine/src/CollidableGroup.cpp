#include "CollidableGroup.h"
#include "CollidableAttorney.h"
#include "CollisionVolumeAABB.h"
#include "MathTools.h"

CollidableGroup::CollidableGroup()
	: _pGroupAABB(new CollisionVolumeAABB())
{}

CollidableGroup::~CollidableGroup()
{
	delete _pGroupAABB;
}

//-----------------------------------------------------------------------------------------------------------------------------
// Registration/Deregistration
//-----------------------------------------------------------------------------------------------------------------------------
void CollidableGroup::registerEntity(Collidable* pCollidable, StorageReference& deleteReference)
{
	deleteReference = _registeredEntities.insert(_registeredEntities.end(), pCollidable);
}

void CollidableGroup::deregisterEntity(const StorageReference& deleteReference)
{
	_registeredEntities.erase(deleteReference);
}

//-----------------------------------------------------------------------------------------------------------------------------
// Getting Collider Collection
//-----------------------------------------------------------------------------------------------------------------------------
const CollidableGroup::Collection& CollidableGroup::getColliderCollection() const
{
	return _registeredEntities;
}

const CollisionVolumeAABB& CollidableGroup::getGroupAABB() const
{
	return *_pGroupAABB;
}

void CollidableGroup::updateGroupAABB()
{
	Vect minVertex = Vect(0.0f, 0.0f, 0.0f);
	Vect maxVertex = Vect(0.0f, 0.0f, 0.0f);

	if (!_registeredEntities.empty())
	{
		CollisionVolumeAABB aabb;
		StorageReference itCollidable = _registeredEntities.begin();
		
		Collidable* pCollidable = *itCollidable;

		aabb.computeData(pCollidable->getBSphere());

		minVertex = aabb.getMinWorldVertex();
		maxVertex = aabb.getMaxWorldVertex();

		++itCollidable;

		while (itCollidable != _registeredEntities.end())
		{
			pCollidable = *itCollidable;
			aabb.computeData(pCollidable->getBSphere());

			minVertex.set(MathTools::Min(aabb.getMinWorldVertex(), minVertex));
			maxVertex.set(MathTools::Max(aabb.getMaxWorldVertex(), maxVertex));

			++itCollidable;
		}
	}

	_pGroupAABB->setMinMaxWorldVertex(minVertex, maxVertex);
}

bool CollidableGroup::isEmpty() const
{
	return _registeredEntities.empty();
}