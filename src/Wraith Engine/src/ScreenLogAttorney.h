#ifndef _ScreenLogAttorney
#define _ScreenLogAttorney

#include "ScreenLog.h"

/**********************************************************************************************//**
 * <summary> A screen log attorney giving access to certain ScreenLog functions
 * 			 to certain classes.</summary>
 *
 * <remarks> NEVER called by the user. </remarks>
 **************************************************************************************************/
class ScreenLogAttorney
{
private:
	ScreenLogAttorney() = delete;
	ScreenLogAttorney(const ScreenLogAttorney&) = delete;
	ScreenLogAttorney& operator=(const ScreenLogAttorney&) = delete;
	ScreenLogAttorney(ScreenLogAttorney&&) = delete;
	ScreenLogAttorney& operator=(ScreenLogAttorney&&) = delete;
	~ScreenLogAttorney() = delete;

public:
	class RenderAccess
	{
		friend class Wraith;

		static void Render() { ScreenLog::Render(); }
	};

	class DeleteAccess
	{
		friend class Wraith;

		static void Delete() { ScreenLog::Delete(); }
	};
};
#endif // !_ScreenLogAttorney

//-----------------------------------------------------------------------------------------------------------------------------
// ScreenLogAttorney Comment Template
//-----------------------------------------------------------------------------------------------------------------------------