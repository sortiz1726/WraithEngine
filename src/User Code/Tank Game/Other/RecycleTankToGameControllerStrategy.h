#ifndef _RecycleTankToGameControllerStrategy
#define _RecycleTankToGameControllerStrategy

#include "RecycleTankStrategy.h"

class GameController;

class RecycleTankToGameControllerStrategy : public RecycleTankStrategy
{
public:
	RecycleTankToGameControllerStrategy() = default;
	RecycleTankToGameControllerStrategy(const RecycleTankToGameControllerStrategy&) = default;
	RecycleTankToGameControllerStrategy& operator=(const RecycleTankToGameControllerStrategy&) = default;
	RecycleTankToGameControllerStrategy(RecycleTankToGameControllerStrategy&&) = default;
	RecycleTankToGameControllerStrategy& operator=(RecycleTankToGameControllerStrategy&&) = default;
	~RecycleTankToGameControllerStrategy() = default;

	// Inherited via RecycleTankStrategy
	virtual void recycle(Tank*) override;

	void setGameController(GameController*);

private:
	GameController* _pGameController;
};

#endif // !_RecycleTankToGameControllerStrategy

//-----------------------------------------------------------------------------------------------------------------------------
// RecycleTankToGameControllerStrategy Comment Template
//-----------------------------------------------------------------------------------------------------------------------------