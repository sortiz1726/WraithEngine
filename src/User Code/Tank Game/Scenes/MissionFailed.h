#ifndef _MissionFailed
#define _MissionFailed

#include "Scene.h"

class MissionFailedController;

class MissionFailed : public Scene
{
public:
	MissionFailed() = default;
	MissionFailed(const MissionFailed&) = default;
	MissionFailed& operator=(const MissionFailed&) = default;
	MissionFailed(MissionFailed&&) = default;
	MissionFailed& operator=(MissionFailed&&) = default;
	~MissionFailed() = default;

	// Inherited via Scene
	virtual void initialize() override;
	virtual void sceneEnd() override;

	void setRestartScene(Scene*);

private:
	MissionFailedController* _pMissionFailedController;
	Scene* _pRestartScene;

};
#endif // !_MissionFailed

//-----------------------------------------------------------------------------------------------------------------------------
// MissionFailed Comment Template
//-----------------------------------------------------------------------------------------------------------------------------