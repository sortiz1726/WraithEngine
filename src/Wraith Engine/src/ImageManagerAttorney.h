#ifndef _ImageManagerAttorney
#define _ImageManagerAttorney

#include "ImageManager.h"

class ImageManagerAttorney
{
private:
	ImageManagerAttorney() = delete;
	ImageManagerAttorney(const ImageManagerAttorney&) = delete;
	ImageManagerAttorney& operator=(const ImageManagerAttorney&) = delete;
	ImageManagerAttorney(ImageManagerAttorney&&) = delete;
	ImageManagerAttorney& operator=(ImageManagerAttorney&&) = delete;
	~ImageManagerAttorney() = delete;

public:
	class DeleteAccess
	{
		friend class Wraith;

		static void Delete() { ImageManager::Delete(); }
	};
};
#endif // !_ImageManagerAttorney

//-----------------------------------------------------------------------------------------------------------------------------
// ImageManagerAttorney Comment Template
//-----------------------------------------------------------------------------------------------------------------------------