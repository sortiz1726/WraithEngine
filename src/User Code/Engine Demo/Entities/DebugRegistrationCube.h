#ifndef _DebugRegistrationCube
#define _DebugRegistrationCube

#include "GameObject.h"

class Tank;
class Bullet;

class DebugRegistrationCube : public GameObject
{
public:
	// Big Six
	DebugRegistrationCube();
	DebugRegistrationCube(const DebugRegistrationCube&) = default;
	DebugRegistrationCube& operator=(const DebugRegistrationCube&) = default;
	DebugRegistrationCube(DebugRegistrationCube&&) = default;
	DebugRegistrationCube& operator=(DebugRegistrationCube&&) = default;
	~DebugRegistrationCube();

	DebugRegistrationCube(const Vect& position);
	DebugRegistrationCube(const std::string& name, const std::string& colorTextureName, const Vect& startPosition, const Vect& moveDirection);

	// Quick Collsion Test
	virtual void collision(DebugRegistrationCube*);
	virtual void collision(Tank*) { Trace::out("DebugRegistrationCube_collision: Collided with Tank\n"); }
	virtual void collision(Bullet*) { Trace::out("DebugRegistrationCube_collision: Colliede with Bullet"); }
	
	void setPosition(const Vect& position);
	void setCanUpdate(bool);
	void setCanDraw(bool);
	void setCanCollide(bool);

	const std::string& getName() const;

	void toggleUpdate();
	void toggleDraw();
	void toggleCollision();

private:
	// Inherited via GameObject Properties
	virtual void update() override;
	virtual void draw() override;
	virtual void alarm0() override;
	virtual void alarm1() override;
	virtual void alarm2() override;
	virtual void keyPressed(AZUL_KEY) override;
	virtual void keyReleased(AZUL_KEY) override;

	void initializeGraphicObjectCube(const std::string& colorTextureName);

	void updateDebugRegistrationCube();
	void moveCube(const Vect& moveDirection);
	void rotateCube(float rotationOffset);
	void updateWorldMatrix();

	void printCurrentTime() const;
private:
	GraphicsObject_TextureLight* _pGraphicsObject_Cube;
	// DebugRegistrationCube scale, rotation, position
	Matrix _cubeScale;
	Matrix _cubeRotation;
	Vect _cubePosition;

	// DebugRegistrationCube Properties
	std::string _name;
	Vect _moveDirection;
	Vect _startPosition;

	const float _scale = 1.0f;
	const float _cubeRotationSpeed = 0.05f;
	const float _cubeTransSpeed = 50.0f;
	
	const float _updateToggleAlarmTime = 1.0f;
	const float _drawToggleAlarmTime = 2.0f;
	const float _resetPositionAlarmTime = 6.0f;

	bool _canDraw = true;
	bool _canUpdate = true;
	bool _canCollide = true;
};

#endif // !_DebugRegistrationCube