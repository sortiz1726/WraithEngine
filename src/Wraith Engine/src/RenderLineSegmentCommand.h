#ifndef _RenderLineSegmentCommand
#define _RenderLineSegmentCommand

#include "AzulCore.h"
#include "RenderCollisionVolumeCommand.h"
#include "RenderLineSegmentCommandPool.h"

class RenderLineSegmentCommand : public RenderCommand
{
public:
	RenderLineSegmentCommand() = default;
	RenderLineSegmentCommand(const RenderLineSegmentCommand&) = default;
	RenderLineSegmentCommand& operator=(const RenderLineSegmentCommand&) = default;
	RenderLineSegmentCommand(RenderLineSegmentCommand&&) = default;
	RenderLineSegmentCommand& operator=(RenderLineSegmentCommand&&) = default;
	~RenderLineSegmentCommand() = default;

	void setWorld(const Matrix&);
	void setColor(const Vect&);

	// Inherited via RenderCommand
	virtual void execute() override;

	void setActiveReference(const RenderLineSegmentCommandPool::ListReference&);
	const RenderLineSegmentCommandPool::ListReference& getActiveReference() const;

private:
	Matrix _world;
	Vect _color;

	// Internall
	RenderLineSegmentCommandPool::ListReference _activeReference;

};
#endif // !_RenderLineSegmentCommand

//-----------------------------------------------------------------------------------------------------------------------------
// RenderLineSegmentCommand Comment Template
//-----------------------------------------------------------------------------------------------------------------------------