#ifndef _TextureManager
#define _TextureManager

#include <string>
#include <map>

class Texture;

/**********************************************************************************************//**
 * <summary> Manager for textures.
 * 			 For loading textures and accessing them within user defined games object
 * 			 </summary>
 *
 * <remarks> </remarks>
 **************************************************************************************************/

class TextureManager
{
	friend class TextureManagerAttorney;
public:
	typedef std::string MapKey;
private:
	typedef std::map<MapKey, Texture*> TextureMap;
	typedef unsigned char colorValue;

private:
	static TextureManager* pTextureManagerInstance;

	// Big Six
	TextureManager();
	TextureManager(const TextureManager&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;
	TextureManager(const TextureManager&&) = delete;
	TextureManager& operator=(TextureManager&&) = delete;
	~TextureManager();

	// Getting Texture Manager
	static TextureManager& GetInstance();

	// Setting Default Path
	void privSetDefaultPath(const std::string& defaultPath);

	// Loading Textures
	void privLoadTextureAndAssignKey(colorValue red, colorValue green, colorValue blue, const MapKey& key);
	void privLoadTextureAndAssignKey(const std::string& fileName, const MapKey& key);
	void privLoadTextureAndAssignKey(Texture*, const MapKey&);

	// Loading Textures helper functions
	bool hasKeyBeenAssigned(const MapKey& key) const;
	void printKeyAssignedErrorAndTerminate(const MapKey& key) const;

	bool isFilePathValid(const std::string& filePath) const;
	void printFileNameErrorAndTerminate(const std::string& fileName) const;

	void printTextureLoadedSuccessfully(const colorValue red, const colorValue green, const colorValue blue) const;
	void printTextureLoadedSuccessfully(const std::string& fileName) const;

	// Getting Textures
	Texture* privGetTexture(const MapKey& key) const;

	// Getting Textures helper function
	Texture* tryToGetTexture(const MapKey& key) const;

	// Deleting Textures
	static void Delete();

	void deleteAllTextures();

public:
	/**********************************************************************************************//**
	 * <summary> Sets default file path to access texture files.</summary>
	 * \ingroup TEXTURERESOURCES
	 * <remarks> </remarks>
	 *
	 * <param name="defaultPath"> The default file path.</param>
	 **************************************************************************************************/
	static void SetDefaultPath(const std::string& defaultPath)
	{
		GetInstance().privSetDefaultPath(defaultPath);
	}

	/**********************************************************************************************//**
	 * <summary> Loads texture and assigns it to a user defined key.</summary>
	 * \ingroup TEXTURERESOURCES
	 * <remarks> </remarks>
	 *
	 * <param name="fileName"> name of texture file.</param>
	 * <param name="key">	   user define key to associate with texture.</param>
	 **************************************************************************************************/
	static void LoadTextureAndAssignKey(const std::string& fileName, const MapKey& key)
	{
		TextureManager::GetInstance().privLoadTextureAndAssignKey(fileName, key);
	}

	/**********************************************************************************************//**
	 * <summary> Loads texture and assigns it to a user defined key.</summary>
	 * \ingroup TEXTURERESOURCES
	 * <remarks> Color values must be bewteen 0 - 254 </remarks>
	 *
	 * <param name="red">   The red value.</param>
	 * <param name="green"> The green value.</param>
	 * <param name="blue">  The blue value.</param>
	 * <param name="key">   user define key to associate with texture.</param>
	 **************************************************************************************************/
	static void LoadTextureAndAssignKey(const colorValue red, const colorValue green, const colorValue blue, const MapKey& key)
	{
		TextureManager::GetInstance().privLoadTextureAndAssignKey(red, green, blue, key);
	}

	static void LoadTextureAndAssignKey(Texture* pTexture, const MapKey& key)
	{
		TextureManager::GetInstance().privLoadTextureAndAssignKey(pTexture, key);
	}

	/**********************************************************************************************//**
	 * <summary> Gets a texture with a user defined key.</summary>
	 * \ingroup TEXTURERESOURCES
	 * <remarks> </remarks>
	 *
	 * <param name="key"> The user defined key associated to a texture.</param>
	 *
	 * <returns> A texture.</returns>
	 **************************************************************************************************/
	static Texture* GetTexture(const MapKey& key)
	{
		return TextureManager::GetInstance().privGetTexture(key);
	}

private:
	std::string _defaultPath;

	TextureMap _textureStorageMap;

	// For personal debugging
private:
	static void DebugPrint(const std::string& message);

	static const std::string DEBUG_TITLE_MESSAGE;
};

// For personal debugging
#ifndef TextureManager_DEBUG
#define TextureManager_DEBUG false
#endif TextureManager_DEBUG

#endif _TextureManager

//-----------------------------------------------------------------------------------------------------------------------------
// TextureManager Comment Template
//-----------------------------------------------------------------------------------------------------------------------------