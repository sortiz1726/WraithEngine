#include "RenderAABBCommand.h"
#include "VisualizerAttorney.h"
#include "RenderAABBCommandPool.h"

void RenderAABBCommand::setWorld(const Matrix& world)
{
	_world = world;
}

void RenderAABBCommand::setColor(const Vect& color)
{
	_color = color;
}

void RenderAABBCommand::execute()
{
	VisualizerAttorney::RenderAccess::RenderAABB(_world, _color);
	RenderAABBCommandPool::ReturnCommand(this);
}

void RenderAABBCommand::setActiveReference(const RenderAABBCommandPool::ListReference& activeReference)
{
	_activeReference = activeReference;
}

const RenderAABBCommandPool::ListReference& RenderAABBCommand::getActiveReference() const
{
	return _activeReference;
}
