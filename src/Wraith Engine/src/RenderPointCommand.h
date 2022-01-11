#ifndef _RenderPointCommand
#define _RenderPointCommand

#include "AzulCore.h"
#include "RenderCollisionVolumeCommand.h"
#include "RenderPointCommandPool.h"

class RenderPointCommand : public RenderCommand
{
public:
	RenderPointCommand() = default;
	RenderPointCommand(const RenderPointCommand&) = default;
	RenderPointCommand& operator=(const RenderPointCommand&) = default;
	RenderPointCommand(RenderPointCommand&&) = default;
	RenderPointCommand& operator=(RenderPointCommand&&) = default;
	~RenderPointCommand() = default;

	void setWorld(const Matrix&);
	void setColor(const Vect&);

	// Inherited via RenderCommand
	virtual void execute() override;

	void setActiveReference(const RenderPointCommandPool::ListReference&);
	const RenderPointCommandPool::ListReference& getActiveReference() const;

private:
	Matrix _world;
	Vect _color;

	// Internall
	RenderPointCommandPool::ListReference _activeReference;

};
#endif // !_RenderPointCommand

//-----------------------------------------------------------------------------------------------------------------------------
// RenderPointCommand Comment Template
//-----------------------------------------------------------------------------------------------------------------------------