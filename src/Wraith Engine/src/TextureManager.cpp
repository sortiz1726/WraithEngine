#include "TextureManager.h"
#include <cassert>
#include <exception>
#include "File.h"
#include "Texture.h"

TextureManager* TextureManager::pTextureManagerInstance = nullptr;

//-----------------------------------------------------------------------------------------------------------------------------
// Getting Texture Manager
//-----------------------------------------------------------------------------------------------------------------------------
TextureManager& TextureManager::GetInstance()
{
	if (pTextureManagerInstance == nullptr)
	{
		pTextureManagerInstance = new TextureManager();
	}
	assert(pTextureManagerInstance);
	return *pTextureManagerInstance;
}

//-----------------------------------------------------------------------------------------------------------------------------
// Instaniating Texture Manager
//-----------------------------------------------------------------------------------------------------------------------------
TextureManager::TextureManager()
{
	TextureManager::DebugPrint("Default Constructor called");
	privSetDefaultPath("Textures/");
	TextureManager::DebugPrint("");
}

//-----------------------------------------------------------------------------------------------------------------------------
// Setting Default Path
//-----------------------------------------------------------------------------------------------------------------------------
void TextureManager::privSetDefaultPath(const std::string& defaultPath)
{
	TextureManager::DebugPrint("Setting Default Path to \"" + defaultPath + "\"");
	_defaultPath = defaultPath;
}

//-----------------------------------------------------------------------------------------------------------------------------
// Loading Textures
//-----------------------------------------------------------------------------------------------------------------------------
void TextureManager::privLoadTextureAndAssignKey(const colorValue red, const colorValue green, const colorValue blue, const MapKey& key)
{
	if (hasKeyBeenAssigned(key)) printKeyAssignedErrorAndTerminate(key);

	Texture* pTexture = new Texture(red, green, blue);
	_textureStorageMap.insert(std::make_pair(key, pTexture));

	printTextureLoadedSuccessfully(red, green, blue);
}

void TextureManager::privLoadTextureAndAssignKey(const std::string& fileName, const MapKey& key)
{
	if (hasKeyBeenAssigned(key)) printKeyAssignedErrorAndTerminate(key);

	const std::string filePath = TextureManager::_defaultPath + fileName;
	if (!isFilePathValid(filePath)) printFileNameErrorAndTerminate(fileName);

	Texture* pTexture = new Texture(filePath.c_str());
	_textureStorageMap.insert(std::make_pair(key, pTexture));

	printTextureLoadedSuccessfully(fileName);
}

void TextureManager::privLoadTextureAndAssignKey(Texture* pTexture, const MapKey& key)
{
	if (hasKeyBeenAssigned(key)) printKeyAssignedErrorAndTerminate(key);

	_textureStorageMap.insert(std::make_pair(key, pTexture));

	printTextureLoadedSuccessfully(pTexture->getName());
}

// Loading Textures helper functions
bool TextureManager::hasKeyBeenAssigned(const MapKey& key) const
{
	return _textureStorageMap.find(key) != _textureStorageMap.end();
}

void TextureManager::printKeyAssignedErrorAndTerminate(const MapKey& key) const
{
	Trace::out("KEY - %s - for TEXTURE has been used. Use another KEY name\n", key.c_str());
	throw std::exception();
	//std::terminate();
}

bool TextureManager::isFilePathValid(const std::string& filePath) const
{
	FileHandle fileHandle;
	FileError result = File::open(fileHandle, filePath.c_str(), FileMode::FILE_READ);
	File::close(fileHandle);
	return result == FileError::FILE_SUCCESS;
}

void TextureManager::printFileNameErrorAndTerminate(const std::string& fileName) const
{
	Trace::out("FILE NAME - %s - for TEXTURE cannot be found. Check FILE NAME or ensure that TEXTURE file is in the TEXTURES FOLDER\n", fileName.c_str());
	throw std::exception();
	//std::terminate();
}

void TextureManager::printTextureLoadedSuccessfully(const colorValue red, const colorValue green, const colorValue blue) const
{
	const std::string RGBValue = "RGB Color(" + std::to_string(red) + ", " + std::to_string(green) + ", " + std::to_string(blue) + ")";
	printTextureLoadedSuccessfully(RGBValue);
}

void TextureManager::printTextureLoadedSuccessfully(const std::string& fileName) const
{
	Trace::out("Texture Manager: %s loaded successfully\n", fileName.c_str());
}

//-----------------------------------------------------------------------------------------------------------------------------
// Getting Textures
//-----------------------------------------------------------------------------------------------------------------------------
Texture* TextureManager::privGetTexture(const MapKey& key) const
{
	return tryToGetTexture(key);
}

// Getting Textures helper function
Texture* TextureManager::tryToGetTexture(const MapKey& key) const
{
	try
	{
		return _textureStorageMap.at(key);
	}
	catch (std::out_of_range exception)
	{
		Trace::out("INVALID key - \"%s\" - for TEXTURE storage map\n", key.c_str());
		throw exception;
	}
}

//-----------------------------------------------------------------------------------------------------------------------------
// Deleting Textures
//-----------------------------------------------------------------------------------------------------------------------------
void TextureManager::Delete()
{
	Trace::out("Texture Manager: Deleting Texture Manager\n");
	delete pTextureManagerInstance;
	pTextureManagerInstance = nullptr;
}

TextureManager::~TextureManager()
{
	TextureManager::DebugPrint("Destructor is called");
	deleteAllTextures();
	TextureManager::DebugPrint("");
}

void TextureManager::deleteAllTextures()
{
	TextureManager::DebugPrint("Deleting all Textures");
	for (auto& pair : _textureStorageMap)
	{
		TextureManager::DebugPrint("Deleting \"" + pair.first + "\" texture");
		Texture* pTexture = pair.second;
		delete pTexture;
	}
	TextureManager::DebugPrint("All Textures have been deleted");
	_textureStorageMap.clear();
}

//-----------------------------------------------------------------------------------------------------------------------------
// For personal debugging
//-----------------------------------------------------------------------------------------------------------------------------
const std::string TextureManager::DEBUG_TITLE_MESSAGE = "TextureManager_DEBUG: ";

void TextureManager::DebugPrint(const std::string& message)
{
	(void(message));
#if TextureManager_DEBUG
	if (message.size() == 0)
	{
		Trace::out("\n");
}
	else
	{
		std::string finalMessage = TextureManager::DEBUG_TITLE_MESSAGE + message + std::string("\n");
		Trace::out("%s", finalMessage.c_str());
	}
#endif TextureManager_DEBUG
}