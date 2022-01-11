#ifndef _ShaderManager
#define _ShaderManager

#include <string>
#include <map>

class ShaderObject;

/**********************************************************************************************//**
 * <summary> Manager for shaders.
 * 			 For loading models and accessing them within user defined games object
 * 			 </summary>
 *
 * <remarks> </remarks>
 **************************************************************************************************/

class ShaderManager
{
	friend class ShaderManagerAttorney;
public:

	/**********************************************************************************************//**
	 * <summary> Values that represent default shaders.</summary>
	 * \ingroup SHADERRESOURCES
	 * <remarks> To be used in ShaderManager::GetDefaultShader(). </remarks>
	 **************************************************************************************************/
	enum class DefaultShader
	{
		TEXTURE,
		LIGHTED_TEXTURE,
		CONSTANT_COLOR,
		SPRITE
	};
private:
	typedef std::string MapKey;
	typedef std::map<MapKey, ShaderObject*> ShaderMap;

private:
	static ShaderManager* pShaderManagerInstance;

	// Big Six
	ShaderManager();
	ShaderManager(const ShaderManager&) = delete;
	ShaderManager& operator=(const ShaderManager&) = delete;
	ShaderManager(const ShaderManager&&) = delete;
	ShaderManager& operator=(ShaderManager&&) = delete;
	~ShaderManager();

	// Getting Shader Manager
	static ShaderManager& GetInstance();
	
	// Instantiating helper functions
	void loadDefaultShaders();

	// Setting Default Path
	void privSetDefaultPath(const std::string defaultPath);

	// Loading Shaders
	void privLoadShaderAndAssignKey(const std::string& fileName, const MapKey& key);

	// Loading Shaders helper functions
	bool hasKeyBeenAssigned(const MapKey& key) const;
	void printKeyAssignedErrorAndTerminate(const MapKey& key) const;

	bool isFilePathValid(const std::string& fileName) const;
	void printFileNameErrorAndTerminate(const std::string& fileName) const;

	void printShaderLoadedSuccessfully(const std::string& fileName) const;

	// Getting Shaders
	ShaderObject* privGetShader(const MapKey& key) const;
	ShaderObject* privGetDefaultShader(const DefaultShader) const;

	// Getting Shaders helper functions
	ShaderObject* tryToGetShader(const MapKey& key) const;
	const MapKey getDefaultShaderKey(const DefaultShader) const;

	// Deleting Shaders
	static void Delete();

	void deleteAllShaders();

public:
	/**********************************************************************************************//**
	 * <summary> Sets default file path to access shader files.</summary>
	 * \ingroup SHADERRESOURCES
	 * <remarks> </remarks>
	 *
	 * <param name="defaultPath"> The default file path.</param>
	 **************************************************************************************************/
	static void SetDefaultPath(const std::string& defaultPath)
	{
		GetInstance().privSetDefaultPath(defaultPath);
	}

	/**********************************************************************************************//**
	 * <summary> Loads shader and assign it to a user defined key.</summary>
	 * \ingroup SHADERRESOURCES
	 * <remarks> </remarks>
	 *
	 * <param name="fileName"> name of shader file.</param>
	 * <param name="key">	   user define key to associate with shader.</param>
	 **************************************************************************************************/
	static void LoadShaderAndAssignKey(const std::string& fileName, const MapKey& key)
	{
		ShaderManager::GetInstance().privLoadShaderAndAssignKey(fileName, key);
	}

	/**********************************************************************************************//**
	 * <summary> Gets default preloaded shader.</summary>
	 * \ingroup SHADERRESOURCES
	 * <remarks> </remarks>
	 *
	 * <param name="defaultShader"> The default shader.</param>
	 *
	 * <returns> A default shader.</returns>
	 **************************************************************************************************/
	static ShaderObject* GetDefaultShader(const DefaultShader defaultShader)
	{
		return ShaderManager::GetInstance().privGetDefaultShader(defaultShader);
	}

	/**********************************************************************************************//**
	 * <summary> Gets a shader with a user defined key.</summary>
	 * \ingroup SHADERRESOURCES
	 * <remarks> </remarks>
	 *
	 * <param name="key"> The user defined key associated to a shader.</param>
	 *
	 * <returns> A shader.</returns>
	 **************************************************************************************************/
	static ShaderObject* GetShader(const MapKey& key)
	{
		return ShaderManager::GetInstance().privGetShader(key);
	}

private:
	std::string _defaultPath;

	ShaderMap _shaderStorageMap;
	
	// For personal debugging
private:
	static void DebugPrint(const std::string& message);

	static const std::string DEBUG_TITLE_MESSAGE;
};

// For personal debugging
#ifndef ShaderManager_DEBUG
#define ShaderManager_DEBUG false
#endif ShaderManager_DEBUG

#endif _ShaderManager

//-----------------------------------------------------------------------------------------------------------------------------
// ShaderManager Comment Template
//-----------------------------------------------------------------------------------------------------------------------------