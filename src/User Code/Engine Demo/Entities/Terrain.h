#ifndef _Terrain
#define _Terrain

class Collidable;
class TerrainRectangleArea;
struct AABBCell;
class Vect;

class Terrain
{
public:
	Terrain() = default;
	Terrain(const Terrain&) = default;
	Terrain& operator=(const Terrain&) = default;
	Terrain(Terrain&&) = default;
	Terrain& operator=(Terrain&&) = default;
	virtual ~Terrain() = default;

	virtual void submitTerrainDrawRegistration() = 0;
	virtual void submitTerrainDrawDeregistration() = 0;

	// Not being used anymore, replaced by using Iterator to traverse and test cells
	virtual void intersect(Collidable*) const = 0;

	virtual TerrainRectangleArea getTerrainRectangleArea(Collidable*) const = 0;
	virtual const AABBCell& getAABBCellAt(int row, int column) const = 0;

	virtual Vect computePointOnTerrainObject(const Vect& position) const = 0;
	virtual Vect computeNormalOnTerrainObject(const Vect& position) const = 0;

	virtual void visualizeCellAt(const Vect& position) const = 0;
};
#endif // !_Terrain

//-----------------------------------------------------------------------------------------------------------------------------
// Terrain Comment Template
//-----------------------------------------------------------------------------------------------------------------------------