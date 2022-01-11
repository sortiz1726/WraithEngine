#include "TesterObject.h"

#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "SpriteFontManager.h"

#include "SceneManager.h"
#include "TimeManager.h"
#include "Wraith.h"

#include "Sprite.h"

#include "vmath.h"
#include "Octree.h"

#include "Visualizer.h"
#include "Colors.h"

Matrix gworld;

#pragma region De/Initialization

TesterObject::TesterObject()
{
	//initializeTestSprites();

	Model* pModel = ModelManager::GetModel("TargetModel");
	ShaderObject* pShader = ShaderManager::GetDefaultShader(ShaderManager::DefaultShader::TEXTURE);
	Texture* pTexture = TextureManager::GetTexture("Red");

	GraphicsObject* pGraphicsObject = nullptr;
	pGraphicsObject = new GraphicsObject_TextureFlat(pModel, pShader, pTexture);
	_graphicsObjects.push_back(pGraphicsObject);
	
	gworld = Matrix(SCALE, Vect(1.0f, 1.0f, 1.0f) * 2.0f) * Matrix(ROT_X, vmath::radians(90.0f)) * Matrix(TRANS, Vect(0.0f, 10.0f, 0.0f));

	pGraphicsObject->SetWorld(gworld);
	Collidable::setColliderModel(pModel, VolumeHierarchyType::OCTREE, 1);
	Collidable::updateCollisionData(gworld);

	submitUpdateRegistration();
	submitDrawRegistration();
	submitDraw2DRegistration();
	submitKeyRegistration(AZUL_KEY::KEY_0, InputEvent::KEY_PRESS);
	submitKeyRegistration(AZUL_KEY::KEY_9, InputEvent::KEY_PRESS);
	//submitKeyRegistration(AZUL_KEY::KEY_7, InputEvent::KEY_PRESS);
	//submitKeyRegistration(AZUL_KEY::KEY_8, InputEvent::KEY_PRESS);
}

void TesterObject::initializeTestModels()
{
	Model* pModel = nullptr;
	ShaderObject* pShader = nullptr;
	Texture* pTexture = nullptr;
	GraphicsObject_TextureFlat* pGraphicsObject = nullptr;
	Matrix world = Matrix(IDENTITY);
	Vect position = Vect(0.0f, 0.0f, 0.0f);
	float xOffset = 25.0f;

	// WindMill
	position.set(0.0f * xOffset, 0.0f, 0.0f);

	pModel = ModelManager::GetModel("WindMill");
	pShader = ShaderManager::GetDefaultShader(ShaderManager::DefaultShader::TEXTURE);
	pTexture = TextureManager::GetTexture("WindMillTexture");

	pGraphicsObject = new GraphicsObject_TextureFlat(pModel, pShader, pTexture);

	world = Matrix(SCALE, Vect(1.0f, 1.0f, 1.0f) * 0.7f) * Matrix(TRANS, position);
	pGraphicsObject->SetWorld(world);

	_graphicsObjects.push_back(pGraphicsObject);

	// Cottage 1
	position.set(1.0f * xOffset, 0.0f, 0.0f);

	pModel = ModelManager::GetModel("Cottage1");
	pShader = ShaderManager::GetDefaultShader(ShaderManager::DefaultShader::TEXTURE);
	pTexture = TextureManager::GetTexture("Cottage1Texture");

	pGraphicsObject = new GraphicsObject_TextureFlat(pModel, pShader, pTexture);

	world = Matrix(SCALE, Vect(1.0f, 1.0f, 1.0f) * 0.5f) * Matrix(TRANS, position);
	pGraphicsObject->SetWorld(world);

	_graphicsObjects.push_back(pGraphicsObject);

	// Campfire
	position.set(2.0f * xOffset, 0.0f, 0.0f);

	pModel = ModelManager::GetModel("Campfire");
	pShader = ShaderManager::GetDefaultShader(ShaderManager::DefaultShader::TEXTURE);
	pTexture = TextureManager::GetTexture("StickTexture");

	pGraphicsObject = new GraphicsObject_TextureFlat(pModel, pShader, pTexture, TextureManager::GetTexture("StoneTexture"));

	world = Matrix(SCALE, Vect(1.0f, 1.0f, 1.0f) * 0.5f) * Matrix(TRANS, position);
	pGraphicsObject->SetWorld(world);

	_graphicsObjects.push_back(pGraphicsObject);

	// Tree
	position.set(3.0f * xOffset, 0.0f, 0.0f);

	pModel = ModelManager::GetModel("Tree");
	pShader = ShaderManager::GetDefaultShader(ShaderManager::DefaultShader::TEXTURE);
	pTexture = TextureManager::GetTexture("TreeTexture");

	pGraphicsObject = new GraphicsObject_TextureFlat(pModel, pShader, pTexture);

	world = Matrix(SCALE, Vect(1.0f, 1.0f, 1.0f) * 0.5f) * Matrix(TRANS, position);
	pGraphicsObject->SetWorld(world);

	_graphicsObjects.push_back(pGraphicsObject);
}

void TesterObject::initializeTestSprites()
{
	Sprite* pSpriteGrid = createSprite("GridImage");
	pSpriteGrid->setCenter(-pSpriteGrid->getWidth() / 2.0f, -pSpriteGrid->getHeight() / 2.0f);

	_pSpriteSquare = createSprite("ColorCornerSquareImage");
	_pSpriteSquare->setPosition(Wraith::GetWindowWidth() / 2.0f, Wraith::GetWindowHeight() / 2.0f);
	_pSpriteSquare->setScalePixel(100.0f, 100.0f);
	_pSpriteSquare->setCenter(_pSpriteSquare->getWidth() / 2.0f, _pSpriteSquare->getHeight() / 2.0f);

	Sprite* pSpriteSquare = createSprite("ColorCornerSquareImage");
	pSpriteSquare->setPosition(Wraith::GetWindowWidth() / 2.0f, Wraith::GetWindowHeight() / 2.0f);
	//pSpriteSquare->setCenter(pSpriteSquare->getWidth() / 2.0f, pSpriteSquare->getHeight() / 2.0f);
}

Sprite* TesterObject::createSprite(const std::string& imageKey)
{
	Sprite* pSprite = new Sprite(imageKey);
	_sprites.push_back(pSprite);
	return pSprite;
}

TesterObject::~TesterObject()
{
	for (auto pGraphicsObject : _graphicsObjects)
	{
		delete pGraphicsObject;
	}

	for (auto& pSprite : _sprites)
	{
		delete pSprite;
	}

}

#pragma endregion

void TesterObject::update()
{
	Visualizer::ShowCollisionVolume(getCollisionVolume());
}

#pragma region Draw

void TesterObject::draw()
{
	//Camera* pCamera = SceneManager::GetCurrentScene()->getCurrentCamera();
	drawModels();
	//pOctree->render(pCamera, depth);
}

void TesterObject::drawModels()
{
	Camera* pCamera = SceneManager::GetCurrentScene()->getCurrentCamera();
	for (auto pGraphicsObject : _graphicsObjects)
	{
		pGraphicsObject->Render(pCamera);
	}
}

void TesterObject::draw2D()
{
	drawSprites();
}

void TesterObject::drawSprites()
{
	for (auto& pSprite : _sprites)
	{
		pSprite->render();
	}
}

#pragma endregion

void TesterObject::keyPressed(AZUL_KEY key)
{
	key;
}
