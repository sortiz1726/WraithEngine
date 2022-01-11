#ifndef _TextureManagerAttorney
#define _TextureManagerAttorney

#include "TextureManager.h"

class TextureManagerAttorney
{
private:
	TextureManagerAttorney() = delete;
	TextureManagerAttorney(const TextureManagerAttorney&) = delete;
	TextureManagerAttorney& operator=(const TextureManagerAttorney&) = delete;
	TextureManagerAttorney(TextureManagerAttorney&&) = delete;
	TextureManagerAttorney& operator=(TextureManagerAttorney&&) = delete;
	~TextureManagerAttorney() = delete;

public:
	class DeleteAccess
	{
		friend class Wraith;

		static void Delete() { TextureManager::Delete(); }
	};

};
#endif // !_TextureManagerAttorney

//-----------------------------------------------------------------------------------------------------------------------------
// TextureManagerAttorney Comment Template
//-----------------------------------------------------------------------------------------------------------------------------