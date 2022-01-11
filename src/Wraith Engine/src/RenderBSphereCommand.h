#ifndef _RenderBSphereCommand
#define _RenderBSphereCommand

#include "AzulCore.h"
#include "RenderCollisionVolumeCommand.h"
#include "RenderBSphereCommandPool.h"

class RenderBSphereCommand : public RenderCommand
{
public:
	RenderBSphereCommand() = default;
	RenderBSphereCommand(const RenderBSphereCommand&) = default;
	RenderBSphereCommand& operator=(const RenderBSphereCommand&) = default;
	RenderBSphereCommand(RenderBSphereCommand&&) = default;
	RenderBSphereCommand& operator=(RenderBSphereCommand&&) = default;
	~RenderBSphereCommand() = default;

	void setWorld(const Matrix&);
	void setColor(const Vect&);

	// Inherited via RenderCommand
	virtual void execute() override;

	void setActiveReference(const RenderBSphereCommandPool::ListReference&);
	const RenderBSphereCommandPool::ListReference& getActiveReference() const;

private:
	Matrix _world;
	Vect _color;

	// Internall
	RenderBSphereCommandPool::ListReference _activeReference;

};
#endif // !_RenderBSphereCommand

//-----------------------------------------------------------------------------------------------------------------------------
// RenderBSphereCommand Comment Template
//-----------------------------------------------------------------------------------------------------------------------------