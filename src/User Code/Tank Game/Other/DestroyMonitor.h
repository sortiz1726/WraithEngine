#ifndef _DestroyMonitor
#define _DestroyMonitor

#include <list>
#include "GameObject.h"
#include "ObjectiveMonitor.h"

class SpriteString;
class Damagable;

class DestroyMonitor : public GameObject, public ObjectiveMonitor
{
public:
	DestroyMonitor();
	DestroyMonitor(const DestroyMonitor&) = default;
	DestroyMonitor& operator=(const DestroyMonitor&) = default;
	DestroyMonitor(DestroyMonitor&&) = default;
	DestroyMonitor& operator=(DestroyMonitor&&) = default;
	~DestroyMonitor();

	void addBuildingToDestroy(Damagable*);
	void removeBuildingToDestroy(Damagable*);

private:
	virtual void draw2D() override;

	void setBuildingsLeft(int numberOfBuildings);
	void offsetBuildingsLeft(int offset);

private:
	int _numberOfBuildings;
	SpriteString* _pBuildingLeftCounter;

	std::list<Damagable*> _buildingsToDestroy;
};
#endif // !_DestroyMonitor

//-----------------------------------------------------------------------------------------------------------------------------
// DestroyMonitor Comment Template
//-----------------------------------------------------------------------------------------------------------------------------