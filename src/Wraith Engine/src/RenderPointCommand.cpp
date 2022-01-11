#include "RenderPointCommand.h"
#include "VisualizerAttorney.h"
#include "RenderPointCommandPool.h"

void RenderPointCommand::setWorld(const Matrix& world)
{
	_world = world;
}

void RenderPointCommand::setColor(const Vect& color)
{
	_color = color;
}

void RenderPointCommand::execute()
{
	VisualizerAttorney::RenderAccess::RenderPoint(_world, _color);
	RenderPointCommandPool::ReturnCommand(this);
}

void RenderPointCommand::setActiveReference(const RenderPointCommandPool::ListReference& activeReference)
{
	_activeReference = activeReference;
}

const RenderPointCommandPool::ListReference& RenderPointCommand::getActiveReference() const
{
	return _activeReference;
}
