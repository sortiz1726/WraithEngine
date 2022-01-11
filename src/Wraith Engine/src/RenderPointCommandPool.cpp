#include "RenderPointCommandPool.h"
#include "RenderPointCommand.h"

RenderPointCommandPool& RenderPointCommandPool::GetInstance()
{
    static RenderPointCommandPool instance;
    return instance;
}

RenderPointCommand* RenderPointCommandPool::privGetCommand()
{
    RenderPointCommand* pCommand = nullptr;

    if (!_commandStack.empty())
    {
        pCommand = _commandStack.top();
        _commandStack.pop();
    }
    else
    {
        pCommand = new RenderPointCommand();
    }

    assert(pCommand != nullptr);

    ListReference activeReference = _activeCommands.insert(_activeCommands.end(), pCommand);
    pCommand->setActiveReference(activeReference);

    return pCommand;
}

void RenderPointCommandPool::privReturnCommand(RenderPointCommand* pCommand)
{
    _activeCommands.erase(pCommand->getActiveReference());
    _commandStack.push(pCommand);
}

RenderPointCommandPool::~RenderPointCommandPool()
{
    recallActiveCommands();
    deleteCommands();
}

void RenderPointCommandPool::recallActiveCommands()
{
    for (RenderPointCommand* pCommand : _activeCommands)
    {
        _commandStack.push(pCommand);
    }
    _activeCommands.clear();
}

void RenderPointCommandPool::deleteCommands()
{
    while (!_commandStack.empty())
    {
        RenderPointCommand* pCommand = _commandStack.top();
        delete pCommand;
        _commandStack.pop();
    }
}