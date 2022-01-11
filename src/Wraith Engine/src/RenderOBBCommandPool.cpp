#include "RenderOBBCommandPool.h"
#include "RenderOBBCommand.h"

RenderOBBCommandPool& RenderOBBCommandPool::GetInstance()
{
    static RenderOBBCommandPool instance;
    return instance;
}

RenderOBBCommand* RenderOBBCommandPool::privGetCommand()
{
    RenderOBBCommand* pCommand = nullptr;

    if (!_commandStack.empty())
    {
        pCommand = _commandStack.top();
        _commandStack.pop();
    }
    else
    {
        pCommand = new RenderOBBCommand();
    }

    assert(pCommand != nullptr);

    ListReference activeReference = _activeCommands.insert(_activeCommands.end(), pCommand);
    pCommand->setActiveReference(activeReference);

    return pCommand;
}

void RenderOBBCommandPool::privReturnCommand(RenderOBBCommand* pCommand)
{
    _activeCommands.erase(pCommand->getActiveReference());
    _commandStack.push(pCommand);
}

RenderOBBCommandPool::~RenderOBBCommandPool()
{
    recallActiveCommands();
    deleteCommands();
}

void RenderOBBCommandPool::recallActiveCommands()
{
    for (RenderOBBCommand* pCommand : _activeCommands)
    {
        _commandStack.push(pCommand);
    }
    _activeCommands.clear();
}

void RenderOBBCommandPool::deleteCommands()
{
    while (!_commandStack.empty())
    {
        RenderOBBCommand* pCommand = _commandStack.top();
        delete pCommand;
        _commandStack.pop();
    }
}