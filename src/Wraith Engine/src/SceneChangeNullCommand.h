#ifndef _SceneChangeNullCommand
#define _SceneChangeNullCommand

#include "SceneManagerCommand.h"

class SceneChangeNullCommand : public SceneManagerCommand
{
public:
	SceneChangeNullCommand() = default;
	SceneChangeNullCommand(const SceneChangeNullCommand&) = default;
	SceneChangeNullCommand& operator=(const SceneChangeNullCommand&) = default;
	SceneChangeNullCommand(SceneChangeNullCommand&&) = default;
	SceneChangeNullCommand& operator=(SceneChangeNullCommand&&) = default;
	~SceneChangeNullCommand() = default;

	// Inherited via SceneManagerCommand
	virtual void execute() override;
};
#endif // !_SceneChangeNullCommand

//-----------------------------------------------------------------------------------------------------------------------------
// SceneChangeNullCommand Comment Template
//-----------------------------------------------------------------------------------------------------------------------------