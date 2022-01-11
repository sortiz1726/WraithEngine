#ifndef _TimeManagerAttorney
#define _TimeManagerAttorney

#include "TimeManager.h"

/**********************************************************************************************//**
 * <summary> A time manager attorney for letting specific classes access
 * 			 specific private funcions within TimeManager class.</summary>
 *
 * <remarks> NEVER to be called by the user. </remarks>
 **************************************************************************************************/
class TimeManagerAttorney
{
public:
	TimeManagerAttorney() = delete;
	TimeManagerAttorney(const TimeManagerAttorney&) = delete;
	TimeManagerAttorney& operator=(const TimeManagerAttorney&) = delete;
	TimeManagerAttorney(TimeManagerAttorney&&) = delete;
	TimeManagerAttorney& operator=(TimeManagerAttorney&&) = delete;
	~TimeManagerAttorney() = delete;
public:
	class TimeAccess
	{
		friend class Wraith;

		static void SetCurrentTimeStamp(float currentTimeStamp) { TimeManager::SetCurrentTimeStamp(currentTimeStamp); };
	};

	class DeleteAccess
	{
		friend class Wraith;

		static void Delete() { TimeManager::Delete(); }
	};
};
#endif // !_TimeManagerAttorney

//-----------------------------------------------------------------------------------------------------------------------------
// TimeManagerAttorney Comment Template
//-----------------------------------------------------------------------------------------------------------------------------