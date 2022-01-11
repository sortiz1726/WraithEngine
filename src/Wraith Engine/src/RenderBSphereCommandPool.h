#ifndef _RenderBSphereCommandPool
#define _RenderBSphereCommandPool

#include <stack>
#include <list>

class RenderBSphereCommand;

/**********************************************************************************************//**
 * <summary> An Object Pool for RenderBSphereCommands.</summary>
 *
 * <remarks> Used closely with Visualizer. </remarks>
 **************************************************************************************************/
class RenderBSphereCommandPool
{
	typedef std::stack<RenderBSphereCommand*> CommandStack;
	typedef std::list<RenderBSphereCommand*> CommandList;
public:
	typedef CommandList::iterator ListReference;

private:
	RenderBSphereCommandPool() = default;
	RenderBSphereCommandPool(const RenderBSphereCommandPool&) = delete;
	RenderBSphereCommandPool& operator=(const RenderBSphereCommandPool&) = delete;
	RenderBSphereCommandPool(RenderBSphereCommandPool&&) = delete;
	RenderBSphereCommandPool& operator=(RenderBSphereCommandPool&&) = delete;
	~RenderBSphereCommandPool();

	static RenderBSphereCommandPool& GetInstance();

	RenderBSphereCommand* privGetCommand();
	void privReturnCommand(RenderBSphereCommand*);

	/**********************************************************************************************//**
	 * <summary> Recall active RenderBSphereCommand not currently in the pool.</summary>
	 *
	 * <remarks> Called when RenderBSphereCommandPool is terminated. </remarks>
	 **************************************************************************************************/
	void recallActiveCommands();
	void deleteCommands();

public:
	/**********************************************************************************************//**
	 * <summary> Gets the command from the pool.</summary>
	 *
	 * <remarks> </remarks>
	 *
	 * <returns> A RenderBSphereCommand pointer.</returns>
	 **************************************************************************************************/
	static RenderBSphereCommand* GetCommand()
	{
		return GetInstance().privGetCommand();
	}

	/**********************************************************************************************//**
	 * <summary> Returns a command. to the pool</summary>
	 *
	 * <remarks> Steven, 3/12/2021.</remarks>
	 *
	 * <param name="pCommand"> A RenderBSphereCommand pointer.</param>
	 **************************************************************************************************/
	static void ReturnCommand(RenderBSphereCommand* pCommand)
	{
		GetInstance().privReturnCommand(pCommand);
	}

private:
	CommandStack _commandStack;
	CommandList _activeCommands;
};
#endif // !_RenderBSphereCommandPool

//-----------------------------------------------------------------------------------------------------------------------------
// RenderBSphereCommandPool Comment Template
//-----------------------------------------------------------------------------------------------------------------------------