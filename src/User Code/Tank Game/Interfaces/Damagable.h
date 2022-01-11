#ifndef _Damagable
#define _Damagable

class DestroyMonitor;

class Damagable
{
public:
	Damagable() = default;
	Damagable(const Damagable&) = default;
	Damagable& operator=(const Damagable&) = default;
	Damagable(Damagable&&) = default;
	Damagable& operator=(Damagable&&) = default;
	virtual ~Damagable() = default;

	virtual float getHealthPercentage() const = 0;
	virtual void applyDamage(float damage) = 0;
	virtual void setDestroyMonitor(DestroyMonitor*) = 0;
};
#endif // !_Damagable

//-----------------------------------------------------------------------------------------------------------------------------
// Damagable Comment Template
//-----------------------------------------------------------------------------------------------------------------------------