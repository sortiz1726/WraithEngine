#ifndef _RenderPointCommandPool
#define _RenderPointCommandPool

#include <stack>
#include <list>

class RenderPointCommand;

/**********************************************************************************************//**
 * <summary> An Object Pool for RenderPointCommands.</summary>
 *
 * <remarks> Used closely with Visualizer. </remarks>
 **************************************************************************************************/
class RenderPointCommandPool
{
	typedef std::stack<RenderPointCommand*> CommandStack;
	typedef std::list<RenderPointCommand*> CommandList;
public:
	typedef CommandList::iterator ListReference;

private:
	RenderPointCommandPool() = default;
	RenderPointCommandPool(const RenderPointCommandPool&) = delete;
	RenderPointCommandPool& operator=(const RenderPointCommandPool&) = delete;
	RenderPointCommandPool(RenderPointCommandPool&&) = delete;
	RenderPointCommandPool& operator=(RenderPointCommandPool&&) = delete;
	~RenderPointCommandPool();

	static RenderPointCommandPool& GetInstance();

	RenderPointCommand* privGetCommand();
	void privReturnCommand(RenderPointCommand*);

	/**********************************************************************************************//**
	 * <summary> Recall active RenderPointCommand not currently in the pool.</summary>
	 *
	 * <remarks> Called when RenderPointCommandPool is terminated. </remarks>
	 **************************************************************************************************/
	void recallActiveCommands();
	void deleteCommands();

public:
	/**********************************************************************************************//**
	 * <summary> Gets the command from the pool.</summary>
	 *
	 * <remarks> </remarks>
	 *
	 * <returns> A RenderPointCommand pointer.</returns>
	 **************************************************************************************************/
	static RenderPointCommand* GetCommand()
	{
		return GetInstance().privGetCommand();
	}

	/**********************************************************************************************//**
	 * <summary> Returns a command. to the pool</summary>
	 *
	 * <remarks> Steven, 3/12/2021.</remarks>
	 *
	 * <param name="pCommand"> A RenderPointCommand pointer.</param>
	 **************************************************************************************************/
	static void ReturnCommand(RenderPointCommand* pCommand)
	{
		GetInstance().privReturnCommand(pCommand);
	}

private:
	CommandStack _commandStack;
	CommandList _activeCommands;
};
#endif // !_RenderPointCommandPool

//-----------------------------------------------------------------------------------------------------------------------------
// RenderPointCommandPool Comment Template
//-----------------------------------------------------------------------------------------------------------------------------