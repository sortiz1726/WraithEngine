#ifndef _SceneManagerCommand
#define _SceneManagerCommand

class SceneManagerCommand
{
public:
	SceneManagerCommand() = default;
	SceneManagerCommand(const SceneManagerCommand&) = default;
	SceneManagerCommand& operator=(const SceneManagerCommand&) = default;
	SceneManagerCommand(SceneManagerCommand&&) = default;
	SceneManagerCommand& operator=(SceneManagerCommand&&) = default;
	virtual ~SceneManagerCommand() = default;

	virtual void execute() = 0;
};
#endif // !_SceneManagerCommand

//-----------------------------------------------------------------------------------------------------------------------------
// SceneManagerCommand Comment Template
//-----------------------------------------------------------------------------------------------------------------------------