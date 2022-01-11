#ifndef _LeaflessTree
#define _LeaflessTree

#include "GameObject.h"

class Tank;
class Bullet;

class LeaflessTree : public GameObject
{
public:
	LeaflessTree();
	LeaflessTree(const LeaflessTree&) = default;
	LeaflessTree& operator=(const LeaflessTree&) = default;
	LeaflessTree(LeaflessTree&&) = default;
	LeaflessTree& operator=(LeaflessTree&&) = default;
	~LeaflessTree();

	void initialize(const Vect& position , float rotationY = 0.0f, float uniformScale = 1.0f);
	void initialize(const Vect& position, const Vect& rotation, const Vect& scale);

	void collision(Tank*);
	void collision(Bullet*);

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

	void InitiailizeLeaflessTreeGraphicsObject();
	
private:
	// Internals
	GraphicsObject_TextureLight* _pLeaflessTreeGraphicsObject;

	Vect _localScale;
	Matrix _localRotation;
	Vect _localPosition;

	bool _hasCollidedDebug;

	static const float adjustedScale;
};
#endif // !_LeaflessTree

//-----------------------------------------------------------------------------------------------------------------------------
// LeaflessTree Comment Template
//-----------------------------------------------------------------------------------------------------------------------------