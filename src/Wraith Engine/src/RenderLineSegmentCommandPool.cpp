#include "RenderLineSegmentCommandPool.h"
#include "RenderLineSegmentCommand.h"

RenderLineSegmentCommandPool& RenderLineSegmentCommandPool::GetInstance()
{
    static RenderLineSegmentCommandPool instance;
    return instance;
}

RenderLineSegmentCommand* RenderLineSegmentCommandPool::privGetCommand()
{
    RenderLineSegmentCommand* pCommand = nullptr;

    if (!_commandStack.empty())
    {
        pCommand = _commandStack.top();
        _commandStack.pop();
    }
    else
    {
        pCommand = new RenderLineSegmentCommand();
    }

    assert(pCommand != nullptr);

    ListReference activeReference = _activeCommands.insert(_activeCommands.end(), pCommand);
    pCommand->setActiveReference(activeReference);

    return pCommand;
}

void RenderLineSegmentCommandPool::privReturnCommand(RenderLineSegmentCommand* pCommand)
{
    _activeCommands.erase(pCommand->getActiveReference());
    _commandStack.push(pCommand);
}

RenderLineSegmentCommandPool::~RenderLineSegmentCommandPool()
{
    recallActiveCommands();
    deleteCommands();
}

void RenderLineSegmentCommandPool::recallActiveCommands()
{
    for (RenderLineSegmentCommand* pCommand : _activeCommands)
    {
        _commandStack.push(pCommand);
    }
    _activeCommands.clear();
}

void RenderLineSegmentCommandPool::deleteCommands()
{
    while (!_commandStack.empty())
    {
        RenderLineSegmentCommand* pCommand = _commandStack.top();
        delete pCommand;
        _commandStack.pop();
    }
}