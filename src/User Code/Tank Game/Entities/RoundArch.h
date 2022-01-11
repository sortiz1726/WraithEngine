#ifndef _RoundArch
#define _RoundArch

#include "GameObject.h"

class Tank;
class Bullet;

class RoundArch : public GameObject
{
public:
	RoundArch();
	RoundArch(const RoundArch&) = default;
	RoundArch& operator=(const RoundArch&) = default;
	RoundArch(RoundArch&&) = default;
	RoundArch& operator=(RoundArch&&) = default;
	~RoundArch();

	void initialize(const Vect& position, float rotationY = 0.0f, float uniformScale = 1.0f);
	void initialize(const Vect& position, const Vect& rotation, const Vect& scale);

	void collision(Tank*);
	void collision(Bullet*);
	void collision(RoundArch*);

private:
	virtual void draw() override;

	virtual void keyPressed(AZUL_KEY) override;

	// Setters/Getters
	void setLocalScale(const Vect& localScale);
	Vect getLocalScale() const;
	Matrix getLocalScaleMatrix() const;

	void setLocalRotation(const Vect& localRotation);
	Matrix getLocalRotationMatrix() const;

	void setLocalPosition(const Vect& localPosition);
	Vect getLocalPosition() const;
	Matrix getLocalPositionMatrix() const;

	void InitiailizeRoundArchGraphicsObject();

private:
	// Internals
	GraphicsObject_TextureLight* _pRoundArchGraphicsObject;

	Vect _localScale;
	Matrix _localRotation;
	Vect _localPosition;

	bool _hasCollidedDebug;

	int _renderLevel;


public:
	bool _canMove;
	bool _canDrawDebug;
};
#endif // !_RoundArch

//-----------------------------------------------------------------------------------------------------------------------------
// RoundArch Comment Template
//-----------------------------------------------------------------------------------------------------------------------------