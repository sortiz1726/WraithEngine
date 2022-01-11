#ifndef _CollisionDispatch
#define _CollisionDispatch

#include "CollisionDispatchBase.h"

template<class UserClass1, class UserClass2>
class CollisionDispatch : public CollisionDispatchBase
{
public:
	CollisionDispatch() = default;
	CollisionDispatch(const CollisionDispatch&) = default;
	CollisionDispatch& operator=(const CollisionDispatch&) = default;
	CollisionDispatch(CollisionDispatch&&) = default;
	CollisionDispatch& operator=(CollisionDispatch&&) = default;
	~CollisionDispatch() = default;

	// Inherited via CollisionDispatchBase
	virtual void processCallBacks(Collidable* pCollidable1, Collidable* pCollidable2)
	{
		UserClass1* pDervivedCollidable1 = static_cast<UserClass1*>(pCollidable1);
		UserClass2* pDervivedCollidable2 = static_cast<UserClass2*>(pCollidable2);

		pDervivedCollidable1->collision(pDervivedCollidable2);
		pDervivedCollidable2->collision(pDervivedCollidable1);
	}

};
#endif // !_CollisionDispatch

//-----------------------------------------------------------------------------------------------------------------------------
// CollisionDispatch Comment Template
//-----------------------------------------------------------------------------------------------------------------------------