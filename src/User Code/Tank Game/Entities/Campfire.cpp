#include "Campfire.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "SceneManager.h"
#include "vmath.h"

const float Campfire::adjustedScale = 0.5f;

Campfire::Campfire()
	: _pCampfireGraphicsObject(nullptr),
	_localScale(Vect(1.0f, 1.0f, 1.0f)),
	_localRotation(Matrix(IDENTITY)),
	_localPosition(Vect(0.0f, 0.0f, 0.0f))
{
	InitiailizeCampfireGraphicsObject();
}

void Campfire::InitiailizeCampfireGraphicsObject()
{
	Vect lightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect lightPosition(1.0f, 1.0f, 1.0f, 1.0f);

	Model* pCampfireModel = ModelManager::GetModel("Campfire");
	ShaderObject* pCampfireShader = ShaderManager::GetDefaultShader(ShaderManager::DefaultShader::LIGHTED_TEXTURE);
	Texture* pCampfireTexture = TextureManager::GetTexture("StickTexture");

	_pCampfireGraphicsObject = new GraphicsObject_TextureLight(pCampfireModel, pCampfireShader, pCampfireTexture, lightColor, lightPosition);

	//Texture* pBrickWallTexture = TextureManager::GetTexture("BrickWallTexture");
	//Texture* pRoofTexture = TextureManager::GetTexture("RoofTexture");
	//Texture* pCabinTexture = TextureManager::GetTexture("CabinTexture");
	//Texture* pChimmneyTexture = TextureManager::GetTexture("ChimneyTexture");

	//_pCampfireGraphicsObject = new GraphicsObject_TextureLight(pCampfireModel, pCampfireShader, pBrickWallTexture, pRoofTexture, pCabinTexture, pChimmneyTexture, lightColor, lightPosition);
}

Campfire::~Campfire()
{
	delete _pCampfireGraphicsObject;
}

void Campfire::initialize(const Vect& position, float rotationY, float uniformScale)
{
	initialize(position, Vect(0.0f, rotationY, 0.0f), Vect(uniformScale, uniformScale, uniformScale));
}

void Campfire::initialize(const Vect& position, const Vect& rotation, const Vect& scale)
{
	setLocalPosition(position);
	setLocalRotation(rotation);
	setLocalScale(scale);
	
	Matrix world = getLocalScaleMatrix() * getLocalRotationMatrix() * getLocalPositionMatrix();
	_pCampfireGraphicsObject->SetWorld(world);

	submitDrawRegistration();
}

void Campfire::draw()
{
	Camera* pCamera = SceneManager::GetCurrentScene()->getCurrentCamera();
	_pCampfireGraphicsObject->Render(pCamera);
}

#pragma region MyRegion

// --> Scale
void Campfire::setLocalScale(const Vect& localScale)
{
	_localScale.set(localScale);
}

Vect Campfire::getLocalScale() const
{
	return _localScale;
}

Matrix Campfire::getLocalScaleMatrix() const
{
	return Matrix(SCALE, _localScale * Campfire::adjustedScale);
}

// --> Rotation
void Campfire::setLocalRotation(const Vect& localRotation)
{
	_localRotation.set(ROT_Y, vmath::radians(localRotation.Y()));
}

Matrix Campfire::getLocalRotationMatrix() const
{
	return _localRotation;
	//return Matrix(Rot3AxisType::ROT_XYZ, vmath::radians(_localRotation.X()), vmath::radians(_localRotation.Y()), vmath::radians(_localRotation.Z()));
}

// --> Position
void Campfire::setLocalPosition(const Vect& localPosition)
{
	_localPosition.set(localPosition);
}

Vect Campfire::getLocalPosition() const
{
	return _localPosition;
}

Matrix Campfire::getLocalPositionMatrix() const
{
	return Matrix(TRANS, _localPosition);
}
#pragma endregion
