#ifndef _Campfire
#define _Campfire

#include "GameObject.h"

class Campfire : public GameObject
{
public:
	Campfire();
	Campfire(const Campfire&) = default;
	Campfire& operator=(const Campfire&) = default;
	Campfire(Campfire&&) = default;
	Campfire& operator=(Campfire&&) = default;
	~Campfire();

	void initialize(const Vect& position , float rotationY = 0.0f, float uniformScale = 1.0f);
	void initialize(const Vect& position, const Vect& rotation, const Vect& scale);

private:
	virtual void draw() override;

	// Setters/Getters
	void setLocalScale(const Vect& localScale);
	Vect getLocalScale() const;
	Matrix getLocalScaleMatrix() const;

	void setLocalRotation(const Vect& localRotation);
	Matrix getLocalRotationMatrix() const;

	void setLocalPosition(const Vect& localPosition);
	Vect getLocalPosition() const;
	Matrix getLocalPositionMatrix() const;

	void InitiailizeCampfireGraphicsObject();
	
private:
	// Internals
	GraphicsObject_TextureLight* _pCampfireGraphicsObject;

	Vect _localScale;
	Matrix _localRotation;
	Vect _localPosition;

	static const float adjustedScale;
};
#endif // !_Campfire

//-----------------------------------------------------------------------------------------------------------------------------
// Campfire Comment Template
//-----------------------------------------------------------------------------------------------------------------------------