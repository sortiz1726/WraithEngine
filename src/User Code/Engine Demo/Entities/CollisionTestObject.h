#ifndef _CollisionTestObject
#define _CollisionTestObject

#include "GameObject.h"

class CollisionVolumeOBB;
class Triangle;

class CollisionTestObject : public GameObject
{
public:
	CollisionTestObject();
	CollisionTestObject(const CollisionTestObject&) = default;
	CollisionTestObject& operator=(const CollisionTestObject&) = default;
	CollisionTestObject(CollisionTestObject&&) = default;
	CollisionTestObject& operator=(CollisionTestObject&&) = default;
	~CollisionTestObject();

private:
	virtual void update() override;
	virtual void draw() override;
	virtual void keyPressed(AZUL_KEY) override;

	void checkKeyboardInput();

	void drawTriangle(const Triangle&);

private:
	CollisionVolumeOBB* _pOBB;
	GraphicsObject_TextureLight* _pLeaflessTreeGraphicsObject;
	
	Matrix _world;
};
#endif // !_CollisionTestObject

//-----------------------------------------------------------------------------------------------------------------------------
// CollisionTestObject Comment Template
//-----------------------------------------------------------------------------------------------------------------------------