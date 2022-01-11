#include "CollisionTestTerrainCommand.h"
#include "CollidableGroup.h"
#include "Collidable.h"
#include "Terrain.h"
#include "TerrainRectangleArea.h"
#include "AABBCell.h"

#include "CollisionVolumeAABB.h"
#include "CollisionVolumeBSphere.h"

#include "SceneManager.h"
#include "Scene.h"

#include "MathTools.h"
#include "Visualizer.h"
#include "Colors.h"

#ifndef CollisionTestTerrainCommand_DEBUG
#define CollisionTestTerrainCommand_DEBUG 1
#endif // !CollisionTestTerrainCommand_DEBUG

CollisionTestTerrainCommand::CollisionTestTerrainCommand(CollidableGroup* pCollidableGroup)
	: _pCollidableGroup(pCollidableGroup)
{}

CollisionTestTerrainCommand::~CollisionTestTerrainCommand()
{
	//delete _pCollisionDispatch;
}

void CollisionTestTerrainCommand::execute()
{
#if CollisionTestTerrainCommand_DEBUG
	debugTestCollisionGroup(_pCollidableGroup);
#else
	testCollisionGroup(_pCollidableGroup);
#endif // CollisionTestTerrainCommand_DEBUG

}

//-----------------------------------------------------------------------------------------------------------------------------
// Execute helpers
//-----------------------------------------------------------------------------------------------------------------------------
void CollisionTestTerrainCommand::testCollisionGroup(CollidableGroup* pCollidableGroup) const
{
	const Terrain* pTerrain = SceneManager::GetCurrentScene()->getTerrain();
	const CollidableGroup::Collection& collection = pCollidableGroup->getColliderCollection();

	for (Collidable* pCollidable : collection)
	{
		TerrainRectangleArea candidateCells = pTerrain->getTerrainRectangleArea(pCollidable);

		for (auto& aabbCell : candidateCells)
		{
			CollisionVolumeAABB AABB;
			AABB.setMinMaxWorldVertex(aabbCell._minVertex, aabbCell._maxVertex);

			// If BSphere intersects  AABB cell then...
			if (MathTools::Intersect(pCollidable->getBSphere(), AABB))
			{
				// If Collision Volume intersects  AABB cell then...
				if (MathTools::Intersect(pCollidable->getCollisionVolume(), AABB))
				{
					processCallback(pCollidable);
				}
			}
		}
	}
}

void CollisionTestTerrainCommand::debugTestCollisionGroup(CollidableGroup* pCollidableGroup) const
{
	const Terrain* pTerrain = SceneManager::GetCurrentScene()->getTerrain();
	const CollidableGroup::Collection& collection = pCollidableGroup->getColliderCollection();

	for (Collidable* pCollidable : collection)
	{
		TerrainRectangleArea candidateCells = pTerrain->getTerrainRectangleArea(pCollidable);
		
		CollisionVolumeAABB DebugAABB;
		DebugAABB.computeData(pCollidable->getBSphere());
		Visualizer::ShowCollisionVolume(DebugAABB, Colors::Black);
		Visualizer::ShowCollisionVolume(pCollidable->getBSphere(), Colors::Green);

		for (auto& aabbCell : candidateCells)
		{
			CollisionVolumeAABB AABB;
			AABB.setMinMaxWorldVertex(aabbCell._minVertex, aabbCell._maxVertex);

			bool doesIntersect = false;
			// If BSphere intersects  AABB cell then...
			if (MathTools::Intersect(pCollidable->getBSphere(), AABB))
			{
				// If Collision Volume intersects  AABB cell then...
				if (MathTools::Intersect(pCollidable->getCollisionVolume(), AABB))
				{
					Visualizer::ShowCollisionVolume(AABB, Colors::Green);
					doesIntersect = true;
				}
				else // It does not intersect
				{
					Visualizer::ShowCollisionVolume(AABB, Colors::Yellow);
				}
			}
			else // It does not intersect
			{
				Visualizer::ShowCollisionVolume(AABB, Colors::Red);
			}

			if (doesIntersect)
			{
				processCallback(pCollidable);
			}
		}
	}
}

void CollisionTestTerrainCommand::processCallback(Collidable* pCollidable) const
{
	pCollidable->terrainCollision();
}