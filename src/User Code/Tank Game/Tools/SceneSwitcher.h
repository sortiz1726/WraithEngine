#ifndef _SceneSwitcher
#define _SceneSwitcher

class Scene;

class SceneSwitcher
{
public:
	SceneSwitcher();
	SceneSwitcher(const SceneSwitcher&) = default;
	SceneSwitcher& operator=(const SceneSwitcher&) = default;
	SceneSwitcher(SceneSwitcher&&) = default;
	SceneSwitcher& operator=(SceneSwitcher&&) = default;
	~SceneSwitcher();

	void setSceneToSwitchTo(Scene*);
	void switchScene();

private:
	Scene* _pSceneToSwitchTo;
};
#endif // !_SceneSwitcher

//-----------------------------------------------------------------------------------------------------------------------------
// SceneSwitcher Comment Template
//-----------------------------------------------------------------------------------------------------------------------------