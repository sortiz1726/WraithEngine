#include "SceneManager.h"
#include "Scene.h"
#include "SceneAttorney.h"
#include "NullScene.h"
#include "SceneChangeNullCommand.h"
#include "SceneChangeCommand.h"

SceneManager* SceneManager::pSceneManagerInstance = nullptr;

SceneManager& SceneManager::GetInstance()
{
    if (pSceneManagerInstance == nullptr)
    {
        pSceneManagerInstance = new SceneManager();
    }
    assert(pSceneManagerInstance != nullptr);
    return *pSceneManagerInstance;
}

SceneManager::SceneManager()
    : _pCurrentScene(new NullScene()),
    _pCurrentSceneCommand(nullptr),
    _pSceneChangeNullCommand(new SceneChangeNullCommand()),
    _pSceneChangeCommand(new SceneChangeCommand()),
    _currentSceneChangeState(SceneChangeState::NO_SCENE_CHANGE)
{
    _pCurrentSceneCommand = _pSceneChangeNullCommand;
}

//---------------------------------------------------------------------------------------------------------
// Set and Getting Current Scenes
//---------------------------------------------------------------------------------------------------------
void SceneManager::privSetStartScene(Scene* pScene)
{
    SceneAttorney::EndAccess::SceneEnd(_pCurrentScene);
    delete _pCurrentScene;
    _pCurrentScene = pScene;
}

void SceneManager::privSetNextScene(Scene* pNextScene)
{
    assert(_currentSceneChangeState == SceneChangeState::NO_SCENE_CHANGE);
    _pSceneChangeCommand->setSceneToChangeTo(pNextScene);
    _pCurrentSceneCommand = _pSceneChangeCommand;
    _currentSceneChangeState = SceneChangeState::PENDING_SCENE_CHANGE;
}

void SceneManager::privChangeScene(Scene* pSceneToChangeTo)
{
    assert(_currentSceneChangeState == SceneChangeState::PENDING_SCENE_CHANGE);
    SceneAttorney::EndAccess::DeregisterTerrain(_pCurrentScene);
    SceneAttorney::EndAccess::ExecuteCommands(_pCurrentScene);
    SceneAttorney::EndAccess::SceneEnd(_pCurrentScene);
    delete _pCurrentScene;

    _pCurrentScene = pSceneToChangeTo;
    SceneAttorney::InitializeAccess::Initialize(_pCurrentScene);
    _pCurrentSceneCommand = _pSceneChangeNullCommand;
    _currentSceneChangeState = SceneChangeState::NO_SCENE_CHANGE;
}

Scene* SceneManager::privGetCurrentScene() const
{
    return _pCurrentScene;
}

//---------------------------------------------------------------------------------------------------------
// Initialize, Update, and Draw Current Scenes
//---------------------------------------------------------------------------------------------------------
void SceneManager::privInitializeStartScene() const
{
    SceneAttorney::InitializeAccess::Initialize(_pCurrentScene);
}

void SceneManager::privUpdate()
{
    _pCurrentSceneCommand->execute();
    SceneAttorney::GameLoopAccess::Update(_pCurrentScene);
}

void SceneManager::privDraw() const
{
    SceneAttorney::GameLoopAccess::Draw(_pCurrentScene);
}


//---------------------------------------------------------------------------------------------------------
// Deleting Manager
//---------------------------------------------------------------------------------------------------------
void SceneManager::Delete()
{
    delete pSceneManagerInstance;
    pSceneManagerInstance = nullptr;
}

SceneManager::~SceneManager()
{
    SceneAttorney::EndAccess::ExecuteCommands(_pCurrentScene);
    SceneAttorney::EndAccess::SceneEnd(_pCurrentScene);
    delete _pCurrentScene;
    delete _pSceneChangeNullCommand;
    delete _pSceneChangeCommand;
}