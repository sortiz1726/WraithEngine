#ifndef _RenderCommand
#define _RenderCommand

class RenderCommand
{
public:
	RenderCommand() = default;
	RenderCommand(const RenderCommand&) = default;
	RenderCommand& operator=(const RenderCommand&) = default;
	RenderCommand(RenderCommand&&) = default;
	RenderCommand& operator=(RenderCommand&&) = default;
	virtual ~RenderCommand() = default;

	virtual void execute() = 0;
};
#endif // !_RenderCommand

//-----------------------------------------------------------------------------------------------------------------------------
// RenderCommand Comment Template
//-----------------------------------------------------------------------------------------------------------------------------