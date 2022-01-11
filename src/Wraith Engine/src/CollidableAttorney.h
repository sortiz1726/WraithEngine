#ifndef _CollidableAttorney
#define _CollidableAttorney

#include "Collidable.h"

/**********************************************************************************************//**
 * <summary> A collidable attorney used to grant access to private functions
 * 			 of collidable to some other classes.</summary>
 *
 * <remarks> NEVER called by the user.  </remarks>
 **************************************************************************************************/
class CollidableAttorney
{
private:
	CollidableAttorney() = delete;
	CollidableAttorney(const CollidableAttorney&) = delete;
	CollidableAttorney& operator=(const CollidableAttorney&) = delete;
	CollidableAttorney(CollidableAttorney&&) = delete;
	CollidableAttorney& operator=(CollidableAttorney&&) = delete;
	~CollidableAttorney() = delete;

public:	
	/**********************************************************************************************//**
	* <summary> Provides registration access to Collidables.</summary>
	*
	* <remarks> </remarks>
	**************************************************************************************************/
	class RegistrationAccess
	{
		friend class CollisionRegisterCommand;
		friend class CollisionDeregisterCommand;

		static void RegisterToScene(Collidable* pCollidable) { pCollidable->registerToScene(); }
		static void DeregisterFromScene(Collidable* pCollidable) { pCollidable->deregisterFromScene(); }
	};
};

#endif // !_CollidableAttorney

//-----------------------------------------------------------------------------------------------------------------------------
// CollidableAttorney Comment Template
//-----------------------------------------------------------------------------------------------------------------------------