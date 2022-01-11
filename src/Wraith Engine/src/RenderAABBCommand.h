#ifndef _RenderAABBCommand
#define _RenderAABBCommand

#include "AzulCore.h"
#include "RenderCollisionVolumeCommand.h"
#include "RenderAABBCommandPool.h"

class RenderAABBCommand : public RenderCommand
{
public:
	RenderAABBCommand() = default;
	RenderAABBCommand(const RenderAABBCommand&) = default;
	RenderAABBCommand& operator=(const RenderAABBCommand&) = default;
	RenderAABBCommand(RenderAABBCommand&&) = default;
	RenderAABBCommand& operator=(RenderAABBCommand&&) = default;
	~RenderAABBCommand() = default;

	void setWorld(const Matrix&);
	void setColor(const Vect&);

	// Inherited via RenderCommand
	virtual void execute() override;

	void setActiveReference(const RenderAABBCommandPool::ListReference&);
	const RenderAABBCommandPool::ListReference& getActiveReference() const;

private:
	Matrix _world;
	Vect _color;

	// Internall
	RenderAABBCommandPool::ListReference _activeReference;

};
#endif // !_RenderAABBCommand

//-----------------------------------------------------------------------------------------------------------------------------
// RenderAABBCommand Comment Template
//-----------------------------------------------------------------------------------------------------------------------------