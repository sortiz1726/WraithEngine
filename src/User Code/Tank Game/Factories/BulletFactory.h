#ifndef _BulletFactory
#define _BulletFactory

#include <list>
#include "AzulCore.h"

class Bullet;

class BulletFactory
{
	typedef std::list<Bullet*> StorageContainer;
private:
	static BulletFactory* pBulletFactoryInstance;

	BulletFactory() = default;
	BulletFactory(const BulletFactory&) = delete;
	BulletFactory& operator=(const BulletFactory&) = delete;
	BulletFactory(BulletFactory&&) = delete;
	BulletFactory& operator=(BulletFactory&&) = delete;
	~BulletFactory();

	static BulletFactory& GetInstance();

	// Bullet Creation/Recycle
	Bullet* privCreateBullet(const Vect& position, const Matrix& rotation);
	void privRecycleBullet(Bullet*);
	void privRecallActiveBullets();

public:
	static Bullet* CreateBullet(const Vect& position, const Matrix& rotation) 
	{
		return GetInstance().privCreateBullet(position, rotation);
	}

	static void RecycleBullet(Bullet* pBullet)
	{
		GetInstance().privRecycleBullet(pBullet);
	}

	static void Termintate();

	static void RecallActiveBullets()
	{
		GetInstance().privRecallActiveBullets();
	}

private:
	StorageContainer _activeBullets;
};
#endif // !_BulletFactory

//-----------------------------------------------------------------------------------------------------------------------------
// BulletFactory Comment Template
//-----------------------------------------------------------------------------------------------------------------------------