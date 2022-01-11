#include "DestroyMonitor.h"
#include "Damagable.h"
#include "SpriteString.h"
#include "SpriteFontManager.h"
#include "SceneSwitcher.h"
#include "Wraith.h"
#include "GameController.h"

DestroyMonitor::DestroyMonitor()
	: _numberOfBuildings(0)
{
	_pBuildingLeftCounter = new SpriteString();

	submitDraw2DRegistration();
}

DestroyMonitor::~DestroyMonitor()
{
	delete _pBuildingLeftCounter;
}

void DestroyMonitor::addBuildingToDestroy(Damagable* pDamagable)
{
	pDamagable->setDestroyMonitor(this);
	_buildingsToDestroy.push_back(pDamagable);
	offsetBuildingsLeft(1);
}

void DestroyMonitor::removeBuildingToDestroy(Damagable* pDamagable)
{
	pDamagable->setDestroyMonitor(nullptr);
	_buildingsToDestroy.remove(pDamagable);
	offsetBuildingsLeft(-1);
}

#pragma region GameObject Properties

void DestroyMonitor::draw2D()
{
	_pBuildingLeftCounter->render();
}

#pragma endregion

#pragma region Actions

#pragma endregion

#pragma region Setters/Getters

void DestroyMonitor::offsetBuildingsLeft(int offset)
{
	setBuildingsLeft(_numberOfBuildings + offset);
}

void DestroyMonitor::setBuildingsLeft(int numberOfBuildings)
{
	_numberOfBuildings = numberOfBuildings;

	if (_numberOfBuildings <= 0)
	{
		_pGameController->switchToNextScene();
	}

	SpriteFont* pFont = SpriteFontManager::GetSpriteFont("MilitaryGreenFont");
	std::string message = "Buildings Left: " + std::to_string(_numberOfBuildings);
	_pBuildingLeftCounter->set(pFont, message, 0, 0);
	int positionX = 0, positionY = 0;
	//positionX = Wraith::GetWindowWidth() - _pBuildingLeftCounter->getWidth() - 10;
	positionX = 0;
	positionY = Wraith::GetWindowHeight() - _pBuildingLeftCounter->getHeight();
	_pBuildingLeftCounter->setPosition(positionX, positionY);
}

#pragma endregion