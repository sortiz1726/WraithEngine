#include "Wraith.h"
#include "BulletFactory.h"
#include "BulletPool.h"

#include "TankFactory.h"
#include "TankControllerPlayerFactory.h"
#include "TankControllerAIFactory.h"
#include "TankControllerAISniperFactory.h"
#include "TankControllerAIChargerFactory.h"
#include "TankControllerNullFactory.h"

#include "TankControllerPlayerPool.h"
#include "TankControllerAIPool.h"
#include "TankControllerAISniperPool.h"
#include "TankControllerAIChargerPool.h"
#include "TankControllerNullPool.h"

// -----------------------------------------------------------------------------
// To be defined by user (Specific to each game)
// -----------------------------------------------------------------------------
void Wraith::gameEnd()
{
	Wraith::PrintTitleMessage("Game Ending");
	// Use this area for final user-related clean-up

	BulletFactory::Termintate();
	TankFactory::Termintate();

	TankControllerPlayerFactory::Terminate();
	TankControllerAIFactory::Terminate();
	TankControllerAISniperFactory::Terminate();
	TankControllerAIChargerFactory::Terminate();
	TankControllerNullFactory::Terminate();

	TankControllerPlayerPool::Terminate();
	TankControllerAIPool::Terminate();
	TankControllerAISniperPool::Terminate();
	TankControllerAIChargerPool::Terminate();
	TankControllerNullPool::Terminate();

	Trace::out("\n");
}