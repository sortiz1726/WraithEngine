#ifndef _DestinationMonitor
#define _DestinationMonitor

#include <queue>
#include "GameObject.h"
#include "ObjectiveMonitor.h"

class Tank;
class SpriteString;
class Marker;

class DestinationMonitor : public GameObject, public ObjectiveMonitor
{
public:
	DestinationMonitor();
	DestinationMonitor(const DestinationMonitor&) = default;
	DestinationMonitor& operator=(const DestinationMonitor&) = default;
	DestinationMonitor(DestinationMonitor&&) = default;
	DestinationMonitor& operator=(DestinationMonitor&&) = default;
	~DestinationMonitor();

	void setTarget(Tank*);
	void createMarker(const Vect& position);

	void markerHit(Marker*, Tank*);

private:
	virtual void draw2D() override;

	void setMarkersLeft(int numberOfMarkersLeft);
	void offsetMarkersLeft(int offset);

private:
	Tank* _pTarget;

	int _numberOfMarkersLeft;
	SpriteString* _pMarkersLeftlCounter;

	std::queue<Marker*> _markers;

	std::queue<Marker*> _toDelete;
};
#endif // !_DestinationMonitor

//-----------------------------------------------------------------------------------------------------------------------------
// DestinationMonitor Comment Template
//-----------------------------------------------------------------------------------------------------------------------------