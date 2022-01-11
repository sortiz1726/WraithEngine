#include "RenderBSphereCommandPool.h"
#include "RenderBSphereCommand.h"

RenderBSphereCommandPool& RenderBSphereCommandPool::GetInstance()
{
    static RenderBSphereCommandPool instance;
    return instance;
}

RenderBSphereCommand* RenderBSphereCommandPool::privGetCommand()
{
    RenderBSphereCommand* pCommand = nullptr;

    if (!_commandStack.empty())
    {
        pCommand = _commandStack.top();
        _commandStack.pop();
    }
    else
    {
        pCommand = new RenderBSphereCommand();
    }

    assert(pCommand != nullptr);

    ListReference activeReference = _activeCommands.insert(_activeCommands.end(), pCommand);
    pCommand->setActiveReference(activeReference);

    return pCommand;
}

void RenderBSphereCommandPool::privReturnCommand(RenderBSphereCommand* pCommand)
{
    _activeCommands.erase(pCommand->getActiveReference());
    _commandStack.push(pCommand);
}

RenderBSphereCommandPool::~RenderBSphereCommandPool()
{
    recallActiveCommands();
    deleteCommands();
}

void RenderBSphereCommandPool::recallActiveCommands()
{
    for (RenderBSphereCommand* pCommand : _activeCommands)
    {
        _commandStack.push(pCommand);
    }
    _activeCommands.clear();
}

void RenderBSphereCommandPool::deleteCommands()
{
    while (!_commandStack.empty())
    {
        RenderBSphereCommand* pCommand = _commandStack.top();
        delete pCommand;
        _commandStack.pop();
    }
}