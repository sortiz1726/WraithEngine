#ifndef _RenderAABBCommandPool
#define _RenderAABBCommandPool

#include <stack>
#include <list>

class RenderAABBCommand;

/**********************************************************************************************//**
 * <summary> An Object Pool for RenderAABBCommands.</summary>
 *
 * <remarks> Used closely with Visualizer. </remarks>
 **************************************************************************************************/
class RenderAABBCommandPool
{
	typedef std::stack<RenderAABBCommand*> CommandStack;
	typedef std::list<RenderAABBCommand*> CommandList;
public:
	typedef CommandList::iterator ListReference;

private:
	RenderAABBCommandPool() = default;
	RenderAABBCommandPool(const RenderAABBCommandPool&) = delete;
	RenderAABBCommandPool& operator=(const RenderAABBCommandPool&) = delete;
	RenderAABBCommandPool(RenderAABBCommandPool&&) = delete;
	RenderAABBCommandPool& operator=(RenderAABBCommandPool&&) = delete;
	~RenderAABBCommandPool();

	static RenderAABBCommandPool& GetInstance();

	RenderAABBCommand* privGetCommand();
	void privReturnCommand(RenderAABBCommand*);

	/**********************************************************************************************//**
	 * <summary> Recall active RenderAABBCommand not currently in the pool.</summary>
	 *
	 * <remarks> Called when RenderAABBCommandPool is terminated. </remarks>
	 **************************************************************************************************/
	void recallActiveCommands();
	void deleteCommands();

public:
	/**********************************************************************************************//**
	 * <summary> Gets the command from the pool.</summary>
	 *
	 * <remarks> </remarks>
	 *
	 * <returns> A RenderAABBCommand pointer.</returns>
	 **************************************************************************************************/
	static RenderAABBCommand* GetCommand()
	{
		return GetInstance().privGetCommand();
	}

	/**********************************************************************************************//**
	 * <summary> Returns a command. to the pool</summary>
	 *
	 * <remarks> Steven, 3/12/2021.</remarks>
	 *
	 * <param name="pCommand"> A RenderAABBCommand pointer.</param>
	 **************************************************************************************************/
	static void ReturnCommand(RenderAABBCommand* pCommand)
	{
		GetInstance().privReturnCommand(pCommand);
	}

private:
	CommandStack _commandStack;
	CommandList _activeCommands;
};
#endif // !_RenderAABBCommandPool

//-----------------------------------------------------------------------------------------------------------------------------
// RenderAABBCommandPool Comment Template
//-----------------------------------------------------------------------------------------------------------------------------