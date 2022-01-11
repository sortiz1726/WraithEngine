#ifndef _RenderLineSegmentCommandPool
#define _RenderLineSegmentCommandPool

#include <stack>
#include <list>

class RenderLineSegmentCommand;

/**********************************************************************************************//**
 * <summary> An Object Pool for RenderLineSegmentCommands.</summary>
 *
 * <remarks> Used closely with Visualizer. </remarks>
 **************************************************************************************************/
class RenderLineSegmentCommandPool
{
	typedef std::stack<RenderLineSegmentCommand*> CommandStack;
	typedef std::list<RenderLineSegmentCommand*> CommandList;
public:
	typedef CommandList::iterator ListReference;

private:
	RenderLineSegmentCommandPool() = default;
	RenderLineSegmentCommandPool(const RenderLineSegmentCommandPool&) = delete;
	RenderLineSegmentCommandPool& operator=(const RenderLineSegmentCommandPool&) = delete;
	RenderLineSegmentCommandPool(RenderLineSegmentCommandPool&&) = delete;
	RenderLineSegmentCommandPool& operator=(RenderLineSegmentCommandPool&&) = delete;
	~RenderLineSegmentCommandPool();

	static RenderLineSegmentCommandPool& GetInstance();

	RenderLineSegmentCommand* privGetCommand();
	void privReturnCommand(RenderLineSegmentCommand*);

	/**********************************************************************************************//**
	 * <summary> Recall active RenderLineSegmentCommand not currently in the pool.</summary>
	 *
	 * <remarks> Called when RenderLineSegmentCommandPool is terminated. </remarks>
	 **************************************************************************************************/
	void recallActiveCommands();
	void deleteCommands();

public:
	/**********************************************************************************************//**
	 * <summary> Gets the command from the pool.</summary>
	 *
	 * <remarks> </remarks>
	 *
	 * <returns> A RenderLineSegmentCommand pointer.</returns>
	 **************************************************************************************************/
	static RenderLineSegmentCommand* GetCommand()
	{
		return GetInstance().privGetCommand();
	}

	/**********************************************************************************************//**
	 * <summary> Returns a command. to the pool</summary>
	 *
	 * <remarks> Steven, 3/12/2021.</remarks>
	 *
	 * <param name="pCommand"> A RenderLineSegmentCommand pointer.</param>
	 **************************************************************************************************/
	static void ReturnCommand(RenderLineSegmentCommand* pCommand)
	{
		GetInstance().privReturnCommand(pCommand);
	}

private:
	CommandStack _commandStack;
	CommandList _activeCommands;
};
#endif // !_RenderLineSegmentCommandPool

//-----------------------------------------------------------------------------------------------------------------------------
// RenderLineSegmentCommandPool Comment Template
//-----------------------------------------------------------------------------------------------------------------------------