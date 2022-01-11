#ifndef _SpriteFontManager
#define _SpriteFontManager

#include <string>
#include <map>

class SpriteFont;

/**********************************************************************************************//**
 * <summary> Manager for sprite fonts.</summary>
 *
 * <remarks> All font files must be in the Fonts folder containing both the tga and xml file
 * 			 with the same name (ex: Font1.tga and Font1.xml)</remarks>
 **************************************************************************************************/
class SpriteFontManager
{
	friend class SpriteFontManagerAttorney;
	typedef std::string MapKey;
	typedef std::map<MapKey, SpriteFont*> StorageMap;
private:
	static SpriteFontManager* pSpriteFontManagerInstance;

	SpriteFontManager();
	SpriteFontManager(const SpriteFontManager&) = delete;
	SpriteFontManager& operator=(const SpriteFontManager&) = delete;
	SpriteFontManager(SpriteFontManager&&) = delete;
	SpriteFontManager& operator=(SpriteFontManager&&) = delete;
	~SpriteFontManager();

	static SpriteFontManager& GetInstance();

	void privSetDefaultPath(const std::string defaultPath);

	// Load SpriteFont
	void privLoadSpriteFontAndAssignKey(const std::string& fileName, const MapKey&);

	// ---> Load SpriteFont helpers
	bool isFilePathValid(const std::string& filePath) const;
	void printFileNameErrorAndTerminate(const std::string& fileName) const;

	bool hasKeyBeenAssigned(const MapKey& key) const;
	void printKeyAssignedErrorAndTerminate(const MapKey& key) const;

	void printSpriteFontLoadedSuccessfully(const std::string& fileName) const;

	// Get SpriteFont
	SpriteFont* privGetSpriteFont(const MapKey&) const;

	// ---> Get SpriteFont helper
	SpriteFont* tryToGetSpriteFont(const MapKey&) const;

	static void Delete();

	// ---> Termination helper
	void deleteSpriteFonts();

public:
	/**********************************************************************************************//**
	* <summary> Sets default file path to access sprite font files.</summary>
	* \ingroup SPRITEFONTRESOURCES
	* <remarks> </remarks>
	*
	* <param name="defaultPath"> The default file path.</param>
	**************************************************************************************************/
	static void SetDefaultPath(const std::string& defaultPath)
	{
		GetInstance().privSetDefaultPath(defaultPath);
	}
	/**********************************************************************************************//**
	 * <summary> Loads a sprite font and assigns it to a user defined key.</summary>
	 * \ingroup SPRITEFONTRESOURCES
	 * <remarks> All font files must be in the Fonts folder containing both the tga and xml file
	 * 			 with the same name (ex: Font1.tga and Font1.xml)</remarks>
	 *
	 * <param name="fileName"> File name of the sprite font.</param>
	 * <param name="key">	   The key.</param>
	 **************************************************************************************************/
	static void LoadSpriteFontAndAssignKey(const std::string& fileName, const MapKey& key)
	{
		GetInstance().privLoadSpriteFontAndAssignKey(fileName, key);
	}

	/**********************************************************************************************//**
	 * <summary> Gets a sprite font using a user defined key.</summary>
	 * \ingroup SPRITEFONTRESOURCES
	 * <remarks> if the key does not exist, 
	 * 			 an exception is thrown with a messaage displaying the error</remarks>
	 *
	 * <param name="key"> The key.</param>
	 *
	 * <returns> a sprite font pointer.</returns>
	 **************************************************************************************************/
	static SpriteFont* GetSpriteFont(const MapKey& key)
	{
		return GetInstance().privGetSpriteFont(key);
	}

private:
	std::string _defaultPath;

	StorageMap _storageMap;

};
#endif // !_SpriteFontManager

//-----------------------------------------------------------------------------------------------------------------------------
// SpriteFontManager Comment Template
//-----------------------------------------------------------------------------------------------------------------------------