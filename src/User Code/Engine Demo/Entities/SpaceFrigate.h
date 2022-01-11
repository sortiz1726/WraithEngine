#ifndef _SpaceFrigate
#define _SpaceFrigate

#include "GameObject.h"

class SpaceFrigate : public GameObject
{
public:
	// Big Six
	SpaceFrigate();
	SpaceFrigate(const SpaceFrigate&) = default;
	SpaceFrigate& operator=(const SpaceFrigate&) = default;
	SpaceFrigate(SpaceFrigate&&) = default;
	SpaceFrigate& operator=(SpaceFrigate&&) = default;
	~SpaceFrigate();

	SpaceFrigate(const std::string& name);

	// Inherited via GameObject Properties
	virtual void update() override;
	virtual void draw() override;
	virtual void alarm0() override;
	virtual void keyPressed(AZUL_KEY) override;
	virtual void keyReleased(AZUL_KEY) override;

	void toggleUpdate();
	void toggleDraw();

private:
	void updateSpaceFrigate();
	void updateBoundingSphere();

	void printCurrentTime() const;
private:
	GraphicsObject_TextureLight* _pGraphicsObject_SpaceFrigate;
	GraphicsObject_WireframeConstantColor* _pGraphicsObject_BoundingSphere;
	GraphicsObject_WireframeConstantColor* _pGraphicsObject_BoundingSphere2;

	// SpaceFrigate scale, rotation, position
	Matrix _shipScale;
	Matrix _shipRotation;
	Vect _shipPosition;

	// SpaceFrigate Properties
	std::string _name;

	const float _shipTransSpeed = 1;
	const float _shipRotationSpeed = .05f;
	bool _boundingSphereToggle = false;

	bool _canToggleDrawRegistration = true;
	bool _currentlyBeingDrawn = true;
	bool _canUpdate = true;
};

#endif // !_SpaceFrigate