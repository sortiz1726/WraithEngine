#include "WallBuilder.h"
#include "GameObjectStorage.h"
#include "Wall.h"
#include "vmath.h"

WallBuilder::WallBuilder()
	: _pWallStorage(new GameObjectStorage())
{}

WallBuilder::~WallBuilder()
{
	delete _pWallStorage;
}

Vect WallBuilder::buildWalls(const Vect& startPosition, float buildAngle, int numberOfWalls)
{
	float wallLength = 14.0f;

	Vect moveOffset = Vect(wallLength, 0.0f, 0.0f);
	moveOffset *= Matrix(RotType::ROT_Y, vmath::radians(buildAngle));

	Vect buildPosition = startPosition;

	for (int i = 0; i < numberOfWalls; i++)
	{
		Wall* pWall = new Wall();
		pWall->initialize(buildPosition, buildAngle);
		buildPosition += moveOffset;
		_pWallStorage->addGameObject(pWall);
	}

	return buildPosition;
}
