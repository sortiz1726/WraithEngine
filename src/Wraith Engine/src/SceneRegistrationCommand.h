#ifndef _Command
#define _Command

class SceneRegistrationCommand
{
public:
	// Big Six
	SceneRegistrationCommand() = default;
	SceneRegistrationCommand(const SceneRegistrationCommand&) = default;
	SceneRegistrationCommand& operator=(const SceneRegistrationCommand&) = default;
	SceneRegistrationCommand(SceneRegistrationCommand&&) = default;
	SceneRegistrationCommand& operator=(SceneRegistrationCommand&&) = default;
	virtual ~SceneRegistrationCommand() = default;

	virtual void execute() = 0;
};
#endif // !_Command

//-----------------------------------------------------------------------------------------------------------------------------
// SceneRegistrationCommand Comment Template
//-----------------------------------------------------------------------------------------------------------------------------