#ifndef _TerrainRectangleArea
#define _TerrainRectangleArea

#include "TRAIterator.h"
#include "AABBCellIndex.h"

class Terrain;

class TerrainRectangleArea
{
public:
	TerrainRectangleArea() = delete;
	TerrainRectangleArea(const TerrainRectangleArea&) = default;
	TerrainRectangleArea& operator=(const TerrainRectangleArea&) = default;
	TerrainRectangleArea(TerrainRectangleArea&&) = default;
	TerrainRectangleArea& operator=(TerrainRectangleArea&&) = default;
	~TerrainRectangleArea() = default;

	TerrainRectangleArea(const Terrain*, const AABBCellIndex& minIndex, const AABBCellIndex& maxIndex);

	const Terrain* getTerrain() const;

	const AABBCellIndex& getMinIndex() const;
	const AABBCellIndex& getMaxIndex() const;

	const TRAIterator& begin();
	const TRAIterator& end();

private:
	const Terrain* _pTerrain;

	AABBCellIndex _minIndex;
	AABBCellIndex _maxIndex;

	TRAIterator _beginIt;
	TRAIterator _endIt;

};
#endif // !_TerrainRectangleArea

//-----------------------------------------------------------------------------------------------------------------------------
// TerrainRectangleArea Comment Template
//-----------------------------------------------------------------------------------------------------------------------------