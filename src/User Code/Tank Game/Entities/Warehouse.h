#ifndef _Warehouse
#define _Warehouse

#include "GameObject.h"
#include "Damagable.h"

class Tank;
class Bullet;

class Warehouse : public GameObject, public Damagable
{
public:
	Warehouse();
	Warehouse(const Warehouse&) = default;
	Warehouse& operator=(const Warehouse&) = default;
	Warehouse(Warehouse&&) = default;
	Warehouse& operator=(Warehouse&&) = default;
	~Warehouse();

	void initialize(const Vect& position, float rotationY = 0.0f, float uniformScale = 1.0f);

	void collision(Tank*);
	void collision(Bullet*);

	// Inherited via Damagable
	virtual float getHealthPercentage() const override;
	virtual void applyDamage(float damage) override;
	virtual void setDestroyMonitor(DestroyMonitor*) override;

	// Setters/Getters
	// ---> Internals
	void setLocalPosition(const Vect& localPosition);
	Vect getLocalPosition() const;
	Matrix getLocalPositionMatrix() const;

	void setLocalRotation(float rotationY);
	void setLocalRotation(const Vect& localRotation);
	Matrix getLocalRotationMatrix() const;
	
	void setLocalScale(float uniformScale);
	void setLocalScale(const Vect& localScale);
	Vect getLocalScale() const;
	Matrix getLocalScaleMatrix() const;

private:
	virtual void draw() override;
	virtual void sceneExit() override;

	void updateWorldMatrix();
private:
	float _health;

	DestroyMonitor* _pDestroyMonitor;

	// Internals
	GraphicsObject_TextureFlat* _pWarehouseGraphicsObject;

	Vect _localScale;
	Matrix _localRotation;
	Vect _localPosition;

	bool _hasCollidedDebug;

	static const float adjustedScale;
};
#endif // !_Warehouse

//-----------------------------------------------------------------------------------------------------------------------------
// Warehouse Comment Template
//-----------------------------------------------------------------------------------------------------------------------------