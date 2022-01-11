#ifndef _DrawCollisionVolumes
#define _DrawCollisionVolumes

#include "GameObject.h"
#include "CollisionVolumeOBB.h"
#include <vector>

class DrawCollisionVolumes : public GameObject
{
public:
	DrawCollisionVolumes();
	DrawCollisionVolumes(const DrawCollisionVolumes&) = default;
	DrawCollisionVolumes& operator=(const DrawCollisionVolumes&) = default;
	DrawCollisionVolumes(DrawCollisionVolumes&&) = default;
	DrawCollisionVolumes& operator=(DrawCollisionVolumes&&) = default;
	// Is it a base class? Should it be virtual?
	~DrawCollisionVolumes() = default;

	void addCollisionVolume(const CollisionVolumeOBB&);

private:
	virtual void update() override;

private:
	std::vector<CollisionVolumeOBB> _collisionVolumes;
};
#endif // !_DrawCollisionVolumes

//-----------------------------------------------------------------------------------------------------------------------------
// DrawCollisionVolumes Comment Template
//-----------------------------------------------------------------------------------------------------------------------------