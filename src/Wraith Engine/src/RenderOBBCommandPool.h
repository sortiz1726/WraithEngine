#ifndef _RenderOBBCommandPool
#define _RenderOBBCommandPool

#include <stack>
#include <list>

class RenderOBBCommand;

/**********************************************************************************************//**
 * <summary> An Object Pool for RenderOBBCommands.</summary>
 *
 * <remarks> Used closely with Visualizer. </remarks>
 **************************************************************************************************/
class RenderOBBCommandPool
{
	typedef std::stack<RenderOBBCommand*> CommandStack;
	typedef std::list<RenderOBBCommand*> CommandList;
public:
	typedef CommandList::iterator ListReference;

private:
	RenderOBBCommandPool() = default;
	RenderOBBCommandPool(const RenderOBBCommandPool&) = delete;
	RenderOBBCommandPool& operator=(const RenderOBBCommandPool&) = delete;
	RenderOBBCommandPool(RenderOBBCommandPool&&) = delete;
	RenderOBBCommandPool& operator=(RenderOBBCommandPool&&) = delete;
	~RenderOBBCommandPool();

	static RenderOBBCommandPool& GetInstance();

	RenderOBBCommand* privGetCommand();
	void privReturnCommand(RenderOBBCommand*);

	/**********************************************************************************************//**
	 * <summary> Recall active RenderOBBCommand not currently in the pool.</summary>
	 *
	 * <remarks> Called when RenderOBBCommandPool is terminated. </remarks>
	 **************************************************************************************************/
	void recallActiveCommands();
	void deleteCommands();

public:
	/**********************************************************************************************//**
	 * <summary> Gets the command from the pool.</summary>
	 *
	 * <remarks> </remarks>
	 *
	 * <returns> A RenderOBBCommand pointer.</returns>
	 **************************************************************************************************/
	static RenderOBBCommand* GetCommand()
	{
		return GetInstance().privGetCommand();
	}

	/**********************************************************************************************//**
	 * <summary> Returns a command. to the pool</summary>
	 *
	 * <remarks> </remarks>
	 *
	 * <param name="pCommand"> A RenderOBBCommand pointer.</param>
	 **************************************************************************************************/
	static void ReturnCommand(RenderOBBCommand* pCommand)
	{
		GetInstance().privReturnCommand(pCommand);
	}

private:
	CommandStack _commandStack;
	CommandList _activeCommands;
};
#endif // !_RenderOBBCommandPool

//-----------------------------------------------------------------------------------------------------------------------------
// RenderOBBCommandPool Comment Template
//-----------------------------------------------------------------------------------------------------------------------------