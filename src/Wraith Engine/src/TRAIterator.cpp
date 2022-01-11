#include "TRAIterator.h"
#include "TerrainRectangleArea.h"
#include "Terrain.h"

TRAIterator::TRAIterator(TerrainRectangleArea* pTerrainRectangleArea,
	int row, int column)
	: _pTerrainRectangleArea(pTerrainRectangleArea),
	_currentRow(row), _currentColumn(column)
{}

const AABBCell& TRAIterator::operator->()
{
	const Terrain* pTerrain = _pTerrainRectangleArea->getTerrain();
	return pTerrain->getAABBCellAt(_currentRow, _currentColumn);
}

const AABBCell& TRAIterator::operator*()
{
	const Terrain* pTerrain = _pTerrainRectangleArea->getTerrain();
	return pTerrain->getAABBCellAt(_currentRow, _currentColumn);
}

TRAIterator& TRAIterator::operator++()
{
	_currentColumn += 1;
	const AABBCellIndex& maxIndex = _pTerrainRectangleArea->getMaxIndex();
	if (_currentColumn > maxIndex._column)
	{
		const AABBCellIndex& minIndex = _pTerrainRectangleArea->getMinIndex();
		_currentColumn = minIndex._column;
		_currentRow += 1;
	}

	return *this;
}

bool TRAIterator::operator!=(const TRAIterator& TRAIterator) const
{
	return !(this->operator==(TRAIterator));
}

bool TRAIterator::operator==(const TRAIterator& TRAIterator) const
{
	return (_currentRow == TRAIterator._currentRow) 
		&& (_currentColumn == TRAIterator._currentColumn);
}
