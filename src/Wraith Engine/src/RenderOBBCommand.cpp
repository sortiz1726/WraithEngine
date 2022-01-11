#include "RenderOBBCommand.h"
#include "VisualizerAttorney.h"
#include "RenderOBBCommandPool.h"

void RenderOBBCommand::setWorld(const Matrix& world)
{
	_world = world;
}

void RenderOBBCommand::setColor(const Vect& color)
{
	_color = color;
}

void RenderOBBCommand::execute()
{
	VisualizerAttorney::RenderAccess::RenderOBB(_world, _color);
	RenderOBBCommandPool::ReturnCommand(this);
}

void RenderOBBCommand::setActiveReference(const RenderOBBCommandPool::ListReference& activeReference)
{
	_activeReference = activeReference;
}

const RenderOBBCommandPool::ListReference& RenderOBBCommand::getActiveReference() const
{
	return _activeReference;
}
