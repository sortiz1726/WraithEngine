#ifndef _Scene
#define _Scene

#include <string>

#include "AzulCore.h"
#include "CameraManager.h"
#include "SceneRegistrationBroker.h"
#include "UpdatableManager.h"
#include "DrawableManager.h"
#include "AlarmableManager.h"
#include "KeyboardEventManager.h"
#include "CollisionManager.h"
#include "TerrainManager.h"

class SceneRegistrationCommand;
class Updatable;
class Drawable;
class Alarmable;
class Inputable;
class Collidable;

/**********************************************************************************************//**
 * <summary> A scene.
 * 			 The place where user defined game objects are created and controlled.
 * 			 Scene handles game object related process such as update, draw, input, and collision.
 * 			 </summary>
 *
 * <remarks> Scene::initialize() and Scene::end() are functions that must be defined
 * 			 when deriving from Scene. </remarks>
 **************************************************************************************************/
class Scene
{
	friend class SceneAttorney;
public:
	// Big Six
	Scene() = default;
	Scene(const Scene&) = default;
	Scene& operator=(const Scene&) = default;
	Scene(Scene&&) = default;
	Scene& operator=(Scene&&) = default;
	virtual ~Scene();

	// Setting Camera

	/**********************************************************************************************//**
	 * <summary> Sets current camera./</summary>
	 *	\ingroup SCENE
	 * <remarks> </remarks>
	 *
	 * <param name="pCamera"> pointer to a camera</param>
	 **************************************************************************************************/
	void setCurrentCamera(Camera* pCamera);

	/**********************************************************************************************//**
	 * <summary> Sets default camera as current camera./</summary>
	 * 	\ingroup SCENE
	 * <remarks> </remarks>
	 **************************************************************************************************/
	void setDefaultCameraAsCurrentCamera();

	/**********************************************************************************************//**
	 * <summary> Sets current 2D camera.</summary>
	 * \ingroup SCENE
	 * <remarks> </remarks>
	 *
	 * <param name="p2DCamera"> pointer to a 2D Camera.</param>
	 **************************************************************************************************/
	void setCurrent2DCamera(Camera* p2DCamera);

	/**********************************************************************************************//**
	 * <summary> Sets default 2D camera as current camera 2D.</summary>
	 * 	\ingroup SCENE
	 * <remarks> </remarks>
	 **************************************************************************************************/
	void setDefault2DCameraAsCurrentCamera();


	// Getting Camera

	/**********************************************************************************************//**
	 * <summary> Gets the current camera.</summary>
	 * 	\ingroup SCENE
	 * <remarks> </remarks>
	 *
	 * <returns> current camera.</returns>
	 **************************************************************************************************/
	Camera* getCurrentCamera() const;

	/**********************************************************************************************//**
	 * <summary> Gets the default camera.</summary>
	 *	\ingroup SCENE
	 * <remarks> </remarks>
	 *
	 * <returns> the default camera.</returns>
	 **************************************************************************************************/
	Camera* getDefaultCamera() const;

	/**********************************************************************************************//**
	 * <summary> Gets the current 2D camera.</summary>
	 * 	\ingroup SCENE
	 * <remarks> </remarks>
	 *
	 * <returns> the current 2D camera.</returns>
	 **************************************************************************************************/
	Camera* getCurrent2DCamera() const;

	/**********************************************************************************************//**
	 * <summary> Gets default 2D camera.</summary>
	 * 	\ingroup SCENE
	 * <remarks> </remarks>
	 *
	 * <returns> the default 2D camera.</returns>
	 **************************************************************************************************/
	Camera* getDefault2DCamera() const;

	// Get Terrain

	/**********************************************************************************************//**
	 * <summary> Gets the current terrain from the scene.</summary>
	 * 	\ingroup SCENE
	 * 	\ingroup TERRAIN
	 * <remarks> </remarks>
	 *
	 * <returns> The terrain.</returns>
	 **************************************************************************************************/
	const Terrain* getTerrain() const;

protected:
	// Setting Collisions

	/**********************************************************************************************//**
	 * <summary> Sets collision pair between two user defined classes.</summary>
	 * \ingroup SCENE
	 * <typeparam name="UserClass1"> Type of the user class 1.</typeparam>
	 * <typeparam name="UserClass2"> Type of the user class 2.</typeparam>
	 **************************************************************************************************/
	template<class UserClass1, class UserClass2>
	void setCollisionPair()
	{
		_collisionManager.setCollisionPair<UserClass1, UserClass2>();
	}

	/**********************************************************************************************//**
	 * <summary> Sets collision within a single user defined class.</summary>
	 * \ingroup SCENE
	 * <typeparam name="UserClass"> Type of the user class.</typeparam>
	 **************************************************************************************************/
	template<class UserClass>
	void setCollisionSelf()
	{
		_collisionManager.setCollisionSelf<UserClass>();
	}

	/**********************************************************************************************//**
	* <summary> Sets collision with the terrain.</summary>
	* \ingroup SCENE
	* <typeparam name="UserClass"> Type of the user class.</typeparam>
	**************************************************************************************************/
	template<class UserClass>
	void setCollisionTerrain()
	{
		_collisionManager.setCollisionTerrain<UserClass>();
	}

	/**********************************************************************************************//**
	 * <summary>  Sets the terrain to be used in the scene.</summary>
	 * \ingroup SCENE
	 * <remarks> </remarks>
	 *
	 * <param name="terrainObjectName"> the name of the terrain object.</param>
	 **************************************************************************************************/
	void setTerrain(const std::string& terrainObjectName);

private:
	// Game Cycle

	/**********************************************************************************************//**
	 * <summary> Initializes this scene.</summary>
	 * \ingroup SCENE
	 *
	 * <remarks> </remarks>
	 **************************************************************************************************/
	virtual void initialize() = 0;

	/**********************************************************************************************//**
	 * <summary> Calls on all managers (except DrawableManager)to perform their specified GameObject callbacks
	 * 			 registered to this scene</summary>
	 *
	 * <remarks> This is called only by the SceneManager in SceneManager::Update()</remarks>
	 **************************************************************************************************/
	void update();

	/**********************************************************************************************//**
	 * <summary> Calls on DrawableManager to call Drawable::draw() and Drawable::draw2D()
	 * 			 on registered entities.</summary>
	 *
	 * <remarks> This is called only by the SceneManager in SceneManager::Draw()</remarks>
	 **************************************************************************************************/
	void draw();

	/**********************************************************************************************//**
	 * <summary> Ends the scene.</summary>
	 * \ingroup SCENE
	 *
	 * <remarks> </remarks>
	 **************************************************************************************************/
	virtual void sceneEnd() = 0;

	/**********************************************************************************************//**
	 * <summary>  Submit command for de/registration of GameObject properties.</summary>
	 *
	 * <remarks> This is used to commands to delay de/registation of GameObject properites</remarks>
	 *
	 * <param name="pCommand"> the scene de/registrationcommand.</param>
	 **************************************************************************************************/
	void submitCommand(SceneRegistrationCommand* pCommand);

	// Entity Registration/Deregistration
	void registerEntity(Updatable*);
	void deregisterEntity(Updatable*);
	
	void registerEntity(Drawable*);
	void deregisterEntity(Drawable*);

	void register2DEntity(Drawable*);
	void deregister2DEntity(Drawable*);

	void registerEntity(Alarmable*, const float time, AlarmID);
	void deregisterEntity(Alarmable*, AlarmID);

	void registerEntity(Inputable*, AZUL_KEY, InputEvent);
	void deregisterEntity(Inputable*, AZUL_KEY, InputEvent);

	void executeCommands();

	CollisionManager& getCollisionManager();

private:
	CameraManager _cameraManager;
	SceneRegistrationBroker _sceneRegistrationBroker;
	UpdatableManager _updatableManager;
	DrawableManager _drawableManager;
	AlarmableManager _alarmableManager;
	KeyboardEventManager _keyboardEventManager;
	CollisionManager _collisionManager;
	TerrainManager _terrainManager;
};

#endif // !_Scene

//-----------------------------------------------------------------------------------------------------------------------------
// Scene Comment Template
//-----------------------------------------------------------------------------------------------------------------------------