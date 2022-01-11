#ifndef _CollisionDispatchBase
#define _CollisionDispatchBase

class Collidable;

class CollisionDispatchBase
{
public:
	CollisionDispatchBase() = default;
	CollisionDispatchBase(const CollisionDispatchBase&) = default;
	CollisionDispatchBase& operator=(const CollisionDispatchBase&) = default;
	CollisionDispatchBase(CollisionDispatchBase&&) = default;
	CollisionDispatchBase& operator=(CollisionDispatchBase&&) = default;
	virtual ~CollisionDispatchBase() = default;

	virtual void processCallBacks(Collidable*, Collidable*);
};
#endif // !_CollisionDispatchBase

//-----------------------------------------------------------------------------------------------------------------------------
// CollisionDispatchBase Comment Template
//-----------------------------------------------------------------------------------------------------------------------------