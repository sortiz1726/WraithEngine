#ifndef _GameObjectExitCommand
#define _GameObjectExitCommand

#include "SceneRegistrationCommand.h"

class GameObject;

/**********************************************************************************************//**
 * <summary> A game object exit command.</summary>
 * \ingroup GAMEOBJECT_INTERNALS
 * <remarks> Responsible for calling on GameObject::sceneExit(). </remarks>
 **************************************************************************************************/
class GameObjectExitCommand : public SceneRegistrationCommand
{
public:
	// Big Six
	GameObjectExitCommand() = delete;
	GameObjectExitCommand(const GameObjectExitCommand&) = default;
	GameObjectExitCommand& operator=(const GameObjectExitCommand&) = default;
	GameObjectExitCommand(GameObjectExitCommand&&) = default;
	GameObjectExitCommand& operator=(GameObjectExitCommand&&) = default;
	~GameObjectExitCommand() = default;

	/**********************************************************************************************//**
	* <summary> Constructor getting a pointer to a GameObject.</summary>
	*
	* <remarks> Initialzed ONLY by GameObject::GameObject(). </remarks>
	*
	* <param name="pGameObject"> a game object pointer.</param>
	**************************************************************************************************/
	GameObjectExitCommand(GameObject* pGameObject);

	// Inherited via SceneRegistrationCommand
	
	/**********************************************************************************************//**
	 * <summary> Calls on GameObject::sceneExit() to its current GameObject pointer.</summary>
	 *
	 * <remarks> Called ONLY by SceneRegistrationBroker::executeCommands(). </remarks>
	 **************************************************************************************************/
	virtual void execute() override;

private:
	GameObject* _pGameObject;
};
#endif // !_GameObjectExitCommand

//-----------------------------------------------------------------------------------------------------------------------------
// GameObjectExitCommand Comment Template
//-----------------------------------------------------------------------------------------------------------------------------