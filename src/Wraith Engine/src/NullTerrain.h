#ifndef _NullTerrain
#define _NullTerrain

#include "Terrain.h"
#include "AABBCell.h"

class NullTerrain : public Terrain
{
public:
	NullTerrain() = default;
	NullTerrain(const NullTerrain&) = default;
	NullTerrain& operator=(const NullTerrain&) = default;
	NullTerrain(NullTerrain&&) = default;
	NullTerrain& operator=(NullTerrain&&) = default;
	~NullTerrain() = default;

	// Inherited via Terrain
	virtual void submitTerrainDrawRegistration() override;
	virtual void submitTerrainDrawDeregistration() override;
	virtual void intersect(Collidable*) const override;

	// Inherited via Terrain
	virtual TerrainRectangleArea getTerrainRectangleArea(Collidable*) const override;
	virtual const AABBCell& getAABBCellAt(int row, int column) const override;
	virtual Vect computePointOnTerrainObject(const Vect& position) const override;
	virtual Vect computeNormalOnTerrainObject(const Vect& position) const override;
	virtual void visualizeCellAt(const Vect& position) const override;

private:
	AABBCell _nullAABBCell;

};
#endif // !_NullTerrain

//-----------------------------------------------------------------------------------------------------------------------------
// NullTerrain Comment Template
//-----------------------------------------------------------------------------------------------------------------------------