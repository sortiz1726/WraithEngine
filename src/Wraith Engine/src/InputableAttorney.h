#ifndef _InputableAttorney
#define _InputableAttorney

#include "Inputable.h"

class InputableAttorney
{
public:
	InputableAttorney() = default;
	InputableAttorney(const InputableAttorney&) = default;
	InputableAttorney& operator=(const InputableAttorney&) = default;
	InputableAttorney(InputableAttorney&&) = default;
	InputableAttorney& operator=(InputableAttorney&&) = default;
	~InputableAttorney() = default;

public:
	class InputAccess
	{
		friend class SingleKeyEventManager;

		static void KeyPressed(Inputable* pInputable, AZUL_KEY key) { pInputable->keyPressed(key); }
		static void KeyReleased(Inputable* pInputable, AZUL_KEY key) { pInputable->keyReleased(key); }
	};

	class RegistrationAccess
	{
		friend class KeyRegistrationCommand;
		friend class KeyDeregistrationCommand;

		static void RegisterKey(Inputable* pInputable, AZUL_KEY key, InputEvent eventType) { pInputable->registerKey(key, eventType); }
		static void DeregisterKey(Inputable* pInputable, AZUL_KEY key, InputEvent eventType) { pInputable->deregisterKey(key, eventType); }
	};

	class FieldAccess
	{
		friend class KeyboardEventManager;
		friend class SingleKeyEventManager;

		static void SetKeyboardDeleteRerefence(Inputable* pInputable, const KeyboardEventManager::StorageMapReference& keyboardReference, AZUL_KEY key, InputEvent eventType)
		{
			pInputable->setKeyboardDeleteReference(keyboardReference, key, eventType);
		}
		static KeyboardEventManager::StorageMapReference GetKeyboardDeleteRerefence(Inputable* pInputable, AZUL_KEY key, InputEvent eventType)
		{
			return pInputable->getKeyboardDeleteReference(key, eventType);
		}

		static void SetSingleKeyDeleteRerefence(Inputable* pInputable, const SingleKeyEventManager::StorageListReference& singleKeyReference, AZUL_KEY key, InputEvent eventType)
		{
			pInputable->setSingleKeyDeleteReference(singleKeyReference, key, eventType);
		}
		static SingleKeyEventManager::StorageListReference GetSingleKeyDeleteRerefence(Inputable* pInputable, AZUL_KEY key, InputEvent eventType)
		{
			return pInputable->getSingleKeyDeleteReference(key, eventType);
		}
	};

};
#endif // !_InputableAttorney

//-----------------------------------------------------------------------------------------------------------------------------
// InputableAttorney Comment Template
//-----------------------------------------------------------------------------------------------------------------------------