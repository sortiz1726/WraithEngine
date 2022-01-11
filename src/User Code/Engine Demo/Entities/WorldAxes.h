#ifndef _WorldAxes
#define _WorldAxes

#include "GameObject.h"

class WorldAxes : public GameObject
{
public:
	// Big Six
	WorldAxes();
	WorldAxes(const WorldAxes&) = default;
	WorldAxes& operator=(const WorldAxes&) = default;
	WorldAxes(WorldAxes&&) = default;
	WorldAxes& operator=(WorldAxes&&) = default;
	~WorldAxes();

	// Inherited via GameObject Properites
	virtual void draw() override;

private:
	GraphicsObject_ColorNoTexture* _pGraphicsObject_Axes;
};

#endif // !_WorldAxes