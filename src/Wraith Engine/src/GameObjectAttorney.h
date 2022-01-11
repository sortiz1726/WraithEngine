#ifndef _GameObjectAttorney
#define _GameObjectAttorney

#include "GameObject.h"

/**********************************************************************************************//**
 * <summary> A Game Object Attorney giving access to certain GameObject functions
 * 			 to certain classes.</summary>
 *  \ingroup GAMEOBJECT_INTERNALS
 *  
 * <remarks> NEVER called by the user. </remarks>
 **************************************************************************************************/
class GameObjectAttorney
{
private:
	GameObjectAttorney() = delete;
	GameObjectAttorney(const GameObjectAttorney&) = delete;
	GameObjectAttorney& operator=(const GameObjectAttorney&) = delete;
	GameObjectAttorney(GameObjectAttorney&&) = delete;
	GameObjectAttorney& operator=(GameObjectAttorney&&) = delete;
	~GameObjectAttorney() = delete;

public:

	/**********************************************************************************************//**
	 * <summary> Provides registration access to GameObject functions.</summary>
	 *
	 * <remarks> </remarks>
	 **************************************************************************************************/
	class RegistrationAccess
	{
		friend class GameObjectEntryCommand;
		friend class GameObjectExitCommand;

		/**********************************************************************************************//**
		 * <summary> Registration access for connecting to the scene. </summary>
		 *  
		 * <remarks> ONLY GameObjectEntryCommand and GameObjectEntryCommand have access. </remarks>
		 *
		 * <param name="pGameObject"> a game object pointer.</param>
		 **************************************************************************************************/
		static void ConnectToScene(GameObject* pGameObject) { pGameObject->connectToScene(); }

		/**********************************************************************************************//**
		 * <summary> Deregistration access for disconnect from the scene. </summary>
		 *  
		 * <remarks> ONLY GameObjectEntryCommand and GameObjectEntryCommand have access. </remarks>
		 *
		 * <param name="pGameObject"> a game object pointer.</param>
		 **************************************************************************************************/
		static void DisconnectFromScene(GameObject* pGameObject) { pGameObject->disconnectFromScene();}
	};
};
#endif // !_GameObjectAttorney

//-----------------------------------------------------------------------------------------------------------------------------
// GameObjectAttorney Comment Template
//-----------------------------------------------------------------------------------------------------------------------------