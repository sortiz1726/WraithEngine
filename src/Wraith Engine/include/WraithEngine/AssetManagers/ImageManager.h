#ifndef _ImageManager
#define _ImageManager

#include <map>
#include <string>

class Image;
class Texture;
struct Rect;

/**********************************************************************************************//**
 * <summary> Manager for images.
 * 			 For loading images and accessing them within user defined games object
 * 			 </summary>
 *
 * <remarks> </remarks>
 **************************************************************************************************/

class ImageManager
{
	friend class ImageManagerAttorney;
	typedef std::string MapKey;
	typedef std::map<MapKey, Image*> StorageMap;
	typedef unsigned char colorValue;
private:
	static ImageManager* pImageManagerInstance;

	ImageManager();
	ImageManager(const ImageManager&) = delete;
	ImageManager& operator=(const ImageManager&) = delete;
	ImageManager(ImageManager&&) = delete;
	ImageManager& operator=(ImageManager&&) = delete;
	~ImageManager();

	static ImageManager& GetInstance();

	// Set Default Path
	void privSetDefaultPath(const std::string& defaultPath);

	// Load Image
	void privLoadImageAndAssignKey(const std::string& fileName, const MapKey&);
	void privLoadImageAndAssignKey(colorValue red, colorValue green, colorValue blue, const MapKey& key);
	void privLoadImageAndAssignKey(Texture*, const MapKey&);
	void privLoadImageAndAssignKey(const std::string& fileName, Rect* , const MapKey&);
	void privLoadImageAndAssignKey(Texture*, Rect*, const MapKey&);

	// ---> Load Image helpers
	bool isFilePathValid(const std::string& filePath) const;
	void printFileNameErrorAndTerminate(const std::string& fileName) const;

	bool hasKeyBeenAssigned(const MapKey& key) const;
	void printKeyAssignedErrorAndTerminate(const MapKey& key) const;

	void printImageLoadedSuccessfully(const std::string& fileName) const;
	void printImageLoadedSuccessfully(colorValue red, colorValue green, colorValue blue) const;

	// Get Image
	Image* privGetImage(const MapKey&) const;

	// ---> Get Image helper
	Image* tryToGetImage(const MapKey&) const;

	static void Delete();

	// ---> Termination helper
	void deleteImages();

public:
	/**********************************************************************************************//**
	 * <summary> Sets default file path to access image files.</summary>
	 * \ingroup IMAGERESOURCES
	 * <remarks> </remarks>
	 *
	 * <param name="defaultPath"> The default file path.</param>
	 **************************************************************************************************/
	static void SetDefaultPath(const std::string& defaultPath)
	{
		GetInstance().privSetDefaultPath(defaultPath);
	}

	/**********************************************************************************************//**
	 * <summary> Loads image and assign it to a user defined key.</summary>
	 * \ingroup IMAGERESOURCES
	 * <remarks> </remarks>
	 *
	 * <param name="fileName"> File name of the image file.</param>
	 * <param name="key">	   The user defined key.</param>
	 **************************************************************************************************/
	static void LoadImageAndAssignKey(const std::string& fileName, const MapKey& key)
	{
		GetInstance().privLoadImageAndAssignKey(fileName, key);
	}

	/**********************************************************************************************//**
	 * <summary> Loads image using color values and assign it to a user defined key.</summary>
	 * \ingroup IMAGERESOURCES
	 * <remarks> Color values must be between 0 - 254 </remarks>
	 *
	 * <param name="red">   The red value.</param>
	 * <param name="green"> The green value.</param>
	 * <param name="blue">  The blue value.</param>
	 * <param name="key">   The user defined key.</param>
	 **************************************************************************************************/
	static void LoadImageAndAssignKey(colorValue red, colorValue green, colorValue blue, const MapKey& key)
	{
		GetInstance().privLoadImageAndAssignKey(red, green, blue, key);
	}

	/**********************************************************************************************//**
	 * <summary> Loads image and assign it to a user defined key.</summary>
	 * \ingroup IMAGERESOURCES
	 * <remarks> </remarks>
	 *
	 * <param name="pTexture"> pointer to a texture.</param>
	 * <param name="key">	   The key.</param>
	 **************************************************************************************************/
	static void LoadImageAndAssignKey(Texture* pTexture, const MapKey& key)
	{
		GetInstance().privLoadImageAndAssignKey(pTexture, key);
	}

	/**********************************************************************************************//**
	 * <summary> Loads image and assign it to user defined key.</summary>
	 * \ingroup IMAGERESOURCES
	 * <remarks> </remarks>
	 *
	 * <param name="fileName">   Filename of the image file.</param>
	 * <param name="pRectangle"> the rectangle indicate the subsection of the image to be used.</param>
	 * <param name="key">		 The user defined key.</param>
	 **************************************************************************************************/
	static void LoadImageAndAssignKey(const std::string& fileName, Rect* pRectangle, const MapKey& key)
	{
		GetInstance().privLoadImageAndAssignKey(fileName, pRectangle, key);
	}

	/**********************************************************************************************//**
	 * <summary> Loads image and assigns it to a user defined key.</summary>
	 * \ingroup IMAGERESOURCES
	 * <remarks> </remarks>
	 *
	 * <param name="pTexture">   the pointer to a texture.</param>
	 * <param name="pRectangle"> the rectangle indicate the subsection of the image to be used.</param>
	 * <param name="key">		 The user defined key.</param>
	 **************************************************************************************************/
	static void LoadImageAndAssignKey(Texture* pTexture, Rect* pRectangle, const MapKey& key)
	{
		GetInstance().privLoadImageAndAssignKey(pTexture, pRectangle, key);
	}

	/**********************************************************************************************//**
	 * <summary> Gets an image with user defined key.</summary>
	 * \ingroup IMAGERESOURCES
	 * <remarks> </remarks>
	 *
	 * <param name="key"> The user defined key associated with the image.</param>
	 *
	 * <returns> A image.</returns>
	 **************************************************************************************************/
	static Image* GetImage(const MapKey& key)
	{
		return GetInstance().privGetImage(key);
	}

private:
	std::string _defaultPath;

	StorageMap _imageStorageMap;
};

#endif // !_ImageManager

//-----------------------------------------------------------------------------------------------------------------------------
// ImageManager Comment Template
//-----------------------------------------------------------------------------------------------------------------------------