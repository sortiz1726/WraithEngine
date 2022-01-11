#include "Sprite.h"

#include "ModelManager.h"
#include "ShaderManager.h"
#include "ImageManager.h"
#include "SceneManager.h"

#include "SpriteStrategyCollection.h"

#include "Scene.h"
#include "GraphicsObject_Sprite.h"
#include "Rect.h"

#include "MathTools.h"

Sprite::Sprite(const std::string& imageKey)
	: _positionX(0.0f), _positionY(0.0f),
	_centerX(0.0f), _centerY(0.0f),
	_angle(0.0f),
	_scaleX(1.0f), _scaleY(1.0f),
	_width(0.0f), _height(0.0f),
	_pSpriteGraphicsObject(nullptr),
	_pPropertyModifierStrategy(&SpriteStrategyCollection::nullModifier)
{
	Model* pModel = ModelManager::GetDefaultModel(ModelManager::DefaultModel::SPRITE);
	ShaderObject* pShader = ShaderManager::GetDefaultShader(ShaderManager::DefaultShader::SPRITE);
	Image* pImage = ImageManager::GetImage(imageKey);
	
	float textureWidth = static_cast<float>(pImage->pText->getWidth());
	float textureHeight = static_cast<float>(pImage->pText->getHeight());

	Rect* pRectangle = new Rect(0.0f, 0.0f, textureWidth, textureHeight);
	_pSpriteGraphicsObject = new GraphicsObject_Sprite(pModel, pShader, pImage, pRectangle);
	delete pRectangle;

	setScalePixel(textureWidth, textureHeight);
}

Sprite::~Sprite()
{
	delete _pSpriteGraphicsObject;
}

void Sprite::render()
{
	_pPropertyModifierStrategy->modify(this);

	Camera* pCamera = SceneManager::GetCurrentScene()->getCurrent2DCamera();
	_pSpriteGraphicsObject->Render(pCamera);
	
	setToNullModifier();
}

//-----------------------------------------------------------------------------------------------------------------------------
// Setter/Getter
//-----------------------------------------------------------------------------------------------------------------------------
void Sprite::setPosition(float positionX, float positionY)
{
	_positionX = positionX;
	_positionY = positionY;

	setToUpdateWorld();
}

float Sprite::getPositionX() const
{
	return _positionX;
}

float Sprite::getPositionY() const
{
	return _positionY;
}

void Sprite::setCenter(float centerX, float centerY)
{
	_centerX = centerX;
	_centerY = centerY;

	setToUpdateWorld();
}

void Sprite::setAngle(float angle)
{
	_angle = angle;
	
	setToUpdateWorld();
}

float Sprite::getAngle() const
{
	return _angle;
}

void Sprite::offsetAngle(float angleOffset)
{
	setAngle(getAngle() + angleOffset);
}

void Sprite::setScaleFactor(float scaleX, float scaleY)
{
	_scaleX = scaleX;
	_scaleY = scaleY;

	setToUpdateWorld();
}

void Sprite::setScalePixel(float width, float height)
{
	_width = width;
	_height = height;

	setToUpdateWorld();
}

float Sprite::getWidth() const
{
	return _width * _scaleX;
}

float Sprite::getHeight() const
{
	return _height * _scaleY;
}

// ---> Setter/Getter helpers
void Sprite::setToUpdateWorld()
{
	_pPropertyModifierStrategy = &SpriteStrategyCollection::worldModifier;
}

void Sprite::setToNullModifier()
{
	_pPropertyModifierStrategy = &SpriteStrategyCollection::nullModifier;
}

void Sprite::updateWorld()
{
	//Matrix world = getScaleMatrix() * getScalePixelMatrix() * getCenterMatrix() * getRotationMatrix() * getPositionMatrix();
	//Vect centerOffset = Vect(-_centerX, -_centerY, 0.0f) * (getScaleMatrix() * getScalePixelMatrix()).getInv();
	//Matrix world = Matrix(TRANS, centerOffset) * getScaleMatrix() * getScalePixelMatrix() * getRotationMatrix() * getPositionMatrix();
	
	Matrix world = getScaleMatrix() * getScalePixelMatrix() * getCenterMatrix() * getRotationMatrix() * getPositionMatrix();
	_pSpriteGraphicsObject->SetWorld(world);
}

Matrix Sprite::getScaleMatrix() const
{
	return Matrix(SCALE, _scaleX, _scaleY, 1.0f);
}

Matrix Sprite::getScalePixelMatrix() const
{
	float adjustedWidthScale = _width / _pSpriteGraphicsObject->origWidth;
	float adjustedheightScale = _height / _pSpriteGraphicsObject->origHeight;

	Matrix scalePixelMatrix(SCALE, adjustedWidthScale, adjustedheightScale, 1.0f);

	return scalePixelMatrix;
}

Matrix Sprite::getCenterMatrix() const
{
	return Matrix(TRANS, -_centerX, -_centerY, 0.0f);
}

Matrix Sprite::getRotationMatrix() const
{
	return Matrix(ROT_Z, _angle);
}

Matrix Sprite::getPositionMatrix() const
{
	return Matrix(TRANS, _positionX, _positionY, -100.0f);
}