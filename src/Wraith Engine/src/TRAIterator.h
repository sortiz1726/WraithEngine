#ifndef _TRAIterator
#define _TRAIterator

class TerrainRectangleArea;
struct AABBCell;

class TRAIterator
{
public:
	TRAIterator() = delete;
	TRAIterator(const TRAIterator&) = default;
	TRAIterator& operator=(const TRAIterator&) = default;
	TRAIterator(TRAIterator&&) = default;
	TRAIterator& operator=(TRAIterator&&) = default;
	~TRAIterator() = default;

	TRAIterator(TerrainRectangleArea*, int row, int column);

	const AABBCell& operator->();
	const AABBCell& operator*();
	TRAIterator& operator++();
	bool operator!=(const TRAIterator&) const;
	bool operator==(const TRAIterator&) const;

private:
	TerrainRectangleArea* _pTerrainRectangleArea;
	int _currentRow;
	int _currentColumn;
};
#endif // !_TRAIterator

//-----------------------------------------------------------------------------------------------------------------------------
// TRAIterator Comment Template
//-----------------------------------------------------------------------------------------------------------------------------