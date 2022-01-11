#include "Marker.h"

#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"

#include "DestinationMonitor.h"
#include "Tank.h"

#include "TimeManager.h"
#include "Visualizer.h"
#include "Colors.h"

Marker::Marker()
	: _pMarkerGraphicsObject_Red(nullptr),
	_pDestinationMonitor(nullptr)
{
	Model* pMarkerModel = ModelManager::GetModel("UnitSphere");
	ShaderObject* pMarkerShader = ShaderManager::GetDefaultShader(ShaderManager::DefaultShader::LIGHTED_TEXTURE);
	Texture* pMarkerTexture = TextureManager::GetTexture("Red");

	Vect lightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect lightPosition(1.0f, 1.0f, 1.0f, 1.0f);

	_pMarkerGraphicsObject_Red = new GraphicsObject_TextureLight(pMarkerModel, pMarkerShader, pMarkerTexture, lightColor, lightPosition);

	pMarkerTexture = TextureManager::GetTexture("Green");
	_pMarkerGraphicsObject_Green = new GraphicsObject_TextureLight(pMarkerModel, pMarkerShader, pMarkerTexture, lightColor, lightPosition);

	_pMarkerGraphicsObject = _pMarkerGraphicsObject_Red;

	setColliderModel(_pMarkerGraphicsObject->getModel(), VolumeType::BSPHERE);
}

Marker::~Marker()
{
	delete _pMarkerGraphicsObject_Red;
	delete _pMarkerGraphicsObject_Green;
}

void Marker::initialize(const Vect& position, float rotation, float uniformScale)
{
	initialize(position, Matrix(RotType::ROT_Y, rotation), uniformScale);
}

void Marker::initialize(const Vect& position, const Matrix& rotation, float uniformScale)
{
	setMarkerPosition(position);
	setMarkerRotation(rotation);
	setMarkerScale(uniformScale);

	updateMarkerWorldMatrix();
}

void Marker::updateMarkerWorldMatrix()
{
	Matrix world = _localScale * _localRotation * Matrix(TRANS, _localPosition);
	_pMarkerGraphicsObject_Red->SetWorld(world);
	_pMarkerGraphicsObject_Green->SetWorld(world);
	updateCollisionData(_pMarkerGraphicsObject->getWorld());
}

#pragma region GameObject Properties

// Draw
void Marker::draw()
{
	Camera* pCamera = SceneManager::GetCurrentScene()->getCurrentCamera();
	_pMarkerGraphicsObject->Render(pCamera);
}

void Marker::collision(Tank* pTank)
{
	if (_pDestinationMonitor != nullptr)
	{
		_pDestinationMonitor->markerHit(this, pTank);
	}
}

// Scene Entry and Exit
void Marker::sceneExit()
{
	submitUpdateDeregistration();
	submitDrawDeregistration();
	submitCollisionDeregistration();
}

void Marker::sceneEntry()
{
	submitUpdateRegistration();
	submitDrawRegistration();

	setCollidableGroup<Marker>();
	submitCollisionRegistration();
}

#pragma endregion

#pragma region Setters/Getters

// Marker Properties
void Marker::setDestinationMonitor(DestinationMonitor* pDestinationMonitor)
{
	_pDestinationMonitor = pDestinationMonitor;
}

// World Properties
void Marker::setMarkerPosition(const Vect& position)
{
	_localPosition = position;
}

Vect Marker::getMarkerPosition() const
{
	return _localPosition;
}

void Marker::setMarkerRotation(float rotation)
{
	_localRotation.set(ROT_AXIS_ANGLE, Vect(0.0f, 1.0f, 0.0f), rotation);
}

void Marker::setMarkerRotation(const Matrix& rotation)
{
	_localRotation = rotation;
}

void Marker::setColorGreen()
{
	_pMarkerGraphicsObject = _pMarkerGraphicsObject_Green;
	updateMarkerWorldMatrix();
}

void Marker::setColorRed()
{
	_pMarkerGraphicsObject = _pMarkerGraphicsObject_Red;
	updateMarkerWorldMatrix();
}

void Marker::setMarkerScale(float scale)
{
	_localScale.set(SCALE, Vect(scale, scale, scale) * 1.0f);
}

#pragma endregion