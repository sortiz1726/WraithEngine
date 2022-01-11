#ifndef _GameObjectEntryCommand
#define _GameObjectEntryCommand

#include "SceneRegistrationCommand.h"

class GameObject;

/**********************************************************************************************//**
 * <summary> A game object entry command.</summary>
 * \ingroup GAMEOBJECT_INTERNALS
 * <remarks> Responsible for calling on GameObject::sceneEntry(). </remarks>
 **************************************************************************************************/
class GameObjectEntryCommand : public SceneRegistrationCommand
{
public:
	// Big Six
	GameObjectEntryCommand() = delete;
	GameObjectEntryCommand(const GameObjectEntryCommand&) = default;
	GameObjectEntryCommand& operator=(const GameObjectEntryCommand&) = default;
	GameObjectEntryCommand(GameObjectEntryCommand&&) = default;
	GameObjectEntryCommand& operator=(GameObjectEntryCommand&&) = default;
	~GameObjectEntryCommand() = default;

	/**********************************************************************************************//**
	 * <summary> Constructor getting a pointer to a GameObject.</summary>
	 *
	 * <remarks> Initialzed ONLY by GameObject::GameObject(). </remarks>
	 *
	 * <param name="pGameObject"> a game object pointer.</param>
	 **************************************************************************************************/
	GameObjectEntryCommand(GameObject* pGameObject);

	// Inherited via SceneRegistrationCommand
	
	/**********************************************************************************************//**
	 * <summary> Calls on GameObject::sceneEntry() to its current GameObject pointer.</summary>
	 *
	 * <remarks> Called ONLY by SceneRegistrationBroker::executeCommands(). </remarks>
	 **************************************************************************************************/
	virtual void execute() override;

private:
	GameObject* _pGameObject;
};
#endif // !_GameObjectEntryCommand

//-----------------------------------------------------------------------------------------------------------------------------
// GameObjectEntryCommand Comment Template
//-----------------------------------------------------------------------------------------------------------------------------