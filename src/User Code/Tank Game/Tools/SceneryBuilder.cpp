#include "SceneryBuilder.h"
#include "GameObject.h"
#include "WindMill.h"
#include "Warehouse.h"
#include "Cottage.h"
#include "LeaflessTree.h"
#include "Campfire.h"
#include "RoundArch.h"
#include "FlatArch.h"

SceneryBuilder::~SceneryBuilder()
{
	for (GameObject* sceneryEntity : _sceneryEntities)
	{
		delete sceneryEntity;
	}
}

void SceneryBuilder::buildWindMill(const Vect& position, float rotationY, float uniformScale)
{
	auto sceneryEntity = new WindMill();
	sceneryEntity->initialize(position, rotationY, uniformScale);
	_sceneryEntities.push_back(sceneryEntity);
}

Warehouse* SceneryBuilder::buildWarehouse(const Vect& position, float rotationY, float uniformScale)
{
	auto sceneryEntity = new Warehouse();
	sceneryEntity->initialize(position, rotationY, uniformScale);
	_sceneryEntities.push_back(sceneryEntity);
	return sceneryEntity;
}

void SceneryBuilder::buildCottage(const Vect& position, float rotationY, float uniformScale)
{
	auto sceneryEntity = new Cottage();
	sceneryEntity->initialize(position, rotationY, uniformScale);
	_sceneryEntities.push_back(sceneryEntity);
}

void SceneryBuilder::buildLeaflessTree(const Vect& position, float rotationY, float uniformScale)
{
	auto sceneryEntity = new LeaflessTree();
	sceneryEntity->initialize(position, rotationY, uniformScale);
	_sceneryEntities.push_back(sceneryEntity);
}

void SceneryBuilder::buildCampfire(const Vect& position, float rotationY, float uniformScale)
{
	auto sceneryEntity = new Campfire();
	sceneryEntity->initialize(position, rotationY, uniformScale);
	_sceneryEntities.push_back(sceneryEntity);
}

void SceneryBuilder::buildRoundArch(const Vect& position, float rotationY, float uniformScale)
{
	auto sceneryEntity = new RoundArch();
	sceneryEntity->initialize(position, rotationY, uniformScale);
	_sceneryEntities.push_back(sceneryEntity);
}

void SceneryBuilder::buildFlatArch(const Vect& position, float rotationY, float uniformScale)
{
	auto sceneryEntity = new FlatArch();
	sceneryEntity->initialize(position, rotationY, uniformScale);
	_sceneryEntities.push_back(sceneryEntity);
}