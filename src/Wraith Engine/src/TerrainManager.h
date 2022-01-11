#ifndef _TerrainManager
#define _TerrainManager

#include <string>

class Terrain;
class NullTerrain;

class TerrainManager
{
public:
	TerrainManager();
	TerrainManager(const TerrainManager&) = delete;
	TerrainManager& operator=(const TerrainManager&) = delete;
	TerrainManager(TerrainManager&&) = delete;
	TerrainManager& operator=(TerrainManager&&) = delete;
	~TerrainManager();

	void setTerrain(const std::string& terrainObjectName);
	Terrain* getTerrain() const;

	void deregisterTerrain();

private:
	Terrain* _pTerrain;

	NullTerrain* _pNullTerrain;
};
#endif // !_TerrainManager

//-----------------------------------------------------------------------------------------------------------------------------
// TerrainManager Comment Template
//-----------------------------------------------------------------------------------------------------------------------------