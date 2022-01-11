#ifndef _RenderOBBCommand
#define _RenderOBBCommand

#include "AzulCore.h"
#include "RenderCollisionVolumeCommand.h"
#include "RenderOBBCommandPool.h"

class RenderOBBCommand : public RenderCommand
{
public:
	RenderOBBCommand() = default;
	RenderOBBCommand(const RenderOBBCommand&) = default;
	RenderOBBCommand& operator=(const RenderOBBCommand&) = default;
	RenderOBBCommand(RenderOBBCommand&&) = default;
	RenderOBBCommand& operator=(RenderOBBCommand&&) = default;
	~RenderOBBCommand() = default;

	void setWorld(const Matrix&);
	void setColor(const Vect&);

	// Inherited via RenderCommand
	virtual void execute() override;

	void setActiveReference(const RenderOBBCommandPool::ListReference&);
	const RenderOBBCommandPool::ListReference& getActiveReference() const;

private:
	Matrix _world;
	Vect _color;

	// Internall
	RenderOBBCommandPool::ListReference _activeReference;

};
#endif // !_RenderOBBCommand

//-----------------------------------------------------------------------------------------------------------------------------
// RenderOBBCommand Comment Template
//-----------------------------------------------------------------------------------------------------------------------------