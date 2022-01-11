#include "RenderAABBCommandPool.h"
#include "RenderAABBCommand.h"

RenderAABBCommandPool& RenderAABBCommandPool::GetInstance()
{
    static RenderAABBCommandPool instance;
    return instance;
}

RenderAABBCommand* RenderAABBCommandPool::privGetCommand()
{
    RenderAABBCommand* pCommand = nullptr;

    if (!_commandStack.empty())
    {
        pCommand = _commandStack.top();
        _commandStack.pop();
    }
    else
    {
        pCommand = new RenderAABBCommand();
    }

    assert(pCommand != nullptr);

    ListReference activeReference = _activeCommands.insert(_activeCommands.end(), pCommand);
    pCommand->setActiveReference(activeReference);

    return pCommand;
}

void RenderAABBCommandPool::privReturnCommand(RenderAABBCommand* pCommand)
{
    _activeCommands.erase(pCommand->getActiveReference());
    _commandStack.push(pCommand);
}

RenderAABBCommandPool::~RenderAABBCommandPool()
{
    recallActiveCommands();
    deleteCommands();
}

void RenderAABBCommandPool::recallActiveCommands()
{
    for (RenderAABBCommand* pCommand : _activeCommands)
    {
        _commandStack.push(pCommand);
    }
    _activeCommands.clear();
}

void RenderAABBCommandPool::deleteCommands()
{
    while (!_commandStack.empty())
    {
        RenderAABBCommand* pCommand = _commandStack.top();
        delete pCommand;
        _commandStack.pop();
    }
}