#include "RenderLineSegmentCommand.h"
#include "VisualizerAttorney.h"
#include "RenderLineSegmentCommandPool.h"

void RenderLineSegmentCommand::setWorld(const Matrix& world)
{
	_world = world;
}

void RenderLineSegmentCommand::setColor(const Vect& color)
{
	_color = color;
}

void RenderLineSegmentCommand::execute()
{
	VisualizerAttorney::RenderAccess::RenderLineSegment(_world, _color);
	RenderLineSegmentCommandPool::ReturnCommand(this);
}

void RenderLineSegmentCommand::setActiveReference(const RenderLineSegmentCommandPool::ListReference& activeReference)
{
	_activeReference = activeReference;
}

const RenderLineSegmentCommandPool::ListReference& RenderLineSegmentCommand::getActiveReference() const
{
	return _activeReference;
}
