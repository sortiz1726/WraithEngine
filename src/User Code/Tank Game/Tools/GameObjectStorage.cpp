#include "GameObjectStorage.h"
#include "GameObject.h"

GameObjectStorage::~GameObjectStorage()
{
	deleteGameObjects();
}

void GameObjectStorage::addGameObject(GameObject* pGameObject)
{
	_storage.push_back(pGameObject);
}

void GameObjectStorage::deleteGameObjects()
{
	for (auto& pGameObject : _storage)
	{
		delete pGameObject;
	}
}
