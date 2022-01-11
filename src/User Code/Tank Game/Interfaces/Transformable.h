#ifndef _Transformable
#define _Transformable

class Matrix;
class Vect;

class Transformable
{
public:
	Transformable() = default;
	Transformable(const Transformable&) = default;
	Transformable& operator=(const Transformable&) = default;
	Transformable(Transformable&&) = default;
	Transformable& operator=(Transformable&&) = default;
	virtual ~Transformable() = default;

	virtual void addChild(Transformable*) = 0;
	virtual void setParent(Transformable*) = 0;

	virtual void updateWorldMatrix() = 0;
	virtual Matrix getWorldMatrix() = 0;
	virtual Matrix getLocalWorldMatrx() = 0;

	virtual void setLocalPosition(const Vect& localPosition) = 0;
	virtual Vect getLocalPosition() const = 0;
	virtual Matrix getLocalPositionMatrix() const = 0;

	virtual void setLocalRotation(const Vect& localRotation) = 0;
	virtual void setLocalRotation(const Matrix& localRotation) = 0;
	virtual Matrix getLocalRotationMatrix() const = 0;

	virtual void setLocalScale(const Vect& localScale) = 0;
	virtual Vect getLocalScale() const = 0;
	virtual Matrix getLocalScaleMatrix() const = 0;

};
#endif // !_Transformable

//-----------------------------------------------------------------------------------------------------------------------------
// Transformable Comment Template
//-----------------------------------------------------------------------------------------------------------------------------