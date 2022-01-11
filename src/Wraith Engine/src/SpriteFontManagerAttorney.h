#ifndef _SpriteFontManagerAttorney
#define _SpriteFontManagerAttorney

#include "SpriteFontManager.h"

class SpriteFontManagerAttorney
{
private:
	SpriteFontManagerAttorney() = delete;
	SpriteFontManagerAttorney(const SpriteFontManagerAttorney&) = delete;
	SpriteFontManagerAttorney& operator=(const SpriteFontManagerAttorney&) = delete;
	SpriteFontManagerAttorney(SpriteFontManagerAttorney&&) = delete;
	SpriteFontManagerAttorney& operator=(SpriteFontManagerAttorney&&) = delete;
	~SpriteFontManagerAttorney() = delete;

public:
	class DeleteAccess
	{
		friend class Wraith;

		static void Delete() { SpriteFontManager::Delete(); }
	};
};
#endif // !_SpriteFontManagerAttorney

//-----------------------------------------------------------------------------------------------------------------------------
// SpriteFontManagerAttorney Comment Template
//-----------------------------------------------------------------------------------------------------------------------------