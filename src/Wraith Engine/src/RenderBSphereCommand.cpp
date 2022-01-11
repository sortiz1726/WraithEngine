#include "RenderBSphereCommand.h"
#include "VisualizerAttorney.h"
#include "RenderBSphereCommandPool.h"

void RenderBSphereCommand::setWorld(const Matrix& world)
{
	_world = world;
}

void RenderBSphereCommand::setColor(const Vect& color)
{
	_color = color;
}

void RenderBSphereCommand::execute()
{
	VisualizerAttorney::RenderAccess::RenderBSphere(_world, _color);
	RenderBSphereCommandPool::ReturnCommand(this);
}

void RenderBSphereCommand::setActiveReference(const RenderBSphereCommandPool::ListReference& activeReference)
{
	_activeReference = activeReference;
}

const RenderBSphereCommandPool::ListReference& RenderBSphereCommand::getActiveReference() const
{
	return _activeReference;
}
