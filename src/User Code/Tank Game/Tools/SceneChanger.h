#ifndef _SceneChanger
#define _SceneChanger

#include "GameObject.h"

class Scene;
class SceneSwitcher;

class SceneChanger : public GameObject
{
public:
	SceneChanger();
	SceneChanger(const SceneChanger&) = default;
	SceneChanger& operator=(const SceneChanger&) = default;
	SceneChanger(SceneChanger&&) = default;
	SceneChanger& operator=(SceneChanger&&) = default;
	~SceneChanger();

	void setNextScene(Scene*);
	void setPreviousScene(Scene*);

private:
	virtual void keyPressed(AZUL_KEY) override;

private:
	const static AZUL_KEY NEXT_SCENE_KEY;
	const static AZUL_KEY PREVIOUS_SCENE_KEY;

	SceneSwitcher* _pNextScene;
	SceneSwitcher* _pPreviousScene;
};
#endif // !_SceneChanger

//-----------------------------------------------------------------------------------------------------------------------------
// SceneChanger Comment Template
//-----------------------------------------------------------------------------------------------------------------------------