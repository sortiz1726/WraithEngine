#ifndef _GameObject
#define _GameObject

#include "AzulCore.h"
#include "Updatable.h"
#include "Drawable.h"
#include "Alarmable.h"
#include "Inputable.h"
#include "Collidable.h"
#include "RegistrationStates.h"

class GameObjectEntryCommand;
class GameObjectExitCommand;

/**********************************************************************************************//**
 * <summary> A game object.
 * 			 Base class for all user defined game objects.
 * 			 Contains operations such as update, draw, input, and collision to be defined by the user.
 * 			 Also contains function to register or deregister specific game object related operations
 * 			 to the current scene.
 * 			 </summary>
 * 
 * \ingroup GAMEOBJECT_INTERNALS
 * 
 * <remarks> remarks>
 **************************************************************************************************/

class GameObject : public Updatable, public Drawable, public Alarmable, public Inputable, public Collidable
{
	friend class GameObjectAttorney;
public:
	/**********************************************************************************************//**
	 * <summary> Default constructor.</summary>
	 * 
	 * <remarks> Initializes its GameObjectEntryCommand and GameObjectExitCommand. 
	 * 			 Also sets its RegistrationState to RegistrationState::CURRENTLY_DEREGISTERED. </remarks>
	 **************************************************************************************************/
	GameObject();

	GameObject(const GameObject&) = default;
	GameObject& operator=(const GameObject&) = default;
	GameObject(GameObject&&) = default;
	GameObject& operator=(GameObject&&) = default;

	/**********************************************************************************************//**
	 * <summary> Destructor.</summary>
	 * \ingroup GAMEOBJECT_INTERNALS
	 * 
	 * <remarks> Deinitializes its GameObjectEntryCommand and GameObjectExitCommand. </remarks>
	 **************************************************************************************************/
	virtual ~GameObject();

	/**********************************************************************************************//**
	 * <summary> Submit scene entry to current scene.</summary>
	 * \ingroup METHODS
	 * <remarks> Mainly used for GameObject entities that are created and recycled with factories. </remarks>
	 **************************************************************************************************/
	void submitSceneEntry();

	/**********************************************************************************************//**
	 * <summary> Submit scene exit from current scene.</summary>
	 * \ingroup METHODS
	 * <remarks> Mainly used for GameObject entities that are created and recycled with factories. </remarks>
	 **************************************************************************************************/
	void submitSceneExit();

private:
	/**********************************************************************************************//**
	 * <summary> Connects to the current scene.</summary>
	 * \ingroup GAMEOBJECT_INTERNALS
	 * 
	 * <remarks> DELAYED call with a command. Called by SceneRegistrationBroker::executeCommands().
	 * 			 NOT called by the user. </remarks>
	 **************************************************************************************************/
	void connectToScene();

	/**********************************************************************************************//**
	 * <summary> Disconnects from the current scene.</summary>
	 * \ingroup GAMEOBJECT_INTERNALS
	 * 
	 * <remarks> DELAYED call with a command. Called by SceneRegistrationBroker::executeCommands().
	 * 			 NOT called by the user. </remarks>
	 **************************************************************************************************/
	void disconnectFromScene();

	/**********************************************************************************************//**
	 * <summary> A callback function for when a game object enters the scene .</summary>
	 * \ingroup GAMEOBJECT_INTERNALS
	 * 
	 * <remarks> CALLED by GameObjectEntryCommand::execute() through GameObjectAttorney. </remarks>
	 **************************************************************************************************/
	virtual void sceneEntry();

	/**********************************************************************************************//**
	 * <summary> A callback function for when a game object exits the scene </summary>
	 * \ingroup GAMEOBJECT_INTERNALS
	 * 
	 * <remarks> CALLED by GameObjectExitCommand::execute() through GameObjectAttorney. </remarks>
	 **************************************************************************************************/
	virtual void sceneExit();

private:
	GameObjectEntryCommand* _pGameObjectEntryCommand;
	GameObjectExitCommand* _pGameObjectExitCommand;

	RegistrationState _currentRegistrationState;
};

#endif // !_GameObject

//-----------------------------------------------------------------------------------------------------------------------------
// GameObject Comment Template
//-----------------------------------------------------------------------------------------------------------------------------