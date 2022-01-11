#include "SpriteFontManager.h"
#include <cassert>
#include <exception>
#include "File.h"
#include "SpriteFont.h"

SpriteFontManager* SpriteFontManager::pSpriteFontManagerInstance = nullptr;

SpriteFontManager& SpriteFontManager::GetInstance()
{
	if (SpriteFontManager::pSpriteFontManagerInstance == nullptr)
	{
		SpriteFontManager::pSpriteFontManagerInstance = new SpriteFontManager();
	}
	assert(SpriteFontManager::pSpriteFontManagerInstance != nullptr);
	return *SpriteFontManager::pSpriteFontManagerInstance;
}


SpriteFontManager::SpriteFontManager()
{
	privSetDefaultPath("Fonts/");
}

void SpriteFontManager::privSetDefaultPath(const std::string defaultPath)
{
	_defaultPath = defaultPath;
}

//-----------------------------------------------------------------------------------------------------------------------------
// Load SpriteFont
//-----------------------------------------------------------------------------------------------------------------------------
void SpriteFontManager::privLoadSpriteFontAndAssignKey(const std::string& fileName, const MapKey& key)
{
	const std::string filePath = _defaultPath + fileName;
	if (!isFilePathValid(filePath)) printFileNameErrorAndTerminate(fileName);

	if (hasKeyBeenAssigned(key)) printKeyAssignedErrorAndTerminate(key);

	SpriteFont* pSpriteFont = new SpriteFont(filePath);

	_storageMap.insert(std::make_pair(key, pSpriteFont));
	
	printSpriteFontLoadedSuccessfully(pSpriteFont->getName());
}

// ---> Load SpriteFont helpers
bool SpriteFontManager::isFilePathValid(const std::string& filePath) const
{
	const std::string filePathWithShaderExtension = filePath + +".tga";

	FileHandle fileHandle;
	FileError result = File::open(fileHandle, filePathWithShaderExtension.c_str(), FileMode::FILE_READ);
	File::close(fileHandle);
	return result == FileError::FILE_SUCCESS;
}

void SpriteFontManager::printFileNameErrorAndTerminate(const std::string& fileName) const
{
	Trace::out("FILE NAME - %s - for SpriteFont cannot be found. Check FILE NAME or ensure that SpriteFont file is in the SpriteFontS FOLDER\n", fileName.c_str());
	throw std::exception();
}

bool SpriteFontManager::hasKeyBeenAssigned(const MapKey& key) const
{
	return _storageMap.find(key) != _storageMap.end();
}

void SpriteFontManager::printKeyAssignedErrorAndTerminate(const MapKey& key) const
{
	Trace::out("KEY - %s - for SpriteFont has been used. Use another KEY name\n", key.c_str());
	throw std::exception();
}

void SpriteFontManager::printSpriteFontLoadedSuccessfully(const std::string& spriteFontName) const
{
	Trace::out("SpriteFont Manager: %s loaded successfully\n", spriteFontName.c_str());
}

//-----------------------------------------------------------------------------------------------------------------------------
// Get SpriteFont
//-----------------------------------------------------------------------------------------------------------------------------
SpriteFont* SpriteFontManager::privGetSpriteFont(const MapKey& key) const
{
	return tryToGetSpriteFont(key);
}

// --> Get SpriteFont helper
SpriteFont* SpriteFontManager::tryToGetSpriteFont(const MapKey& key) const
{
	try
	{
		return _storageMap.at(key);
	}
	catch (std::out_of_range exception)
	{
		Trace::out("INVALID key - \"%s\" - for SpriteFont storage map\n", key.c_str());
		throw exception;
	}
}


//-----------------------------------------------------------------------------------------------------------------------------
// Termination
//-----------------------------------------------------------------------------------------------------------------------------
void SpriteFontManager::Delete()
{
	delete SpriteFontManager::pSpriteFontManagerInstance;
	SpriteFontManager::pSpriteFontManagerInstance = nullptr;
}

SpriteFontManager::~SpriteFontManager()
{
	deleteSpriteFonts();
}

void SpriteFontManager::deleteSpriteFonts()
{
	for (auto& pair : _storageMap)
	{
		SpriteFont* pSpriteFont = pair.second;
		delete pSpriteFont;
	}
}
