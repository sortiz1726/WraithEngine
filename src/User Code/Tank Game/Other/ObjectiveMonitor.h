#ifndef _ObjectiveMonitor
#define _ObjectiveMonitor

class GameController;

class ObjectiveMonitor
{
public:
	ObjectiveMonitor() = default;
	ObjectiveMonitor(const ObjectiveMonitor&) = default;
	ObjectiveMonitor& operator=(const ObjectiveMonitor&) = default;
	ObjectiveMonitor(ObjectiveMonitor&&) = default;
	ObjectiveMonitor& operator=(ObjectiveMonitor&&) = default;
	virtual ~ObjectiveMonitor() = default;

	void setGameControllerToNotify(GameController*);

protected:
	GameController* _pGameController;
};
#endif // !_ObjectiveMonitor

//-----------------------------------------------------------------------------------------------------------------------------
// ObjectiveMonitor Comment Template
//-----------------------------------------------------------------------------------------------------------------------------