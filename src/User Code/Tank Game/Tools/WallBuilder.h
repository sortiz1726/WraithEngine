#ifndef _WallBuilder
#define _WallBuilder

class Wall;
class GameObjectStorage;
class Vect;

class WallBuilder
{
public:
	WallBuilder();
	WallBuilder(const WallBuilder&) = default;
	WallBuilder& operator=(const WallBuilder&) = default;
	WallBuilder(WallBuilder&&) = default;
	WallBuilder& operator=(WallBuilder&&) = default;
	~WallBuilder();

	Vect buildWalls(const Vect& startPosition, float buildAngle, int numberOfWalls);

private:
	void deleteGameObjects();

private:
	GameObjectStorage* _pWallStorage;
};
#endif // !_WallBuilder

//-----------------------------------------------------------------------------------------------------------------------------
// WallBuilder Comment Template
//-----------------------------------------------------------------------------------------------------------------------------