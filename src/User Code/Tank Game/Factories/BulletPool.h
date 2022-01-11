#ifndef _BulletPool
#define _BulletPool

#include <stack>

class Bullet;

class BulletPool
{
private:
	typedef std::stack<Bullet*> StorageContainer;
private:
	static BulletPool* pBulletPoolInstance;

	BulletPool() = default;
	BulletPool(const BulletPool&) = delete;
	BulletPool& operator=(const BulletPool&) = delete;
	BulletPool(BulletPool&&) = delete;
	BulletPool& operator=(BulletPool&&) = delete;
	~BulletPool();

	static BulletPool& GetInstance();

	// Bullet Retrival/Return
	Bullet* privGetBullet();
	void privReturnBullet(Bullet*);

	// --> Bullet Termintation helpers
	void deleteBullets();

public:
	static Bullet* GetBullet()
	{
		return GetInstance().privGetBullet();
	}

	static void ReturnBullet(Bullet* pBullet)
	{
		GetInstance().privReturnBullet(pBullet);
	}

	static void Terminate();

private:
	StorageContainer _recycledBullets;
};
#endif // !_BulletPool

//-----------------------------------------------------------------------------------------------------------------------------
// BulletPool Comment Template
//-----------------------------------------------------------------------------------------------------------------------------