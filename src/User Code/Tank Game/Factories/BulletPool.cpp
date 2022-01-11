#include "BulletPool.h"
#include "Bullet.h"

BulletPool* BulletPool::pBulletPoolInstance = nullptr;

BulletPool& BulletPool::GetInstance()
{
	if (pBulletPoolInstance == nullptr)
	{
		pBulletPoolInstance = new BulletPool();
	}
	assert(pBulletPoolInstance != nullptr);
	return *pBulletPoolInstance;
}

//-----------------------------------------------------------------------------------------------------------------------------
// Bullet Retrival/Return
//-----------------------------------------------------------------------------------------------------------------------------
Bullet* BulletPool::privGetBullet()
{
	Bullet* pBullet = nullptr;
	if (!_recycledBullets.empty())
	{
		pBullet = _recycledBullets.top();
		_recycledBullets.pop();
	}
	else
	{
		pBullet = new Bullet();
	}
	assert(pBullet != nullptr);
	return pBullet;
}

void BulletPool::privReturnBullet(Bullet* pBullet)
{
	assert(pBullet != nullptr);
	_recycledBullets.push(pBullet);
}

//-----------------------------------------------------------------------------------------------------------------------------
// Bullet Pool Termination
//-----------------------------------------------------------------------------------------------------------------------------
void BulletPool::Terminate()
{
	delete pBulletPoolInstance;
	pBulletPoolInstance = nullptr;
}

BulletPool::~BulletPool()
{
	deleteBullets();
}

// ---> Bullet Pool Termination helper
void BulletPool::deleteBullets()
{
	while (!_recycledBullets.empty())
	{
		delete _recycledBullets.top();
		_recycledBullets.pop();
	}
}