#include "TerrainObjectManager.h"
#include "TerrainObject.h"
#include <cassert>
#include <exception>
#include "File.h"

TerrainObjectManager* TerrainObjectManager::pTerrainObjectManagerInstance = nullptr;

//-----------------------------------------------------------------------------------------------------------------------------
// Get Model Manager
//-----------------------------------------------------------------------------------------------------------------------------
TerrainObjectManager& TerrainObjectManager::GetInstance()
{
	if (pTerrainObjectManagerInstance == nullptr)
	{
		pTerrainObjectManagerInstance = new TerrainObjectManager();
	}
	assert(pTerrainObjectManagerInstance);
	return *pTerrainObjectManagerInstance;
}

//-----------------------------------------------------------------------------------------------------------------------------
// Instantiating Model Manager
//-----------------------------------------------------------------------------------------------------------------------------
TerrainObjectManager::TerrainObjectManager()
{
	TerrainObjectManager::DebugPrint("Default Constructor called");
	privSetDefaultPath("Terrains/");
	TerrainObjectManager::DebugPrint("");
}

//-----------------------------------------------------------------------------------------------------------------------------
// Setting Default Path
//-----------------------------------------------------------------------------------------------------------------------------
void TerrainObjectManager::privSetDefaultPath(const std::string& defaultPath)
{
	TerrainObjectManager::DebugPrint("Setting Default Path to \"" + defaultPath + "\"");
	_defaultPath = defaultPath;
}

//-----------------------------------------------------------------------------------------------------------------------------
// Loading Terrain
//-----------------------------------------------------------------------------------------------------------------------------
void TerrainObjectManager::privLoadAndAssignKey(const std::string& fileName, float sideLength, float maxHeight, float assignedGroundLevel, const std::string& textureName, int uRepeat, int vRepeat, const MapKey& key)
{
	if (hasKeyBeenAssigned(key)) printKeyAssignedErrorAndTerminate(key);

	const std::string filePath = TerrainObjectManager::_defaultPath + fileName;
	if (!isFilePathValid(filePath)) printFileNameErrorAndTerminate(fileName);

	TerrainObject* pTerrainObject = new TerrainObject(filePath.c_str(), sideLength, maxHeight, assignedGroundLevel, textureName, uRepeat, vRepeat);
	_storageMap.insert(std::make_pair(key, pTerrainObject));

	printTerrainObjectLoadedSuccessfully(fileName);
}

// Loading Models helper functions
bool TerrainObjectManager::hasKeyBeenAssigned(const MapKey& key) const
{
	return _storageMap.find(key) != _storageMap.end();
}

void TerrainObjectManager::printKeyAssignedErrorAndTerminate(const MapKey& key) const
{
	Trace::out("KEY - %s - for TERRAIN OBJECT has been used. Use another KEY name\n", key.c_str());
	throw std::exception();
	//std::terminate();
}

bool TerrainObjectManager::isFilePathValid(const std::string& filePath) const
{
	FileHandle fileHandle;
	FileError result = File::open(fileHandle, filePath.c_str(), FileMode::FILE_READ);
	File::close(fileHandle);
	return result == FileError::FILE_SUCCESS;
}

void TerrainObjectManager::printFileNameErrorAndTerminate(const std::string& fileName) const
{
	Trace::out("FILE NAME - %s - for TERRAIN OBJECT cannot be found. Check FILE NAME or ensure that terrain model file is in the TERRAINS FOLDER\n", fileName.c_str());
	throw std::exception();
}

void TerrainObjectManager::printTerrainObjectLoadedSuccessfully(const std::string& fileName) const
{
	Trace::out("Terrain Object Manager: %s loaded successfully\n", fileName.c_str());
}

//-----------------------------------------------------------------------------------------------------------------------------
// Getting Models
//-----------------------------------------------------------------------------------------------------------------------------

TerrainObject* TerrainObjectManager::getTerrainObject(const MapKey& key) const
{
	return tryToGetTerrainObject(key);
}

// Getting Models helper function
TerrainObject* TerrainObjectManager::tryToGetTerrainObject(const MapKey& key) const
{
	try
	{
		return _storageMap.at(key);
	}
	catch (std::out_of_range exception)
	{
		Trace::out("INVALID key - \"%s\" - for TERRAIN OBJECT storage map. CHECK if key is misspelled or if terrain object was loaded\n", key.c_str());
		throw exception;
		//std::terminate();
	}
}

//-----------------------------------------------------------------------------------------------------------------------------
// Deleting Models
//-----------------------------------------------------------------------------------------------------------------------------
void TerrainObjectManager::Delete()
{
	Trace::out("Model Manager: Deleting Model Manager\n");
	delete pTerrainObjectManagerInstance;
	pTerrainObjectManagerInstance = nullptr;
}

TerrainObjectManager::~TerrainObjectManager()
{
	TerrainObjectManager::DebugPrint("Destructor is called");
	deleteAllTerrainObjects();
	TerrainObjectManager::DebugPrint("");
}

void TerrainObjectManager::deleteAllTerrainObjects()
{
	TerrainObjectManager::DebugPrint("Deleting all Terrain Objects");
	for (auto& pair : _storageMap)
	{
		TerrainObjectManager::DebugPrint("Deleting \"" + pair.first + "\" Terrain Object");
		TerrainObject* pTerrainObject = pair.second;
		delete pTerrainObject;
	}
	TerrainObjectManager::DebugPrint("All Terrain Object have been deleted");
	_storageMap.clear();
}

//-----------------------------------------------------------------------------------------------------------------------------
// For personal debugging
//-----------------------------------------------------------------------------------------------------------------------------
const std::string TerrainObjectManager::DEBUG_TITLE_MESSAGE = "TerrainObjectManager_DEBUG: ";

void TerrainObjectManager::DebugPrint(const std::string& message)
{
	(void(message));
#if TerrainObjectManager_DEBUG
	if (message.size() == 0)
	{
		Trace::out("\n");
	}
	else
	{
		std::string finalMessage = TerrainObjectManager::DEBUG_TITLE_MESSAGE + message + std::string("\n");
		Trace::out("%s", finalMessage.c_str());
	}
#endif TerrainObjectManager_DEBUG
}