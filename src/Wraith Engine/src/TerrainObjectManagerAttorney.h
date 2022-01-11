#ifndef _TerrainObjectManagerAttorney
#define _TerrainObjectManagerAttorney

#include "TerrainObjectManager.h"

class TerrainObjectManagerAttorney
{
public:
	TerrainObjectManagerAttorney() = default;
	TerrainObjectManagerAttorney(const TerrainObjectManagerAttorney&) = default;
	TerrainObjectManagerAttorney& operator=(const TerrainObjectManagerAttorney&) = default;
	TerrainObjectManagerAttorney(TerrainObjectManagerAttorney&&) = default;
	TerrainObjectManagerAttorney& operator=(TerrainObjectManagerAttorney&&) = default;
	~TerrainObjectManagerAttorney() = default;

public:
	class DeleteAccess
	{
		friend class Wraith;

		static void Delete() { TerrainObjectManager::Delete();}
	};

};
#endif // !_TerrainObjectManagerAttorney

//-----------------------------------------------------------------------------------------------------------------------------
// TerrainObjectManagerAttorney Comment Template
//-----------------------------------------------------------------------------------------------------------------------------