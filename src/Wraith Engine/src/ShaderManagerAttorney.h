#ifndef _ShaderManagerAttorney
#define _ShaderManagerAttorney

#include "ShaderManager.h"

class ShaderManagerAttorney
{
public:
	ShaderManagerAttorney() = default;
	ShaderManagerAttorney(const ShaderManagerAttorney&) = default;
	ShaderManagerAttorney& operator=(const ShaderManagerAttorney&) = default;
	ShaderManagerAttorney(ShaderManagerAttorney&&) = default;
	ShaderManagerAttorney& operator=(ShaderManagerAttorney&&) = default;
	~ShaderManagerAttorney() = default;

public:
	class DeleteAccess
	{
		friend class Wraith;

		static void Delete() { ShaderManager::Delete(); }
	};

};
#endif // !_ShaderManagerAttorney

//-----------------------------------------------------------------------------------------------------------------------------
// ShaderManagerAttorney Comment Template
//-----------------------------------------------------------------------------------------------------------------------------