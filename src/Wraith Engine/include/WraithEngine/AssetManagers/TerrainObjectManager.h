#ifndef _TerrainObjectManager
#define _TerrainObjectManager

#include <string>
#include <map>

class TerrainObject;

/**********************************************************************************************//**
 * <summary> Manager for Terrain Objects. 
 * 			 For loading terrain and accessing them within user defined games object
 * 			 </summary>
 *
 * <remarks> </remarks>
 **************************************************************************************************/

class TerrainObjectManager
{
	friend class TerrainObjectManagerAttorney;

private:
	typedef std::string MapKey;
	typedef std::map<MapKey, TerrainObject*> TerrainObjectMap;

private:
	static TerrainObjectManager* pTerrainObjectManagerInstance;

	// Big Six
	TerrainObjectManager();
	TerrainObjectManager(const TerrainObjectManager&) = delete;
	TerrainObjectManager& operator=(const TerrainObjectManager&) = delete;
	TerrainObjectManager(const TerrainObjectManager&&) = delete;
	TerrainObjectManager& operator=(TerrainObjectManager&&) = delete;
	~TerrainObjectManager();

	// Getting Model Manager
	static TerrainObjectManager& GetInstance();
	
	// Setting Default Path
	void privSetDefaultPath(const std::string& defaultPath);

	// Loading Terrain Model
	void privLoadAndAssignKey(const std::string& fileName, float sideLength,
		float maxHeight, float assignedGroundLevel,
		const std::string& textureName,
		int uRepeat, int vRepeat, const MapKey& key);

	// ---> Loading Models helper
	bool hasKeyBeenAssigned(const MapKey& key) const;
	void printKeyAssignedErrorAndTerminate(const MapKey& key) const;

	bool isFilePathValid(const std::string& fileName) const;
	void printFileNameErrorAndTerminate(const std::string& fileName) const;
	
	void printTerrainObjectLoadedSuccessfully(const std::string& fileName) const;
	
	// Getting Terrain Object
	TerrainObject* getTerrainObject(const MapKey& key) const;

	// ---> Getting Terrain Object helpers
	TerrainObject* tryToGetTerrainObject(const MapKey& key) const;
	
	// Termination
	static void Delete();

	// ---> Termination helper
	void deleteAllTerrainObjects();

public:
	/**********************************************************************************************//**
	 * <summary> Sets default file path to access terrain model files.</summary>
	 * \ingroup TERRAINRESOURCES
	 * <remarks> </remarks>
	 *
	 * <param name="defaultPath"> The default file path.</param>
	 **************************************************************************************************/
	static void SetDefaultPath(const std::string& defaultPath)
	{
		GetInstance().privSetDefaultPath(defaultPath);
	}

	/**********************************************************************************************//**
	 * <summary> Loads terrains and assigns a user define key.</summary>
	 * \ingroup TERRAINRESOURCES
	 * <remarks> MUST be called after all calls to TextureManager::LoadTextureAndAssignKey(),
	 *			 since it retrives texture based on name assigned to TextureManager. </remarks>
	 *
	 * <param name="fileName"> name of azul model file.</param>
	 * <param name="sideLength"> side length of terrain square.</param>
	 * <param name="maxHeight"> the maximum height of the terrain model can be.</param>
	 * <param name="assignedGroundLevel"> the ground level of terrain (or the minimum y-level the lowest point can be).</param>
	 * <param name="uRepeat"> the U (or horizontal) repeat of texture.</param>
	 * <param name="vRepeat"> the V (or vertical) repeat of texture.</param>
	 * <param name="key">	   user define key to associate with terrain object.</param>
	 **************************************************************************************************/
	static void LoadAndAssignKey(const std::string& fileName, float sideLength,
		float maxHeight, float assignedGroundLevel,
		const std::string& textureName,
		int uRepeat, int vRepeat, const MapKey& key)
	{
		TerrainObjectManager::GetInstance().privLoadAndAssignKey(fileName, sideLength,
			maxHeight, assignedGroundLevel,
			textureName,
			uRepeat, vRepeat, key);
	}

	/**********************************************************************************************//**
	 * <summary> Gets a Terrain Object with user defined key.</summary>
	 * \ingroup TERRAINRESOURCES
	 * <remarks> </remarks>
	 *
	 * <param name="key"> The user defined key associated to a Terrain Object.</param>
	 *
	 * <returns> A TerrainObject.</returns>
	 **************************************************************************************************/
	static TerrainObject* GetTerrainObject(const MapKey& key)
	{
		return TerrainObjectManager::GetInstance().getTerrainObject(key);
	}

private:
	std::string _defaultPath;

	TerrainObjectMap _storageMap;

	// For personal debugging
private:
	static void DebugPrint(const std::string& message);
	
	template<typename ...Args>
	static void DebugPrintf(const char* format, Args... args);

	static const std::string DEBUG_TITLE_MESSAGE;
};

// For personal debugging
#ifndef TerrainObjectManager_DEBUG
#define TerrainObjectManager_DEBUG false
#endif !TerrainObjectManager_DEBUG

template<typename... Args>
void TerrainObjectManager::DebugPrintf(const char* format, Args... args)
{
#if TerrainObjectManager_DEBUG
	std::string stringFormat = std::string(format);
	if (stringFormat.size() == 0)
	{
		Trace::out("\n");
	}
	else
	{
		std::string finalMessage = TerrainObjectManager::DEBUG_TITLE_MESSAGE + stringFormat + "\n";
		Trace::out(finalMessage.c_str(), args...);
	}
#endif TerrainObjectManager_DEBUG
}

#endif _TerrainObjectManager

//-----------------------------------------------------------------------------------------------------------------------------
// TerrainObjectManager Comment Template
//-----------------------------------------------------------------------------------------------------------------------------