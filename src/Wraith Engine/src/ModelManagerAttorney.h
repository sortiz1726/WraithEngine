#ifndef _ModelManagerAttorney
#define _ModelManagerAttorney

#include "ModelManager.h"

class ModelManagerAttorney
{
public:
	ModelManagerAttorney() = default;
	ModelManagerAttorney(const ModelManagerAttorney&) = default;
	ModelManagerAttorney& operator=(const ModelManagerAttorney&) = default;
	ModelManagerAttorney(ModelManagerAttorney&&) = default;
	ModelManagerAttorney& operator=(ModelManagerAttorney&&) = default;
	~ModelManagerAttorney() = default;

public:
	class DeleteAccess
	{
		friend class Wraith;

		static void Delete() { ModelManager::Delete();}
	};

};
#endif // !_ModelManagerAttorney

//-----------------------------------------------------------------------------------------------------------------------------
// ModelManagerAttorney Comment Template
//-----------------------------------------------------------------------------------------------------------------------------