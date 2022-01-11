#ifndef _OctreeModelManagerAttorney
#define _OctreeModelManagerAttorney

#include "OctreeModelManager.h"

class OctreeModelManagerAttorney
{
public:
	OctreeModelManagerAttorney() = default;
	OctreeModelManagerAttorney(const OctreeModelManagerAttorney&) = default;
	OctreeModelManagerAttorney& operator=(const OctreeModelManagerAttorney&) = default;
	OctreeModelManagerAttorney(OctreeModelManagerAttorney&&) = default;
	OctreeModelManagerAttorney& operator=(OctreeModelManagerAttorney&&) = default;
	~OctreeModelManagerAttorney() = default;

public:
	class GetAccess
	{
		friend class CollisionVolumeOctree;

		static OctreeNode* GetOctreeModel(Model* pModel, int maxDepth)
		{
			return OctreeModelManager::GetOctreeModel(pModel, maxDepth);
		}
	};


	class DeleteAccess
	{
		friend class Wraith;

		static void Delete() { OctreeModelManager::Delete();}
	};

};
#endif // !_OctreeModelManagerAttorney

//-----------------------------------------------------------------------------------------------------------------------------
// OctreeModelManagerAttorney Comment Template
//-----------------------------------------------------------------------------------------------------------------------------