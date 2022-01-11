#ifndef _SceneManager
#define _SceneManager

class Scene;
class SceneManagerCommand;
class SceneChangeNullCommand;
class SceneChangeCommand;

/**********************************************************************************************//**
 * <summary> Manager for scenes.
 * 			 Allows access for current scene and setting scenes to use
 * 			 </summary>
 *
 * <remarks> </remarks>
 **************************************************************************************************/

class SceneManager
{
	friend class SceneManagerAttorney;

private:
	enum class SceneChangeState
	{
		PENDING_SCENE_CHANGE,
		NO_SCENE_CHANGE
	};

private:
	static SceneManager* pSceneManagerInstance;

	// Big Six
	SceneManager();
	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;
	SceneManager(SceneManager&&) = delete;
	SceneManager& operator=(SceneManager&&) = delete;
	~SceneManager();

	// Get Scene Manager
	static SceneManager& GetInstance();

	// Set Start Scene
	void  privSetStartScene(Scene*);
	void privSetNextScene(Scene*);
	
	// Get Current Scene
	Scene* privGetCurrentScene() const;

	/**********************************************************************************************//**
	 * <summary> Initializes the starting scene.</summary>
	 *
	 * <remarks> ONLY called by Wraith::LoadContent() through SceneManagerAttorney. </remarks>
	 **************************************************************************************************/
	static void InitializeStartScene()
	{
		GetInstance().privInitializeStartScene();
	}
	void privInitializeStartScene() const;

	/**********************************************************************************************//**
	 * <summary> Calls Scene::update() on current scene.</summary>
	 *
	 * <remarks> ONLY called by Wraith::update() through SceneManagerAttorney.</remarks>
	 **************************************************************************************************/
	static void Update()
	{
		GetInstance().privUpdate();
	}
	void privUpdate();

	/**********************************************************************************************//**
	 * <summary> Calls Scene::draw() on current scene.</summary>
	 *
	 * <remarks>  ONLY called by Wraith::Draw() through SceneManagerAttorney.</remarks>
	 **************************************************************************************************/
	static void Draw()
	{
		GetInstance().privDraw();
	}
	void privDraw() const;

	/**********************************************************************************************//**
	 * <summary> Changes to particular scene.</summary>
	 *
	 * <remarks> </remarks>
	 *
	 * <param name="pScene"> the pointer scene in which to change to.</param>
	 **************************************************************************************************/
	static void ChangeScene(Scene* pScene)
	{
		GetInstance().privChangeScene(pScene);
	}
	void privChangeScene(Scene*);

	// Terminate Scene Manager
	static void Delete();

public:
	/**********************************************************************************************//**
	 * <summary> Sets a start scene to begin with.</summary>
	 * \ingroup SCENE
	 * <remarks> </remarks>
	 *
	 * <param name="pScene"> pointer to the start scene.</param>
	 **************************************************************************************************/
	static void SetStartScene(Scene* pScene)
	{
		GetInstance().privSetStartScene(pScene);
	}

	/**********************************************************************************************//**
	 * <summary> Sets the next scene to change to.</summary>
	 * \ingroup SCENE
	 * <remarks> </remarks>
	 *
	 * <param name="pScene"> pointer to the next scene.</param>
	 **************************************************************************************************/
	static void SetNextScene(Scene* pScene)
	{
		GetInstance().privSetNextScene(pScene);
	}

	/**********************************************************************************************//**
	 * <summary> Gets the current scene.</summary>
	 * \ingroup SCENE
	 * <remarks> </remarks>
	 *
	 * <returns> the current scene.</returns>
	 **************************************************************************************************/
	static Scene* GetCurrentScene()
	{
		return GetInstance().privGetCurrentScene();
	}

private:
	Scene* _pCurrentScene;

	SceneChangeNullCommand* _pSceneChangeNullCommand;
	SceneChangeCommand* _pSceneChangeCommand;

	SceneManagerCommand* _pCurrentSceneCommand;

	SceneChangeState _currentSceneChangeState;
};

#endif // !_SceneManager
