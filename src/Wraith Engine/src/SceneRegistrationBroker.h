#ifndef _SceneRegistrationBroker
#define _SceneRegistrationBroker

#include <list>

class SceneRegistrationCommand;

/**********************************************************************************************//**
 * <summary> A scene registration broker.</summary>
 *
 * <remarks> </remarks>
 **************************************************************************************************/
class SceneRegistrationBroker
{
private:
	typedef std::list<SceneRegistrationCommand*> StorageContainer;
public:
	SceneRegistrationBroker() = default;
	SceneRegistrationBroker(const SceneRegistrationBroker&) = default;
	SceneRegistrationBroker& operator=(const SceneRegistrationBroker&) = default;
	SceneRegistrationBroker(SceneRegistrationBroker&&) = default;
	SceneRegistrationBroker& operator=(SceneRegistrationBroker&&) = default;
	~SceneRegistrationBroker() = default;

	void addCommand(SceneRegistrationCommand*);

	/**********************************************************************************************//**
	 * <summary> Executes the 'commands' operation.</summary>
	 *
	 * <remarks> Steven, 3/23/2021.</remarks>
	 **************************************************************************************************/
	void executeCommands();

private:
	StorageContainer _sceneRegistrationCommands;
};
#endif // !_SceneRegistrationBroker

//-----------------------------------------------------------------------------------------------------------------------------
// SceneRegistrationBroker Comment Template
//-----------------------------------------------------------------------------------------------------------------------------