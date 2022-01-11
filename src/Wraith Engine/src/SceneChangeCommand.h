#ifndef _SceneChangeCommand
#define _SceneChangeCommand

#include "SceneManagerCommand.h"

class Scene;

class SceneChangeCommand : public SceneManagerCommand
{
public:
	SceneChangeCommand();
	SceneChangeCommand(const SceneChangeCommand&) = default;
	SceneChangeCommand& operator=(const SceneChangeCommand&) = default;
	SceneChangeCommand(SceneChangeCommand&&) = default;
	SceneChangeCommand& operator=(SceneChangeCommand&&) = default;
	~SceneChangeCommand() = default;

	void setSceneToChangeTo(Scene*);

	// Inherited via SceneManagerCommand
	virtual void execute() override;

private:
	Scene* _pSceneToChangeTo;
};
#endif // !_SceneChangeCommand

//-----------------------------------------------------------------------------------------------------------------------------
// SceneChangeCommand Comment Template
//-----------------------------------------------------------------------------------------------------------------------------