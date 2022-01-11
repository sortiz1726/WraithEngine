#include "CollisionTestObject.h"
#include "CollisionVolumeOBB.h"
#include "CollisionVolumeOctree.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "SceneManager.h"
#include "Visualizer.h"
#include "Colors.h"
#include "TimeManager.h"
#include "MathTools.h"
#include "Triangle.h"
#include "vmath.h"


// global variables just for testin, just used to testing
CollisionVolumeOctree* pGlobalOctree;

int maxDepthDEBUG = 5;
int currentDepthDEBUG = 0;
float scaleDebug = 1.0f;

CollisionTestObject::CollisionTestObject()
	: _pOBB(nullptr)
{
	_world = Matrix(SCALE, Vect(1.0f, 1.0f, 1.0f) * 5.0f);


	pGlobalOctree = new CollisionVolumeOctree(ModelManager::GetModel("Tree"), maxDepthDEBUG);

	Vect lightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect lightPosition(1.0f, 1.0f, 1.0f, 1.0f);

	Model* pLeaflessTreeModel = ModelManager::GetModel("Tree");
	ShaderObject* pLeaflessTreeShader = ShaderManager::GetDefaultShader(ShaderManager::DefaultShader::LIGHTED_TEXTURE);
	Texture* pLeaflessTreeTexture = TextureManager::GetTexture("TreeTexture");

	_pLeaflessTreeGraphicsObject = new GraphicsObject_TextureLight(pLeaflessTreeModel, pLeaflessTreeShader, pLeaflessTreeTexture, lightColor, lightPosition);
	
	submitUpdateRegistration();
	submitDrawRegistration();
	submitKeyRegistration(AZUL_KEY::KEY_1, InputEvent::KEY_PRESS);
	submitKeyRegistration(AZUL_KEY::KEY_2, InputEvent::KEY_PRESS);
}

CollisionTestObject::~CollisionTestObject()
{
	delete _pOBB;
	delete pGlobalOctree;
	delete _pLeaflessTreeGraphicsObject;
}

void CollisionTestObject::update()
{
	checkKeyboardInput();
	_pLeaflessTreeGraphicsObject->SetWorld(_world);
	pGlobalOctree->computeData(_pLeaflessTreeGraphicsObject->getModel(), _pLeaflessTreeGraphicsObject->getWorld());
	
	pGlobalOctree->debugDraw(currentDepthDEBUG, Colors::Blue);
}

void CollisionTestObject::draw()
{
	Camera* pCamera = SceneManager::GetCurrentScene()->getCurrentCamera();

	_pLeaflessTreeGraphicsObject->Render(pCamera);
}

void CollisionTestObject::keyPressed(AZUL_KEY key)
{
	if (key == AZUL_KEY::KEY_1)
	{
		currentDepthDEBUG -= 1;
	}
	if (key == AZUL_KEY::KEY_2)
	{
		currentDepthDEBUG += 1;
	}

	currentDepthDEBUG = MathTools::Clamp(currentDepthDEBUG, 0, maxDepthDEBUG - 1);
}

void CollisionTestObject::checkKeyboardInput()
{
	float deltaTime = TimeManager::GetElaspedFrameTimeInSeconds();
	float speed = 35.0f;

	float xMove = (float)(Keyboard::GetKeyState(AZUL_KEY::KEY_F) - Keyboard::GetKeyState(AZUL_KEY::KEY_H));
	float zMove = (float)(Keyboard::GetKeyState(AZUL_KEY::KEY_T) - Keyboard::GetKeyState(AZUL_KEY::KEY_G));

	Vect moveOffset = Vect(xMove, 0.0f, zMove) * speed * deltaTime;

	float rotSpeed = 35.0f;
	float yRotdir = (float)(Keyboard::GetKeyState(AZUL_KEY::KEY_V) - Keyboard::GetKeyState(AZUL_KEY::KEY_N));
	float yRotOffet = yRotdir * rotSpeed * deltaTime;

	float scaleSpeed = 0.1f;
	float scaleDir = (float)(Keyboard::GetKeyState(AZUL_KEY::KEY_R) - Keyboard::GetKeyState(AZUL_KEY::KEY_Y));

	scaleDebug += scaleDir * scaleSpeed * deltaTime;

	_world *= Matrix(SCALE, Vect(1.0f, 1.0f, 1.0f) * scaleDebug) * Matrix(ROT_Y, vmath::radians(yRotOffet)) * Matrix(TRANS, moveOffset);
}

void CollisionTestObject::drawTriangle(const Triangle& triangle)
{
	Vect lineColor = Colors::AliceBlue;
	Vect pointColor = Colors::Red;

	Visualizer::ShowPointAt(triangle.getVertex0(), pointColor);
	Visualizer::ShowPointAt(triangle.getVertex1(), pointColor);
	Visualizer::ShowPointAt(triangle.getVertex2(), pointColor);

	Visualizer::ShowLineSegment(triangle.getVertex0(), triangle.getVertex1(), lineColor);
	Visualizer::ShowLineSegment(triangle.getVertex1(), triangle.getVertex2(), lineColor);
	Visualizer::ShowLineSegment(triangle.getVertex2(), triangle.getVertex0(), lineColor);
}
