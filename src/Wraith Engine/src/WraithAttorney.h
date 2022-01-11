#ifndef _WraithAttorney
#define _WraithAttorney

#include "Wraith.h"

class WraithAttorney
{
public:
	WraithAttorney() = delete;
	WraithAttorney(const WraithAttorney&) = delete;
	WraithAttorney& operator=(const WraithAttorney&) = delete;
	WraithAttorney(WraithAttorney&&) = delete;
	WraithAttorney& operator=(WraithAttorney&&) = delete;
	~WraithAttorney() = delete;
public:
	class TimeAccess
	{
		friend class FreezeTime;

		static float GetTimeInSeconds() { return Wraith::GetTimeInSeconds(); }
	};
};
#endif // !_WraithAttorney

//-----------------------------------------------------------------------------------------------------------------------------
// WraithAttorney Comment Template
//-----------------------------------------------------------------------------------------------------------------------------