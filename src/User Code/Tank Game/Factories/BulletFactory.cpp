#include "BulletFactory.h"
#include "Bullet.h"
#include "BulletPool.h"
#include "TimeManager.h"

BulletFactory* BulletFactory::pBulletFactoryInstance = nullptr;

BulletFactory& BulletFactory::GetInstance()
{
    if (pBulletFactoryInstance == nullptr)
    {
        pBulletFactoryInstance = new BulletFactory();
    }
    assert(pBulletFactoryInstance != nullptr);
    return *pBulletFactoryInstance;
}

Bullet* BulletFactory::privCreateBullet(const Vect& position, const Matrix& rotation)
{
    Bullet* pBullet = BulletPool::GetBullet();
    pBullet->initialize(position, rotation);
    _activeBullets.push_back(pBullet);
    return pBullet;
}

void BulletFactory::privRecycleBullet(Bullet* pBullet)
{
    _activeBullets.remove(pBullet);
    BulletPool::ReturnBullet(pBullet);
}

void BulletFactory::privRecallActiveBullets()
{
    for (Bullet* pBullet : _activeBullets)
    {
        pBullet->submitSceneExit();
    }
}

void BulletFactory::Termintate()
{
    delete pBulletFactoryInstance;
    pBulletFactoryInstance = nullptr;
    BulletPool::Terminate();
}

BulletFactory::~BulletFactory()
{
    for (Bullet* pBullet : _activeBullets)
    {
        BulletPool::ReturnBullet(pBullet);
    }
    _activeBullets.clear();
}
