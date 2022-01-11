#include "TerrainManager.h"
#include "TerrainObjectManager.h"
#include "TerrainObject.h"
#include "NullTerrain.h"

TerrainManager::TerrainManager()
	: _pTerrain(nullptr),
	_pNullTerrain(new NullTerrain())
{
	_pTerrain = _pNullTerrain;
}

TerrainManager::~TerrainManager()
{
	delete _pNullTerrain;
}

void TerrainManager::setTerrain(const std::string& terrainObjectName)
{
	_pTerrain->submitTerrainDrawDeregistration();
	_pTerrain = TerrainObjectManager::GetTerrainObject(terrainObjectName);
	_pTerrain->submitTerrainDrawRegistration();
}

Terrain* TerrainManager::getTerrain() const
{
	return _pTerrain;
}

void TerrainManager::deregisterTerrain()
{
	_pTerrain->submitTerrainDrawDeregistration();
	_pTerrain = _pNullTerrain;
	_pTerrain->submitTerrainDrawRegistration();
}
