#include "DestinationMonitor.h"
#include "Marker.h"

#include "Tank.h"
#include "SpriteString.h"
#include "SpriteFontManager.h"
#include "SceneSwitcher.h"
#include "Wraith.h"
#include "GameController.h"


DestinationMonitor::DestinationMonitor()
	: _pTarget(nullptr),
	_numberOfMarkersLeft(0)
{
	_pMarkersLeftlCounter = new SpriteString();

	submitDraw2DRegistration();
}

DestinationMonitor::~DestinationMonitor()
{
	while (!_markers.empty())
	{
		delete _markers.front();
		_markers.pop();
	}

	while (!_toDelete.empty())
	{
		delete _toDelete.front();
		_toDelete.pop();
	}

	delete _pMarkersLeftlCounter;
}

#pragma region GameObject Properties

void DestinationMonitor::draw2D()
{
	_pMarkersLeftlCounter->render();
}

#pragma endregion

#pragma region Actions

void DestinationMonitor::createMarker(const Vect& position)
{
	Marker* pMarker = new Marker();
	pMarker->setDestinationMonitor(this);
	pMarker->initialize(position + Vect(0.0f, 0.0f, 0.0f), 0.0f, 2.0f);
	pMarker->submitSceneEntry();

	if (_markers.empty())
	{
		pMarker->setColorGreen();
	}

	_markers.push(pMarker);

	setMarkersLeft(_markers.size());
}

void DestinationMonitor::markerHit(Marker* pMarker, Tank* pTank)
{
	if (pMarker != _markers.front()) return;

	if (pTank != _pTarget) return;

	pMarker->submitSceneExit();
	_markers.pop();
	if (!_markers.empty())
	{
		_markers.front()->setColorGreen();
	}
	setMarkersLeft(_markers.size());

	_toDelete.push(pMarker);
}

#pragma endregion

#pragma region Setters/Getters

void DestinationMonitor::setTarget(Tank* pTarget)
{
	_pTarget = pTarget;
}

void DestinationMonitor::offsetMarkersLeft(int offset)
{
	setMarkersLeft(_numberOfMarkersLeft + offset);
}

void DestinationMonitor::setMarkersLeft(int numberOfMarkersLeft)
{
	_numberOfMarkersLeft = numberOfMarkersLeft;

	if (_numberOfMarkersLeft <= 0)
	{
		_pGameController->switchToNextScene();
	}

	SpriteFont* pFont = SpriteFontManager::GetSpriteFont("MilitaryGreenFont");
	std::string message = "Markers: " + std::to_string(_numberOfMarkersLeft);
	_pMarkersLeftlCounter->set(pFont, message, 0, 0);
	int positionX = 0, positionY = 0;
	//positionX = Wraith::GetWindowWidth() - _pBuildingLeftCounter->getWidth() - 10;
	positionX = 0;
	positionY = Wraith::GetWindowHeight() - _pMarkersLeftlCounter->getHeight();
	_pMarkersLeftlCounter->setPosition(positionX, positionY);
}

#pragma endregion