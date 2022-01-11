#include "ImageManager.h"
#include <cassert>
#include <exception>
#include "File.h"
#include "Image.h"
#include "Rect.h"
#include "TextureManager.h"

ImageManager* ImageManager::pImageManagerInstance = nullptr;

ImageManager& ImageManager::GetInstance()
{
	if (ImageManager::pImageManagerInstance == nullptr)
	{
		ImageManager::pImageManagerInstance = new ImageManager();
	}
	assert(ImageManager::pImageManagerInstance != nullptr);
	return *ImageManager::pImageManagerInstance;
}

ImageManager::ImageManager()
{
	privSetDefaultPath("Images/");
}

//-----------------------------------------------------------------------------------------------------------------------------
// Set Default Path
//-----------------------------------------------------------------------------------------------------------------------------
void ImageManager::privSetDefaultPath(const std::string& defaultPath)
{
	_defaultPath = defaultPath;
}


//-----------------------------------------------------------------------------------------------------------------------------
// Load Image
//-----------------------------------------------------------------------------------------------------------------------------
void ImageManager::privLoadImageAndAssignKey(const std::string& fileName, const MapKey& key)
{
	const std::string filePath = _defaultPath + fileName;
	if (!isFilePathValid(filePath)) printFileNameErrorAndTerminate(fileName);

	Texture* pTexture = new Texture(filePath.c_str());

	try
	{
		privLoadImageAndAssignKey(pTexture, key);
	}
	catch (const std::exception& exception)
	{
		delete pTexture;
		throw exception;
	}
}

void ImageManager::privLoadImageAndAssignKey(colorValue red, colorValue green, colorValue blue, const MapKey& key)
{
	Texture* pTexture = new Texture(red, green, blue);

	try
	{
		privLoadImageAndAssignKey(pTexture, key);
	}
	catch (const std::exception& exception)
	{
		delete pTexture;
		throw exception;
	}

	printImageLoadedSuccessfully(red, green, blue);
}

void ImageManager::privLoadImageAndAssignKey(Texture* pTexture, const MapKey& key)
{
	float textureWidth = static_cast<float>(pTexture->getWidth());
	float textureHeight = static_cast<float>(pTexture->getHeight());
	Rect* pRectangle = new Rect(0.0f, 0.0f, textureWidth, textureHeight);

	try
	{
		privLoadImageAndAssignKey(pTexture, pRectangle, key);
	}
	catch (const std::exception& exception)
	{
		delete pRectangle;
		throw exception;
	}
}

void ImageManager::privLoadImageAndAssignKey(const std::string& fileName, Rect* pRectangle, const MapKey& key)
{
	const std::string filePath = _defaultPath + fileName;
	if (!isFilePathValid(filePath)) printFileNameErrorAndTerminate(fileName);

	Texture* pTexture = new Texture(filePath.c_str());

	try
	{
		privLoadImageAndAssignKey(pTexture, pRectangle, key);
	}
	catch (const std::exception& exception)
	{
		delete pTexture;
		throw exception;
	}
}

void ImageManager::privLoadImageAndAssignKey(Texture* pTexture, Rect* pRectanlge, const MapKey& key)
{
	if (hasKeyBeenAssigned(key)) printKeyAssignedErrorAndTerminate(key);

	TextureManager::LoadTextureAndAssignKey(pTexture, key);
	Image* pImage = new Image(pTexture, pRectanlge);
	_imageStorageMap.insert(std::make_pair(key, pImage));

	printImageLoadedSuccessfully(pTexture->getName());
}

// ---> Load Image helpers
bool ImageManager::isFilePathValid(const std::string& filePath) const
{
	FileHandle fileHandle;
	FileError result = File::open(fileHandle, filePath.c_str(), FileMode::FILE_READ);
	File::close(fileHandle);
	return result == FileError::FILE_SUCCESS;
}

void ImageManager::printFileNameErrorAndTerminate(const std::string& fileName) const
{
	Trace::out("FILE NAME - %s - for IMAGE cannot be found. Check FILE NAME or ensure that IMAGE file is in the IMAGES FOLDER\n", fileName.c_str());
	throw std::exception();
}

bool ImageManager::hasKeyBeenAssigned(const MapKey& key) const
{
	return _imageStorageMap.find(key) != _imageStorageMap.end();
}

void ImageManager::printKeyAssignedErrorAndTerminate(const MapKey& key) const
{
	Trace::out("KEY - %s - for IMAGE has been used. Use another KEY name\n", key.c_str());
	throw std::exception();
}

void ImageManager::printImageLoadedSuccessfully(colorValue red, colorValue green, colorValue blue) const
{
	const std::string RGBValue = "RGB Color(" + std::to_string(red) + ", " + std::to_string(green) + ", " + std::to_string(blue) + ")";
	printImageLoadedSuccessfully(RGBValue);
}

void ImageManager::printImageLoadedSuccessfully(const std::string& textureName) const
{
	Trace::out("Image Manager: %s loaded successfully\n", textureName.c_str());
}

//-----------------------------------------------------------------------------------------------------------------------------
// Get Image
//-----------------------------------------------------------------------------------------------------------------------------
Image* ImageManager::privGetImage(const MapKey& key) const
{
	return tryToGetImage(key);
}

// --> Get Image helper
Image* ImageManager::tryToGetImage(const MapKey& key) const
{
	try
	{
		return _imageStorageMap.at(key);
	}
	catch (std::out_of_range exception)
	{
		Trace::out("INVALID key - \"%s\" - for IMAGE storage map\n", key.c_str());
		throw exception;
	}
}


//-----------------------------------------------------------------------------------------------------------------------------
// Termination
//-----------------------------------------------------------------------------------------------------------------------------
void ImageManager::Delete()
{
	delete ImageManager::pImageManagerInstance;
	ImageManager::pImageManagerInstance = nullptr;
}

ImageManager::~ImageManager()
{
	deleteImages();
}

void ImageManager::deleteImages()
{
	for (auto& pair : _imageStorageMap)
	{
		Image* pImage = pair.second;
		delete pImage;
	}
}
