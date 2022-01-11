#include "TerrainRectangleArea.h"

TerrainRectangleArea::TerrainRectangleArea(const Terrain* pTerrain,
	const AABBCellIndex& minIndex, const AABBCellIndex& maxIndex)
	: _pTerrain(pTerrain),
	_minIndex(minIndex), _maxIndex(maxIndex),
	_beginIt(this, _minIndex._row, _minIndex._column),
	_endIt(this, _maxIndex._row + 1, _minIndex._column)
{}

const Terrain* TerrainRectangleArea::getTerrain() const
{
	return _pTerrain;
}

const AABBCellIndex& TerrainRectangleArea::getMinIndex() const
{
	return _minIndex;
}

const AABBCellIndex& TerrainRectangleArea::getMaxIndex() const
{
	return _maxIndex;
}

const TRAIterator& TerrainRectangleArea::begin()
{
	return _beginIt;
}

const TRAIterator& TerrainRectangleArea::end()
{
	return _endIt;
}
