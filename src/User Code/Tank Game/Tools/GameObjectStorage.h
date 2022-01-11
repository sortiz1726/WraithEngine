#ifndef _GameObjectStorage
#define _GameObjectStorage

#include <vector>

class GameObject;

class GameObjectStorage
{
public:
	GameObjectStorage() = default;
	GameObjectStorage(const GameObjectStorage&) = default;
	GameObjectStorage& operator=(const GameObjectStorage&) = default;
	GameObjectStorage(GameObjectStorage&&) = default;
	GameObjectStorage& operator=(GameObjectStorage&&) = default;
	~GameObjectStorage();

	void addGameObject(GameObject*);

private:
	void deleteGameObjects();

private:
	std::vector<GameObject*> _storage;
};
#endif // !_GameObjectStorage

//-----------------------------------------------------------------------------------------------------------------------------
// GameObjectStorage Comment Template
//-----------------------------------------------------------------------------------------------------------------------------