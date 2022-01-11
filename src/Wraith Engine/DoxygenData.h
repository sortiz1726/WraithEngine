/** \defgroup Wraith-API Wraith API
\brief These are reference of commands to be used by the user.
*/

/************************************* GAME INITIALIZE AND END *************************************/

/** \defgroup GAME_INITALIZE_END Game Initialize and End
\ingroup Wraith-API
\brief User defined functions to set up and end the game

Game Initialize is used mostly for setting up window settings. Game End is used for user clean up such as 
factories, pools, and clean up.
Here is an example of how to use it properly.
	\code

	NOTE: in GameInitialize.cpp
	// -----------------------------------------------------------------------------
	// To be defined by user (Specific to each game)
	// -----------------------------------------------------------------------------
	#include "Wraith.h"

	void Wraith::gameInitialize()
	{
		Wraith::PrintTitleMessage("Game Initializing");
		// Wraith Window Device setup
		Wraith::SetWindowName("Wraith Engine");
		Wraith::SetWindowWidthAndHeight(800, 600);
		Wraith::SetBackgroundColor(0.4f, 0.4f, 0.8f, 1.0f);
	
		// Use this area, for one time non-graphic creation
	
		Trace::out("\n");
	}

	NOTE: in GameEnd.cpp
	// -----------------------------------------------------------------------------
	// To be defined by user (Specific to each game)
	// -----------------------------------------------------------------------------
	#include "Wraith.h"

	#include "BulletFactory.h"
	#include "BulletPool.h"
	
	#include "TankFactory.h"
	#include "TankControllerPlayerFactory.h"
	#include "TankControllerAIFactory.h"
	#include "TankControllerAISniperFactory.h"
	#include "TankControllerAIChargerFactory.h"
	#include "TankControllerNullFactory.h"
	
	#include "TankControllerPlayerPool.h"
	#include "TankControllerAIPool.h"
	#include "TankControllerAISniperPool.h"
	#include "TankControllerAIChargerPool.h"
	#include "TankControllerNullPool.h"

	void Wraith::gameEnd()
	{
		Wraith::PrintTitleMessage("Game Ending");
		// Use this area for final user-related clean-up
	
		BulletFactory::Termintate();
		TankFactory::Termintate();
	
		TankControllerPlayerFactory::Terminate();
		TankControllerAIFactory::Terminate();
		TankControllerAISniperFactory::Terminate();
		TankControllerAIChargerFactory::Terminate();
		TankControllerNullFactory::Terminate();
	
		TankControllerPlayerPool::Terminate();
		TankControllerAIPool::Terminate();
		TankControllerAISniperPool::Terminate();
		TankControllerAIChargerPool::Terminate();
		TankControllerNullPool::Terminate();
	
		Trace::out("\n");
	}

	\endcode

*/

/************************************* GAMEOBJECT *************************************/

/** \defgroup GAMEOBJECT GameObject
\ingroup Wraith-API
\brief All user defined game entities will be derived from GameObject base class.
*/

/** \defgroup UPDATE Update
\ingroup GAMEOBJECT
\brief For updating the GameObject entity every frame. NOTE: GameObject Entity must be registered in order to process GameObject::update callback.

The Update callback is called by the current Scene every frame.
Here is an example of Tank moving foward at a constant rate.
	\code
	Tank::Tank()
	{
		_speed = 5.0f;
		GameObject::submitUpdateRegistration();
	}

	void Tank::Update() // The update callback
	{
		Vect moveOffset += Vect(0.0f, 0.0f, 1.0f) * _speed;
		this->move(moveOffset);
	}
	\endcode

*/

/** \defgroup DRAW Draw
\ingroup GAMEOBJECT
\brief For drawing the GameObject entity every frame.
There are two draw callbacks: GameObject::draw() used for rendering models and GameObject::draw2D() used for rendering Sprite entities.
NOTE: GameObject Entity must be registered (using GameObject::submitDrawRegistration() or GameObject::submitDraw2DRegistration())in order to process GameObject::draw and GameObject::draw2D callback.

The Draw callback is called by the current Scene every frame.
Here is an example of WindMill rendering it model.
NOTE: this requires the use of SceneManager to get the current scene and getting the scene's current Camera.
	\code
	WindMill::WindMill()
	{
		// Create Graphics Object
		Model* pWindMillModel = ModelManager::GetModel("WindMill");
		ShaderObject* pTextureShader = ShaderManager::GetDefaultShader(ShaderManager::DefaultShader::TEXTURE);
		Texture* pWindMillTexture = TextureManager::GetTexture("WindMill");

		_pGraphicsObject_WindMill = new GraphicsObject_TextureFlat(pWindMillModel, pTextureShader, pWindMillTexture);

		// IMPORTANT: Submit Draw Registrations
		GameObject::submitDrawRegistration();
	}

	void WindMill::draw() // The draw callback
	{
		// Get current camera
		Camera* pCamera = SceneManager::GetCurrentScene()->getCurrentCamera();

		_pGraphicsObject_WindMill->render(pCamera);
	}
	\endcode

Here is an example of a HUD rendering a "Game Over" image (using the Sprite).
NOTE: rendering Sprite entities does need the use of access the current 2D camera.
	\code
	HUD::HUD()
	{
		// Sprite
		_pGameOverSprite = new Sprite("GameOverImage");
		_pGameOverSprite->setPosition(250.0f, 250.0f);

		// Submit Registration
		// IMPORTANT: For sprites, you must render in draw2D() callback.
		// Make sure to call  submitDrawRegistration2D() for registration
		GameObject::submitDraw2DRegistration();
	}

	void HUD::draw2D() // The draw2D callback
	{
		_pGameOverSprite->render();
	}

	\endcode

*/

/** \defgroup ALARMS Alarms
\ingroup GAMEOBJECT

\brief Each GameObject has up to 3 alarms to used. NOTE: GameObject Entity must be registered in order to process GameObject::alarm0, GameObject::alarm1, and GameObject::alarm2 callbacks.

Alarms are simple countdown mechanism to help control time-based events. Uses AlarmID for setting a specific alarm.
Below is a simple example of a self-resetting alarm to make the Tank shoot at a constant rate
	\code
	Tank::Tank( )
	{
		_fireBulletDelay = 2.0f;
		GameObject::submitAlarmRegistration(_fireBulletDelay, AlarmID::ALARM_0);	// sets Alarm 0 to go off in 2 secs

		_moveTimeDelay = 5.5f;
		GameObject::submitAlarmRegistration(_moveTimeDelay, AlarmabaleManager::AlarmID::ALARM_1); // set Alarm 1 to go off in 5 secs

		_terminationTimeDelay = 60.0f;
		GameObject::submitAlarmRegistration(_terminationTimeDelay, AlarmabaleManager::AlarmID::ALARM_2);  // set Alarm 2 to go off in 60 secs
	}

	void Tank::alarm0() // This is the Alarm0 callback
	{
		this->fireBullet();
		GameObject::submitAlarmRegistration(_fireBulletDelay, AlarmID::ALARM_0);	// sets Alarm 0 to go off in 2 secs
	}

	void Tank::alarm1() // This is the Alarm1 callback
	{
		Vect randomLocation = generateRandomPosition();
		this->moveHere(randomLocation);
		GameObject::submitAlarmRegistration(_timeDelay, AlarmID::ALARM_1);	// resets Alarm 1 to go off in 5 secs
	}

	void Tank::alarm3() // This is the Alarm2 callback
	{
		this->terminate();
	}

	void Tank::terminate()
	{
		// deregistrating any possible active alarms
		// checking first it is registered before deregistrating
		if(GameObject::isRegisteredForAlarm (AlarmID::ALARM_0))
		{
			GameObject::submitAlarmDeregistration(AlarmID::ALARM_0);
		}

		if(GameObject::isRegisteredForAlarm (AlarmID::ALARM_1))
		{
			GameObject::submitAlarmDeregistration(AlarmID::ALARM_1);
		}
	}

	\endcode

*/

/** \defgroup COLLISION Collisions
\ingroup GAMEOBJECT
\brief For collision of GameObject entity tested every frame. NOTE: GameObject Entity must be registered in order to process collision callback

Collisions are a way for game objects to interact with each other on a virtual physical level.

You set up the colliders by passing in the collider model  (which is just an ordinary model) and calling 
	\code
- GameObject::setColliderModel(pColliderModel, VolumeType::BSphere) for BSphere volume

- GameObject::setColliderModel(pColliderModel, VolumeType::OBB) for OBB volume

- GameObject::setColliderModel(pColliderModel, VolumeType::AABB) for AABB volume

- GameObject::setColliderModel(pColliderModel, VolumeHierarchyType::OCTREE, maxDept) for Octree (must pass in maximum depth that is greater than or equal to 1)
	\endcode

Here is an example of setting up collision callbacks of tank, bullet, warehouse, wind mill, and tree game object.
As well as how an enitity would interact with Terrain collisions.

NOTE: This is simply to set the callbacks for collisions and not to set up the collision tests.
NOTE: The use of an octree uses the VolumeHiearchyType::OCTREE instead of VolumeType (only for BSphsere, AABB, and OBB)

That must be done within a user derived Scene entity in the Scene::initialize().
	\code
	// -----------------------------------------------------------------------------------
	// LevelOne Scene Set Up
	// -----------------------------------------------------------------------------------
	LevelOneScene::initialize() // Example of a user derived Scene Entity
	{
		setCollisionPair<Tank, Bullet>();
		setCollisionSelf<Bullet>();
		setCollisionPair<Bullet, WindMill>();

		Tank* pTank = new Tank();
		Bullet* pBullet = new Bullet();
		WindMill* pWindMill = new WindMill();
	}

	// -----------------------------------------------------------------------------------
	// Tank Game Object Set Up
	// -----------------------------------------------------------------------------------

	// IMPORTANT: Used for snapping tank to terrain
	#include "SceneManager.h"
	#include "Scene.h"
	#include "Terrain.h"

	// USES OBB for collision detection
	Tank::Tank()
	{
		// IMPORTANT: Set collidable group here using the class type of the object.
		// As well as setting the collider model 
		// and Volume Type (refer to Collidable::VolumeType)
		GameObject::setCollidableGroup<Tank>();
		GameObject::setColliderModel(_pTankModel, VolumeType::OBB);

		// Submit Registration
		GameObject::submitUpdateRegistration();
		GameObject::submitCollisionRegistration();
	}

	void Tank::update()
	{
		// IMPORTANT: For objects with changing world matrix (translating, rotating, scaling)
		// A call to update collider data must be made

		this->move(); // call to move changes position thus changes world matrix
		GameObject::updateCollisionData(worldMatrix);
	}

	void Tank::collision(Bullet* pBullet) // Bullet collision callback
	{
		this->applyDamage(pBullet->getDamageValue());
	}

	void Tank::terrainCollision() // Terrain collision
	{
		// NOTE: returns a const Terrain* not just a Terrain*.
		const Terrain* pTerrain = SceneManager::GetCurrentScene()->getTerrain();

		// Setting position close the terrain
		Vect terrainPosition = pTerrain->computePointOnTerrainObject();
		this->setPosition(terrainPosition);

		// Setting orientation based on terrain normal
		// (basically using the normal to determine how to rotate tank 
		// to make it appear tilt as it moves on the terrain)
		Vect terrainNormal = pTerrain->computePointOnTerrainObject();
		this->setOrientation(terrainPosition);
	}

	// -----------------------------------------------------------------------------------
	// Bullet Game Object Set Up
	// -----------------------------------------------------------------------------------

	// USES BSphere for collision detection
	Bullet::Bullet()
	{
		// IMPORTANT: Set collidable group here using the class type of the object.
		// As well as setting the collider model
		// and Volume Type (refer to Collidable::VolumeType)
		GameObject::setCollidableGroup<Bullet>();
		GameObject::setColliderModel(_pBulletModel, VolumeType::BSPHERE);

		// Submit Registration
		GameObject::submitUpdateRegistration();
		GameObject::submitCollisionRegistration()
	}

	void Bullet::update()
	{
		// IMPORTANT: For objects with changing world matrix (translating, rotating, scaling)
		// A call to update collider data must be made

		this->move(); // call to move changes position thus changes world matrix
		GameObject::updateCollisionData(worldMatrix);
	}

	void Bullet::collision(Tank* pTank) // Tank collision callback
	{
		this->destroy();
	}

	void Bullet::collision(Bullet* pBullet) // Bullet collision callback
	{
		this->destroy();
	}

	void Bullet::collision(WindMill* pWindMill) // WindMill collision callback
	{
		this->destroy();
	}


	void Bullet::terrainCollision() // Terrain collision
	{
		this->destroy();
	}


	// -----------------------------------------------------------------------------------
	// Warehouse Game Object Set Up
	// -----------------------------------------------------------------------------------

	// USES AABB for collision detection
	Warehouse::Warehouse()
	{
		// IMPORTANT: Set collidable group here using the class type of the object.
		// As well as setting the collider model
		// and Volume Type (refer to Collidable::VolumeType)
		GameObject::setCollidableGroup<Warehouse>();
		GameObject::setColliderModel(_pWarehouseModel, VolumeType::AABB);

		// IMPORTANT: Since this game object is stationary (meaning world matrix will not change)
		// You may update collision data once here
		GameObject::updateCollisionData(worldMatrix);

		// Submit Registration
		GameObject::submitCollisionRegistration()
	}

	void Warehouse::collision(Bullet*) // Bullet collision callback
	{
		// Does nothing
	}
	\endcode

Using Collision Volume Octree has some slight difference such as using a difference enum type VolumeHierarchyType::OCTREE
and GameObject::setColliderModel() taking an extra paremeter max depth.
IMPORTANT: The depth value must be greater than or equal to 1. Anything less will result in a error.
	\code
	// -----------------------------------------------------------------------------------
	// WindMill Game Object Set Up
	// -----------------------------------------------------------------------------------

	// USES OCTREE for collision detection
	WindMill::WindMill()
	{
		// IMPORTANT: Set collidable group here using the class type of the object.
		// As well as setting the collider model 
		// and Volume HiearchyType (refer to Collidable::VolumeHierarchyType)
		GameObject::setCollidableGroup<WindMill>();
		// IMPORTANT: Octree also takes in maximum depth (depth value must be equal to or greater than 1)
		GameObject::setColliderModel(_pWindMillModel, VolumeHierarchyType::OCTREE, 4);

		// IMPORTANT: Since this game object is stationary (meaning world matrix will not change)
		// You may update collision data once here
		GameObject::updateCollisionData(worldMatrix);

		// Submit Registration
		GameObject::submitCollisionRegistration()
	}

	void WindMill::collision(Bullet*) // Bullet collision callback
	{
		// Does nothing
	}

	// -----------------------------------------------------------------------------------
	// Tree Game Object Set Up
	// -----------------------------------------------------------------------------------

	// USES OCTREE for collision detection
	Tree::Tree()
	{
		// IMPORTANT: Set collidable group here using the class type of the object.
		// As well as setting the collider model
		// and Volume HiearchyType (refer to Collidable::VolumeHierarchyType)
		GameObject::setCollidableGroup<Tree>();
		// IMPORTANT: Octree also takes in maximum depth (depth value must be equal to or greater than 1)
		GameObject::setColliderModel(_pTreeModel, VolumeHierarchyType::OCTREE, 5);

		// IMPORTANT: Since this game object is stationary (meaning world matrix will not change)
		// You may update collision data once here
		GameObject::updateCollisionData(worldMatrix);

		// Submit Registration
		GameObject::submitCollisionRegistration()
	}

	void Tree::collision(Bullet*) // Bullet collision callback
	{
		// Does nothing
	}

	\endcode

*/

/** \defgroup INPUTS Inputs
\ingroup GAMEOBJECT
\brief For detecting inputs of GameObject entity every frame. NOTE: GameObject Entity must be registered in order to process GameObject::keyPressed and GameObject::keyReleased callbacks

Inputs from keyboard are detected in two ways. Continuous key press or single event press/release.
NOTE: For single event key press/release, GameObject entities must be registered. InputEvent enum is used for selecting the type of key event to detect
	Here is an example of setting up keyboard detection in Tank Object
	\code
	Tank::Tank()
	{
		// Submit Registration
		GameObject::submitUpdateRegistration();
		GameObject::submitKeyRegistration(AZUL_KEY::KEY_SPACE, InputEvent::KEY_PRESS); // Spacebar press detection
	}

	Tank::update() // Used for continuous key press
	{
		if(Keyboard::GetKeyState(AZUL_KEY::KEY_W))
		{
			this->moveFoward();
		}
		if(Keyboard::GetKeyState(AZUL_KEY::KEY_S))
		{
			this->moveBackward();
		}

		if(Keyboard::GetKeyState(AZUL_KEY::KEY_A))
		{
			this->turnLeft();
		}
		if(Keyboard::GetKeyState(AZUL_KEY::KEY_S))
		{
			this->turnRight();
		}
	}

	void Tank::keyPressed(AZUL_KEY key) // key press callback
	{
		if(key == AZUL_KEY::SPACE)
		{
			this->fireBullet();
		}
	}
	\endcode
*/

/** \defgroup METHODS Other Methods
\ingroup GAMEOBJECT
\brief Various methods to control internal aspects of the GameObject.

GameObject entry and exit from a Scene is mostly used when
using objects that are created and recycled from an Object Pool
For example here is where it would be used for Bullet created/recycled from a Bullet pool.
NOTE: this uses collisions for the example see \ref COLLISION "Collision Module" for more information about collisions.
As well as key inputs, see \ref INPUTS "Input Module" for more information about inputs.
	\code
	// -----------------------------------------------------------------------------------
	// Bullet Game Object Set Up
	// -----------------------------------------------------------------------------------
	Bullet::Bullet()
	{
		// Initializing Bullet Graphics Object and other settings
		// Set up collision for bullet
	}

	void Bullet::sceneEntry()
	{
		//NOTE: This is where registration for update, draw, inputs, and collision should occur
		GameObject::submitUpdateRegistration();
		GameObject::submitDrawRegistration();
		GameObject::submitCollisionRegistration();
	}

	void Bullet::sceneExit()
	{
		//NOTE: This is where deregistration for update, draw, inputs, and collision should occur
		GameObject::submitUpdateDeregistration();
		GameObject::submitDrawDeregistration();
		GameObject::submitCollisionDeregistration();

		// In this example since the Bullet was created by the pool, 
		// we return it back to the pool
		BulletPool::ReturnBullet(this);

	}

	void Bullet::collision(Tank*) // Collision with tank object
	{
		GameObject::submitSceneExit();
	}

	// -----------------------------------------------------------------------------------
	// Tank Game Object Set Up
	// -----------------------------------------------------------------------------------
	Tank::Tank()
	{
		// Submit Key registration
	}

	void Tank::keyPress(AZUL_KEY key)
	{
		if(key == AZUL_KEY::SPACE) // Fire key
		{
			// Get bullet from Bullet Pool
			Bullet* pBullet = BulletPool::GetBullet();

			Vect bulletPosition = computeBulletSpawnPosition();
			Vect bulletDirection = computeBulletDirection();
			pBullet->initialize(bulletPosition, bulletDirection);

			// Submit scene entry;
			pBullet->submitSceneEntry();
		}
	}

	\endcode

*/

/************************************* RESOURCES *************************************/

/** \defgroup RESOURCES Resources
\ingroup Wraith-API
\brief Loading external resources into the game. Uses various resource managers: ModelManager, ShaderManager, TextureManager, ImageManager, and SpriteFontManager.

Resources are loaded by the users in the LoadResource.cpp file. Here is an example of how resources are to be load
NOTE: Must include header files for all asset managers.
	\code
	#include "Wraith.h"

	#include "ModelManager.h"
	#include "ShaderManager.h"
	#include "TextureManager.h"
	#include "SceneManager.h"
	#include "ImageManager.h"
	#include "SpriteFontManager.h"
	#include "TerrainObjectManager.h

	void Wraith::loadResources()
	{
		//---------------------------------------------------------------------------------------------------------
		// Load Models
		//---------------------------------------------------------------------------------------------------------

		ModelManager::LoadModelAndAssignKey(Model::PreMadeModels::UnitSphere, "UnitSphere");
		ModelManager::LoadModelAndAssignKey(Model::PreMadeModels::UnitBox_WF, "UnitCube");
		ModelManager::LoadModelAndAssignKey("tank.azul", "Tank");
		ModelManager::LoadModelAndAssignKey("Plane.azul", "Plane");
		ModelManager::LoadModelAndAssignKey("Axis.azul", "Axis");

		//---------------------------------------------------------------------------------------------------------
		// Load Shaders
		//---------------------------------------------------------------------------------------------------------

		ShaderManager::LoadShaderAndAssignKey("colorNoTextureRender", "colorNoTexture");

		//---------------------------------------------------------------------------------------------------------
		// Load Textures
		//---------------------------------------------------------------------------------------------------------

		// load tga files
		TextureManager::LoadTextureAndAssignKey("tank.tga", "TankTexture");
		TextureManager::LoadTextureAndAssignKey("grid.tga", "GridTexture");
		TextureManager::LoadTextureAndAssignKey("mountain.tga", "MountainTexture");
		TextureManager::LoadTextureAndAssignKey("grass.tga", "GrassTexture");

		// load color textures from color values
		TextureManager::LoadTextureAndAssignKey(128, 128, 128, "Grey");
		TextureManager::LoadTextureAndAssignKey(254, 0, 0, "Red");
		TextureManager::LoadTextureAndAssignKey(0, 254, 0, "Green");
		TextureManager::LoadTextureAndAssignKey(0, 0, 254, "Blue");

		//---------------------------------------------------------------------------------------------------------
		// Load Images
		//---------------------------------------------------------------------------------------------------------

		ImageManager::LoadImageAndAssignKey("RedBar.tga", "RedBarImage");
		ImageManager::LoadImageAndAssignKey("EnemySpriteSheet.tga", new Rect(0.0f, 0.0, 19.4f, 20.05f), "Enemy1");
		ImageManager::LoadImageAndAssignKey(254, 0, 0, "RedImage");

		//---------------------------------------------------------------------------------------------------------
		// Load Images
		//---------------------------------------------------------------------------------------------------------

		SpriteFontManager::LoadSpriteFontAndAssignKey("TimesNewRoman, "HUDFont");
		SpriteFontManager::LoadSpriteFontAndAssignKey("CourierNew, "TitleFont");

		//---------------------------------------------------------------------------------------------------------
		// Load Terrain
		//---------------------------------------------------------------------------------------------------------

		TerrainObjectManager::LoadAndAssignKey("HMtest1.tga", 500.0f, 30.0f, -10.0f, "GridTexture", 1, 1, "TestTerrain");
		TerrainObjectManager::LoadAndAssignKey("FlatHeightMap.tga", 500.0f, 30.0f, -10.0f, "GrassTexture", 1, 1, "GrassTerrain");
		TerrainObjectManager::LoadAndAssignKey("MountainHeightMap.tga", 500.0f, 30.0f, -10.0f, "MountainTexture", 1, 1, "MountainTerrain");


		//---------------------------------------------------------------------------------------------------------
		// Set Starting Scene
		//---------------------------------------------------------------------------------------------------------

		SceneManager::SetStartScene(new LevelOneScene());
	}

	\endcode

	And are retrived within an GameObject entitiy like a tank like this
	NOTE: You must include ModelManager.h, ShaderManager.h, and TextureManager.h
	header files to access resources.
	\code
	#include "ModelManager.h"
	#include "ShaderManager.h"
	#include "TextureManager.h"

	// -----------------------------------------------------------------------------------
	// Tank Game Object Set Up
	// -----------------------------------------------------------------------------------
	void Tank::Tank()
	{
		// Retrivieing resources
		Model* pTankModel = ModelManager::GetModel("Tank");
		ShaderObject* pTankShader = ShaderManager::GetDefaultShader(ShaderManager::DefaultShader::LIGHTED_TEXTURE);
		Texture* pTankTexture = TextureManager::GetTexture("TankTexture");

		_pTankGraphicsObject = new GraphicsObject_FlatTexture(pTankModel, pTankShader, pTankTexture);

		Sprite _healthBar = new Sprite("RedBarImage");
	}

	\endcode

*/

/** \defgroup MODELRESOURCES Model Resources
\ingroup RESOURCES
\brief Loading external model resources into the game. As well as accessing them.
*/

/** \defgroup SHADERRESOURCES Shader Resources
\ingroup RESOURCES
\brief Loading external shader resources into the game. As well as accessing them.
*/

/** \defgroup TEXTURERESOURCES Texture Resources
\ingroup RESOURCES
\brief Loading external texture resources into the game. As well as accessing them.
*/

/** \defgroup IMAGERESOURCES Image Resources
\ingroup RESOURCES
\brief Loading external image resources into the game. As well as accessing them.
*/

/** \defgroup SPRITEFONTRESOURCES Sprite Resources
\ingroup RESOURCES
\brief Loading external sprite font resources into the game. As well as accessing them.

SpriteFonts are used mainly for SpriteString entities. SpriteFonts require two files in order to be used.
The tga image of the letters and an xml file that provides data on how to parse the image correctly.
Theses files must have the name (ex: Font1.tga and Font1.xml) and must be within the Fonts folder in order
for the SpriteFontManager to access them.
*/

/** \defgroup TERRAINRESOURCES Terrain Resources
\ingroup RESOURCES
\brief Loading external height maps (as .tga files) to create Terrain Objects. As well as accessing them.

IMPORTANT: Loading Terrain Objects should be called after all calls to TextureManager::LoadTextureAndAssignKey()
have been done to avoid errors as assiging a texture to terrain object uses the name assigned to the texture
and not the name of the file you want the texture to load.

Terrain Objects defines a terrain generated by height map along with texture, size, and UV value repeats. They have data
within them to to allow for collision and rendering to the a specific scene.
*/

/************************************* SCENE *************************************/

/** \defgroup SCENE Scene
\ingroup Wraith-API
\brief A Scene is the place where GameObject entities exists. NOTE: Users will use the SceneManager to access and set scene entities.

Scenes handle many of services and callbacks that GameObject entities have such as updating, drawing, inputs, and collisions
The Scene entities are managed by SceneManager. The SceneManager allows user access to the current scene. As well as setting the next scene.
When deriving from Scene, there are two methods the users musth implement: Scene::initialize and Scene::sceneEnd.

Scene::initialize is where the user instantiates GameObject entities. Also Scene::setCollisionPair() and  Scene::setCollisionSelf() that are to be tested within the scene.
Refer to \ref COLLISION "Collisions" for more information about collisions. As well as setting the terrain (by calling Scene::setTerrain())
the user wants to use in the scene (optional).

Scene::sceneEnd is where the user deletes any GameObject entities created and where entities created by factories should be recalled here.

Here is an example of how a user defined scene would be set up.
NOTE: Tanks create bullets with a factory so the factory must recall all bullets in Scene::sceneEnd().
	\code
	LevelOneScene::initialize()
	{
		// (OPTIONAL) Setting the terrain to be used 
		Scene::setTerrain ("MountainTerrain");
		
		// Setting Collision Tests
		// -> Collidable vs Collidable
		setCollisionSelf<Tank>();
		setCollisionPair<Tank, Bullet>();

		setCollisionSelf<Bullet>();
		setCollisionPair<Bullet, WindMill>();
		setCollisionPair<Bullet, Warehouse>();
		setCollisionPair<Bullet, Tree>();

		// -> Collidable vs Terrain
		setCollisionTerrain<Tank>();
		setCollisionTerrain<Bullet>();

		// Initialzing Entities
		Tank* pPlayerTank = new Tank();
		Tank* pEnemyTank = new Tank();

		WindMill* pWindMill_1 = new WindMill();
		WindMill* pWindMill_2 = new WindMill();
	}

	LevelOneScene::sceneEnd()
	{
		delete pPlayerTank
		delete pEnemyTank;

		delete pWindMill_1;
		delete pWindMill_2;

		// NOTE: This where factories should recall live game object.
		BulletFactory::RecallBullets();
	}

	\endcode

For switching to another scene we call on SceneManager::SetNextScene() and pass in the scene we want to switch to.
Here is an example of how a user defined GameObject SceneChanger could be used to switch to another scene
NOTE: You must include SceneManager.h header file to access SceneManager.
	\code
	#include "SceneManager.h"

	SceneChanger::SceneChanger(Scene* pNextScene)
	{
		_pNextScene = pNextScene;

		// Here we will use key press to switch for next scene
		GameObject::submitKeyRegistration(AZUL_KEY::SPACE, InputEvent::KEY_PRESS);
	}

	SceneChanger::keyPressed(AZUL_KEY key)
	{
		if(key == AZUL_KEY::SPACE)
		{
			this->switchScene();
		}
	}

	SceneChanger::switchScene()
	{
		SceneManager::SetNextScene(_pNextScene);
	}

	\endcode
*/

/************************************* SPRITES *************************************/

/** \defgroup SPRITES Sprites
\ingroup Wraith-API
\brief Sprites are 2D entites meant to display either an image using a Sprite entity or a text message using a SpriteString
*/

/** \defgroup SPRITE Sprite
\ingroup SPRITES
\brief A Sprite entity is used for displaying a 2D image on the screen. It can be used anywhere within a user defined GameObject.

The Sprite's constructor must take in a imageKey, a key used to assign to a particular image within the ImageManager,
in order to create Sprite entity.

IMPORTANT: To render a Sprite entity, it you must call Sprite::render() within the GameObject::draw2D() callback in order to display
the sprite properly.

Here is an example of how a sprite can be used.
	\code
	HUD::HUD()
	{
		_pHeartSprite = new Sprite("HeartImage");
		_pHeartSprite->setPosition(50, 100);

		_pLoadingSprite = new Sprite("LoadingImage");
		_pLoadingSprite->setPosition(10, 100);
		// IMPORTANT: Submit Draw 2D Registration
		GameObject::submitDraw2DRegistration();

		// Other registrations (not really needed for sprite)
		GameObject::submitUpdateRegistraion();
	}

	void HUD::update()
	{
		_pLoadingSprite->offsetAngle(0.05f);
	}

	void HUD::draw2D()
	{
		// IMPORTANT: if two sprites overlap each other
		// the one that gets drawn on top is the sprite
		// who's Sprite::render() was called last

		_pLoadingSprite->render();
		_pHeartSprite->render();
	}

	\endcode

*/

/** \defgroup SPRITESTRING SpriteString
\ingroup SPRITES
\brief A SpriteString entity is used for displaying a 2D text messages on the screen. It can be used anywhere within a user defined GameObject.

A SpriteString takes in a SpriteFont pointer, a message, and the X and Y position of the screen.
X = 0 and Y = 0 is the lower left corner of the screen. This is either done with the SpriteString constructor or the SpriteString::set() function.
The position of the SpriteString can changed anytime.

IMPORTANT: To render a SpriteString entity, it you must call SpriteString::render() within the GameObject::draw2D() callback in order to display
the sprite properly.

Here is an example of how a sprite can be used.
IMPORTANT: You must include SpriteString.h and SpriteFontManager.h
	\code
	#include "SpriteString.h"
	#include "SpriteFontManager.h"

	struct PlayerData
	{
		std::string _name;
		int _health;
	};

	HUD::HUD(PlayerData* pPlayerData)
	{
		_pPlayerData = pPlayerData
		SpriteFont* pFont = SpriteFontManager::GetSpriteFont("HUDFont");

		_pUserName = new SpriteString(pFont, pPlayerData->_name, 0, 500);

		_pHealth = new SpriteString();

		// IMPORTANT: Submit Draw 2D Registration
		GameObject::submitDraw2DRegistration();

		// Other registrations (not really needed for sprite)
		GameObject::submitUpdateRegistraion();
	}

	void HUD::update()
	{
		SpriteFont* pFont = SpriteFontManager::GetSpriteFont("HUDFont");
		std::string healthMessage = "Health: " + std::to_string(_pPlayerData->_health);
		_pHealth->set(pFont, "healthMessage", 0, 500);
	}

	void HUD::draw2D()
	{
		// IMPORTANT: if two sprites overlap each other
		// the one that gets drawn on top is the sprite
		// who's Sprite::render() was called last

		_pUserName->render();
		_pHealth->render();
	}

	\endcode

*/

/************************************* TERRAINS *************************************/

/** \defgroup TERRAIN Terrain
\ingroup Wraith-API
\brief Basic functions to interact with the terrain such computing the normals and points
on the terrain.

Terrain Objects holds information about the model of the terrain as well as containing the
internal mechanism for conducting collisions.

Here is an example of how to access the terrain within a game object to 
clamp the Tank to the terrain by getting the position on the terrain. As well as using the collision callback.
IMPORTANT: You must include SceneManager.h, Scene.h, and Terrain.h
	\code
	#include "SceneManager.h"
	#include "Scene.h"
	#include "Terrain.h"

	// ----------------------------------------------------------
	// Tank class
	// ----------------------------------------------------------
	void Tank::update()
	{
		// NOTE: returns a const Terrain* not just a Terrain*.
		const Terrain* pTerrain = SceneManager::GetCurrentScene()->getTerrain();

		// Setting position close the terrain
		Vect terrainPosition = pTerrain->computePointOnTerrainObject();
		this->setPosition(terrainPosition);

		// Setting orientation based on terrain normal
		// (basically using the normal to determine how to rotate tank 
		// to make it appear tilt as it moves on the terrain)
		Vect terrainNormal = pTerrain->computePointOnTerrainObject();
		this->setOrientation(terrainPosition);

		// For debugging purposes
		// visualizing the cell you are currently on.
		pTerrain->visualizeCellAt(getPosition());

	}

	// ----------------------------------------------------------
	// Bullet class
	// ----------------------------------------------------------
	void Bullet::terrainCollision() // Terrain collision
	{
		this->destroy();
	}

	\endcode

*/

/************************************* TOOLS *************************************/

/** \defgroup TOOLS Tools
\ingroup Wraith-API
\brief These are reference of tools provided by the engine that the user can use. Some are for debugging.
*/

/** \defgroup VISUALIZER Visualizer
\ingroup TOOLS
\brief The Visualizer is used for visualizing many things such as the Collision Volume of a Game Object, points in space, line segments, and rays.

The Visualizer is a tool for the user to use to for visualzing collider model. This can aid in debugging collisions.
To use it you must include Visualizer.h header file. You may pass in a Vector for the color or use the Colors namespace
for using preset color.

Here are some methods that you may want to call (shown with some input examples)
	\code
- Visualizer::ShowCollisionVolume(this->Collidable::getCollisionVolume(), Colors::Red) -> or any other color from Color namespace.

- Visualizer::ShowCollisionVolume(this->Collidable::getCollisionVolume(), Colors::Blue, 4) -> Depth value only used for Octree.

- Visualizer::ShowRay(myPosition, moveDirection, Colors::Red) -> ray length based on moveDirection vector length

- Visualizer::ShowRay(myPosition, moveDirection, 8, Colors::Red) -> ray length set to 8 due to extra length parameter

- Visualizer::ShowPointAt(myPosition, Color::Green);

- Visualizer::ShowLineSegment(myPosition, targetPosition, Colors::Blue);

	\endcode

Here is an example of how this can be used for debugging collisions.
	\code
	#include "Visualizer.h"
	#include "Colors.h"

	// NOTE: Tank class has a bool variable call _hasCollidedDebug which is used
	//  for visualizing a collision with color change

	Tank::Tank()
	{
		// IMPORTANT: Set collidable group here using the class type of the object.
		// Also set collider model
		GameObject::setCollidableGroup<Tank>();
		GameObject::setColliderModel(_pTankModel, VolumeType::OBB);

		// Submit Registration
		GameObject::submitUpdateRegistration();
		GameObject::submitCollisionRegistration();
	}

	void Tank::update()
	{
		// IMPORTANT: For objects with changing world matrix (translating, rotating, scaling)
		// A call to update collider data must be made

		this->move(); // call to move changes position thus changes world matrix
		GameObject::updateCollisionData(worldMatrix);

		// This is where the Visualizer tool is used AFTER updating collision data

		if(_hasCollidedDebug) // if it has collided show red sphere
		{
			// Colors::Red is just a Vect object.
			// You may pass in Vect object or use Colors namespace for quick access to colors
			Visualizer::ShowCollisionVolume(this->Collidable::getCollisionVolume(), Colors::Red)
		}
		else // else show blue sphere
		{
			Visualizer::ShowCollisionVolume(this->Collidable::getCollisionVolume(), Colors::Blue)
		}

		// Set _hasCollidedDebug to false afterwards
		_hasCollidedDebug = false;
	}

	void Tank::collision(Tank* pTank)
	{
		// In any collision callback set _hasCollidedDebug to true
		_hasCollidedDebug = true;
	}

	void Tank::collision(Bullet* pBullet)
	{
		// In any collision callback set _hasCollidedDebug to true
		_hasCollidedDebug = true;
	}

	\endcode

Here is an example of how this can be used for debugging collisions with </B>Octree</B>.
	\code
	#include "Visualizer.h"
	#include "Colors.h"
	#include "MathTools.h"

	// NOTE: WindMill class has a bool variable call _hasCollidedDebug which is used
	//  for visualizing a collision with color change

	WindMill::WindMill()
	{
		// IMPORTANT: Set collidable group here using the class type of the object.
		// Also set collider model
		GameObject::setCollidableGroup<WindMill>();
		GameObject::setColliderModel(_pWindMillModel, VolumeHierarchyType::OCTREE, 4);

		// Submit Registration
		GameObject::submitUpdateRegistration();
		GameObject::submitCollisionRegistration();

		// Keys used for changing render levels
		submitKeyRegistration(AZUL_KEY::KEY_1, InputEvent::KEY_PRESS);
		submitKeyRegistration(AZUL_KEY::KEY_2, InputEvent::KEY_PRESS);

		_renderLevel = 0;
	}

	void WindMill::update()
	{
		// This is where the Visualizer tool is used AFTER updating collision data

		if(_hasCollidedDebug) // if it has collided show red sphere
		{
			// Colors::Red is just a Vect object.
			// You may pass in Vect object or use Colors namespace for quick access to colors
			Visualizer::ShowCollisionVolume(this->Collidable::getCollisionVolume(), Colors::Red, _renderLevel)
		}
		else // else show blue sphere
		{
			Visualizer::ShowCollisionVolume(this->Collidable::getCollisionVolume(), Colors::Blue, _renderLevel)
		}

		// Set _hasCollidedDebug to false afterwards
		_hasCollidedDebug = false;
	}

	void WindMill::collision(Tank* pTank)
	{
		// In any collision callback set _hasCollidedDebug to true
		_hasCollidedDebug = true;
	}

	void WindMill::collision(Bullet* pBullet)
	{
		// In any collision callback set _hasCollidedDebug to true
		_hasCollidedDebug = true;
	}

	// Used for changing render level my clamping value 
	// between 0 and the max depth through getCollisionVolume.getMaxDepth()
	void WindMill::keyPressed(AZUL_KEY key)
	{
		if (key == AZUL_KEY::KEY_1) _renderLevel -= 1;
		if (key == AZUL_KEY::KEY_2) _renderLevel += 1;
		_renderLevel = MathTools::Clamp(_renderLevel, 0, getCollisionVolume().getMaxDepth());
	}

	\endcode

Here is another example of how the visualizing the point, line segment, and ray could be used.
	\code
	#include "Visualizer.h"
	#include "Colors.h"

	Tank::Tank()
	{
		// IMPORTANT: Set collidable group here using the class type of the object.
		// Also set collider model
		GameObject::setCollidableGroup<Tank>();
		GameObject::setColliderModel(_pTankModel);

		// Submit Registration
		GameObject::submitUpdateRegistration();
		GameObject::submitCollisionRegistration();
	}

	void Tank::update()
	{
		// Visualize the current direction of the tank
		Vect moveDirection = getMoveDirection();
		Vect position = getPosition();
		Visualizer::ShowRay(position, moveDirection, Colors::Red);

		// Visualize the leading point in front of the target to shoot at.
		Tank* pTarget = getTarget();
		Vect leadingPoint = computeLeadingPoint(pTarget);
		Visualizer::ShowPointAt(leadingPoint, Color::Green);

		// Visualizing the line of slight between tank and target
		Vect myPosition = getPosition();
		Vect targetPosition = pTarget->getPosition();
		Visualizer::ShowLineSegment(myPosition, targetPosition, Colors::Blue);
	}

	\endcode

*/

/** \defgroup SCREENLOG ScreenLog
\ingroup TOOLS
\brief The ScreenLog is used for displaying console messages on the game screen.

The ScreenLog is a visual alternative to the writing messages in the console. This prints out messages
directly onto the game screen. Function call to print a message similar to printf(char* format, ...) taking
Messages appear on the top left corner. You must include ScreenLog.h header file

Here is an example of how the ScreenLog could be used.
	\code
	#include "ScreenLog.h"

	// NOTE: Tank has Vect variable called _position

	Tank::Tank()
	{
		_position = Vect(0.0f, 0.0f, 0.0f);

		GameObject::submitUpdateRegistration();
	}

	void Tank::update()
	{
		this->move();

		// This is where ScreenLog::Add() is called to print a message
		// NOTE: ScreenLog::Add() can be called anywhere, not just here
		ScreenLog::Add("Tank position: (%3.1f, %3.1f, %3.1f)", _position[x], _position[y], _position[z]);
	}

	void Tank::move()
	{
		\\ moves tank and updates _position
	}

	\endcode

*/

/** \defgroup WRAITHENGINE WraithEngine
\ingroup TOOLS
\brief The Wraith engine class is the core aspect of the program that runs everything.
It also offers settings for the window display.

Useful tool for users include functions to set the window dimensions (width and height), background color, and name for the window
(All of which should be called in the GameInitialize.cpp file). Users can also access the window width and height.

Here is an example of how these tools are used:
NOTE: You must include Wraith.h header file to acesss Wraith functions.
	\code
	\\ in GameInitialize.cpp
	#include "Wraith.h"

	void Wraith::gameInitialize()
	{
		// Wraith Window Device setup
		Wraith::SetWindowName("Wraith Engine");
		Wraith::SetWindowWidthAndHeight(800, 600);
		Wraith::SetBackgroundColor(0.4f, 0.4f, 0.8f, 1.0f);
	}

	\\ in HUD.cpp (a user defined object)
	#include "Wraith.h"
	#include "Sprite.h"

	HUD::HUD
	{
		_pHealthBarSprite = new Sprite("HealthBarImage");

		// Here I want to set this HealthBarSprite to be in the top-center of the window.
		// NOTE (0, 0) is the bottom left corner of the screen

		float xPosition = (float) Wraith::GetWindowWidth() / 2.0f;
		float yPosition = (float) Wraith::GetWindowHeight() - _pHealthSprite->getHeight();

		_pHealthBarSprite->setPosition(xPosition, yPosition);
	}

	\endcode

*/

/** \defgroup TIMEMANAGER Time Manager
\ingroup TOOLS
\brief The TimeManager hold and gives user information regarding time. Also has freeze framing tool for debuggung

The TimeManager offers time information such as total time the game as been running and giving the time between frames.
The freeze framing tool can be activated and deactived by pressing F10. Use F9 to progress to the next frame

Here is a example of how the TimeManager could be used.
NOTE: You must include the TimeManager.h header file.
	\code
	#include "TimeManager.h"

	Bullet::Bullet()
	{
		_position = Vect(0.0f, 0.0f, 0.0f);
		_direction = Vect(0.0f, 0.0f, 1.0f);
		_speed = 10.0f;

		GameObject::submitUpdateRegistration();
	}

	Bullet::update()
	{
		this->move();
	}

	Bullet::move()
	{
		float deltaTime += TimeManager::GetElaspedFrameTimeInSeconds();

		// using frame time here for moving bullet
		_position += _direction * _speed * _deltaTime;

		// Then update neccessary data within bullet to use position
		// such as updating world matrix for model
	}

	\endcode

*/

/** \defgroup MATHTOOLS Math Tools
\ingroup TOOLS
\brief Provides a few math tools from MathTools namespace that user can use.
A few tools include getting scale and translation from a

*/

/************************************* GETTING STARTED *************************************/

/** \defgroup GETTINGSTARTED Getting Started
\brief Here is brief overview on to set up your new game.

<B> Step 1 </B>: Set up window settings
- \ref GAME_INITALIZE_END "Window set up": Documention regarding the set up of the window

<B> Step 2 </B>: Loading Resources and setting start scene
- \ref RESOURCES "Loading Resources": Documention regarding how to loading resources such as models, textures, and shaders.

<B> Step 3 </B>: Create a few user defined game objects. All of which derive from game object
- \ref GAMEOBJECT "Game Object": Documention regarding the use of GameObject and the services it offers

<B> Step 4 </B>: Create a user define scene
- \ref SCENE "Scene": Documention regarding the set up of the scene (including cleaning up)

<B> Step 5 </B>: User clean up
- \ref GAME_INITALIZE_END "User clean": Documention regarding clean up user factories, object pools, and other user defined system.

*/

/************************************* RECYCLING STARTED *************************************/

/** \defgroup GAMEOBJECTRECYCLING Game Object Recycling
\ Information on doing proper recycling within the game engine

When recycling Game Objects, the usage of GameObject::sceneEntry() and GameObject::sceneExit() 
(callbacks that are meant to be override and indirectly call by GameObject::submitSceneEntry() and GameObject::submitSceneExit())
is important to use.

With what ever mechanism is used to recall and deactive Game Objects (like through a factory) one must be careful of making sure
to deregister the GameObject's X-ables (Updatable, Drawable, Alarmable, Inputable, and Collidable) from the scene.

The game will stop if you deregister and X-able that wasn't registered or register one that had not been deregistered. Each
X-able has methods to determine if and X-able is registered
- GameObject::isRegisteredForUpdate()
- GameObject::isRegisteredForDraw() and Drawable::isRegisteredForDraw2D()
- GameObject::isRegisteredForAlarm() passing in an alarm ID to check (ALARM_0 , ALARM_1 , ALARM_2)
- GameObject::isRegisterForKeyWithEvent(AZUL_KEY key, InputEvent eventType) event type are KEY_PRESS and KEY_RELEASE
- GameObject::isRegisteredForCollisions()

The mechanism to recall the objects must be done in the user defined scene callback Scene::sceneEnd();

In this example there is a tank game object and a tank factory

So in the user defined scene, recalling is done in the Scene::sceneEnd()
	\code

	// In a user defined scene
	TestScene::sceneEnd()
	{
		TankFactory::RecallTanks();
	}

	\endcode

The factories which contained a collection of active tanks going to each one calling on GameObject::submitExit()
	\code
	// Factories implemented as Singletons

	TankFactory::RecallTanks()
	{
		GetInstance().privRecallTanks();
	}

	TankFactory::privRecallTanks()
	{
		for(Tank* pTank : _activeTanks)
		{
			pTank->GameObject::submitSceneExit();
		}
	}

	\endcode

In the tank class the GameObject::sceneEntry() and GameObject::sceneExit() must be override to deregisted any X-ables that have been registered
	\code

	// In Tank class

	Tank()
	{
		// registration should be done in GameObject::sceneEntry()
		// and not in the constructor of the object
	}

	void Tank::sceneEntry()
	{
		GameObject::submitUpdateRegistration();
		GameObject::submitDrawRegistration();

		// This alarm is set to call Alarm0 which....
		GameObject::submitAlarmRegistration(_fireBulletDelay, AlarmID::ALARM_0);
	}

	void Tank::Alarm0()
	{
		// fires bullet and...
		fireBullet();
		// resets Alarm0 again
		GameObject::submitAlarmRegistration(_fireBulletDelay, AlarmID::ALARM_0);
	}

	void Tank::sceneExit()
	{
		// No need to check registration since we know for certain 
		// that it is still registered since it was done only once
		// and no where in this tank code changes that (this may not alway be the case depending on how game is set up)
		GameObject::submitUpdateDeregistration();
		GameObject::submitDrawDeregistration();
		
		// Alarms on the hand (especially those that a reset multiple times)
		// would need to be check since you may not know if  it is current registered
		// when the scene ends due to timing
		if (GameObject::isRegisteredForAlarm(AlarmID::ALARM_0))
		{
			GameObject::submitAlarmDeregistration(AlarmID::ALARM_0);
		}
	}

	\endcode


*/

/************************************* WRAITH INTERNALS *************************************/

/** \defgroup WRAITH_INTERNALS Wraith Internals
\brief Provides documentation of the inner workings of the Wraith Engine
*/

/************************************* GAME OBJECT INTERNALS *************************************/

/** \defgroup GAMEOBJECT_INTERNALS GameObject Internals
\ingroup WRAITH_INTERNALS
\brief Game Object is the central entitiy of Engine for deriving and creating user define object for the game.

Game Object derives from Updatable, Drawable, Alarmable, Inputable, and Collidable. The main purpose of this object is to provide
centralize hub for all functions from derived class and registration/deregistration for the Game Object itself.

*/

/** \defgroup UPDATABLE_INTERNALS Updatable Internals
\ingroup GAMEOBJECT_INTERNALS
\brief Resposible for registration and deregistration. As well having callback for update

*/

/************************************* Wraith *************************************/

/*! \mainpage About Wraith

Wraith is a simple 3D Game Engine that allows users to create games in C++

\section features Features
Wraith provides the features for users:
	- Resources managers (ModelManager, ShaderManager, TextureManager, ImageManager, SpriteManager and TerrainManager) for handling the 
	loading and retrievial of models, textures, shaders, images, sprites, and terrain objects.
	- Scene and GameObject Bases classes for users to derive and create their own scenes and object for their game.
	- GameObject contains callbacks for updating, drawing, collisions, and inputs.

*/

/*! \page usingWraith Using Wraith
Here are User Documentations for using Wraith

- \ref Wraith-API "Wraith API": Documention for users to use in order to create the game with the engine.
- \ref TOOLS "Tools": Documention for tools that users can use for debugging their game.

Here are are Developer Documentation for using Wraith. NOTE: Only used for understanding the internals of engine.

- \ref WRAITH_INTERNALS "Wraith Internals": Documentation for Developers who want to look at the inner wokrings of the engine.

*/
