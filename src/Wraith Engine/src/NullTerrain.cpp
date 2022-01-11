#include "NullTerrain.h"
#include "AABBCellIndex.h"
#include "TerrainRectangleArea.h"

void NullTerrain::submitTerrainDrawRegistration()
{
	// Does nothing
}

void NullTerrain::submitTerrainDrawDeregistration()
{
	// Does nothing
}

void NullTerrain::intersect(Collidable*) const
{
	// Does nothing
}

TerrainRectangleArea NullTerrain::getTerrainRectangleArea(Collidable*) const
{
	AABBCellIndex minIndex;
	AABBCellIndex maxIndex;
	return TerrainRectangleArea(this, minIndex, maxIndex);
}

const AABBCell& NullTerrain::getAABBCellAt(int, int) const
{
	return _nullAABBCell;
}

Vect NullTerrain::computePointOnTerrainObject(const Vect& position) const
{
	return position;
}

Vect NullTerrain::computeNormalOnTerrainObject(const Vect&) const
{
	return Vect(0.0f, 1.0f, 0.0f);
}

void NullTerrain::visualizeCellAt(const Vect&) const
{
	// does nothing
}
