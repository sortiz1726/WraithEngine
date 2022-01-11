#ifndef _WorldPlane
#define _WorldPlane

#include "GameObject.h"

class WorldPlane : public GameObject
{
public:
	// Big Six
	WorldPlane();
	WorldPlane(const WorldPlane&) = default;
	WorldPlane& operator=(const WorldPlane&) = default;
	WorldPlane(WorldPlane&&) = default;
	WorldPlane& operator=(WorldPlane&&) = default;
	~WorldPlane();

	// Inherited via GameObject
	virtual void draw() override;

private:
	GraphicsObject_TextureFlat* _pGraphicsObject_Plane = nullptr;
};

#endif // !_WorldPlane