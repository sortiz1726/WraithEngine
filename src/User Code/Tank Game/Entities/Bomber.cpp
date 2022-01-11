#include "Bomber.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Tank.h"
#include "BulletFactory.h"
#include "Bullet.h"
#include "vmath.h"
#include "ScreenLog.h"

Bullet* pSOMEBULLET = nullptr;

Bomber::Bomber()
	: _pTarget(nullptr),
	_pTargetGraphicsObject(nullptr),
	_timer(3.0f)
{
	Model* pTargetModel = ModelManager::GetModel("TargetModel");
	ShaderObject* pTextureShader = ShaderManager::GetDefaultShader(ShaderManager::DefaultShader::TEXTURE);
	Texture* pTargetTexture = TextureManager::GetTexture("Red");

	_pTargetGraphicsObject = new GraphicsObject_TextureFlat(pTargetModel, pTextureShader, pTargetTexture);

	Matrix world = Matrix(IDENTITY);
	_pTargetGraphicsObject->SetWorld(world);

	submitUpdateRegistration();
	submitDrawRegistration();
	submitAlarmRegistration(_timer, AlarmID::ALARM_0);
}

Bomber::~Bomber()
{
	delete _pTargetGraphicsObject;
}

void Bomber::setTarget(Tank* pTarget)
{
	_pTarget = pTarget;
}

void Bomber::setTimer(float timer)
{
	_timer = timer;
}

void Bomber::update()
{
	if (pSOMEBULLET != nullptr)
	{
		Vect position = pSOMEBULLET->getBulletPosition();
		//ScreenLog::Add("Bomber_bullet: (%3.1f, %3.1f, %3.1f)", position[x], position[y], position[z]);
	}
	//ScreenLog::Add("Bomber_targetHeatlh: %3.1f", _pTarget->getHealth());
}

void Bomber::draw()
{
	Camera* pCamera = SceneManager::GetCurrentScene()->getCurrentCamera();
	_pTargetGraphicsObject->Render(pCamera);
}

void Bomber::alarm0()
{
	aquirePosition(_pTarget->getTankPosition());
	fire();
	submitAlarmRegistration(_timer, AlarmID::ALARM_0);
}

void Bomber::aquirePosition(const Vect& position)
{
	_targetPosition = position;
	Vect offsetTargetPosition = _targetPosition;
	offsetTargetPosition[y] = 0.0f;
	Matrix translation = Matrix(TRANS, offsetTargetPosition);
	_pTargetGraphicsObject->SetWorld(translation);
}

void Bomber::fire()
{
	Matrix rotateDown = Matrix(ROT_X, vmath::radians(90.f));
	Vect spawnPosition = _targetPosition + Vect(0.0f, 100.0f, 0.0f);
	Bullet* pBullet = BulletFactory::CreateBullet(spawnPosition, rotateDown);
	pBullet->submitSceneEntry();
	pSOMEBULLET = pBullet;

	Vect offset = Vect(4.0f, 0.0f, 0.0f);
	int numberOfBullet = 5;
	Matrix rotate = Matrix(ROT_Y, vmath::radians(360.0f / numberOfBullet));

	for (int i = 0; i < numberOfBullet; i++)
	{
		offset *= rotate;
		pBullet = BulletFactory::CreateBullet(spawnPosition + offset, rotateDown);
		pBullet->submitSceneEntry();
	}
}
