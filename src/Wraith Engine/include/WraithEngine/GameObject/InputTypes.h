#ifndef _InputEvent
#define _InputEvent

/**********************************************************************************************//**
 * <summary> Values that represent event types.</summary>
 *	\ingroup INPUTS
 * <remarks> To be used in GameObject::submitKeyRegistration(), GameObject::submitKeyDeregistration(), 
 * 			 GameObject::registerKey(), and GameObject::deregisterKey(). </remarks>
 **************************************************************************************************/

enum class InputEvent
{
	KEY_PRESS, 
	KEY_RELEASE
};

#endif // !_InputEvent