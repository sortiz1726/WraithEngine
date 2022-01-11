#ifndef _RegistrationState
#define _RegistrationState

/**********************************************************************************************//**
 * <summary> Values that represent registration states.</summary>
 *	\ingroup GAMEOBJECT_INTERNALS
 *	
 * <remarks> Internally used ONLY by GameObject, Updatable, Drawable, 
 * 			 Alarmable, Inputable, and Colliable. </remarks>
 **************************************************************************************************/
enum class RegistrationState
{
	CURRENTLY_DEREGISTERED,
	PENDING_REGISTRATION,
	CURRENTLY_REGISTERED,
	PENDING_DEREGISTRATION
};

#endif // !_RegistrationState