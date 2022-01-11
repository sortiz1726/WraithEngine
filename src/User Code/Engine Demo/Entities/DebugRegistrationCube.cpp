#include "DebugRegistrationCube.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "TimeManager.h"

DebugRegistrationCube::DebugRegistrationCube()
	: _pGraphicsObject_Cube(nullptr),
	_name("defaultName"),
	_startPosition(Vect(0, 0, 0))
{
	//-----------------------------------------------------------------------------------------------------------------------------
	// Cube
	//-----------------------------------------------------------------------------------------------------------------------------
	initializeGraphicObjectCube("Grey");
	_cubeScale.set(SCALE, _scale, _scale, _scale);
	_cubeRotation.set(IDENTITY);
	setPosition(_startPosition);
	updateWorldMatrix();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Register to Current Scene
	//-----------------------------------------------------------------------------------------------------------------------------
	setCanDraw(true);

	Trace::out("DebugRegistrationCube: "); setCollidableGroup<DebugRegistrationCube>();
}

DebugRegistrationCube::DebugRegistrationCube(const Vect& startPosition)
	: DebugRegistrationCube()
{
	setPosition(startPosition);
	updateWorldMatrix();
}

DebugRegistrationCube::DebugRegistrationCube(const std::string& name, const std::string& colorTextureName, const Vect& startPosition, const Vect& moveDirection)
	: _name(name),
	_startPosition(startPosition),
	_moveDirection(moveDirection)
{
	//-----------------------------------------------------------------------------------------------------------------------------
	// Cube
	//-----------------------------------------------------------------------------------------------------------------------------
	initializeGraphicObjectCube(colorTextureName);
	_cubeScale.set(SCALE, _scale, _scale, _scale);
	_cubeRotation.set(IDENTITY);
	updateWorldMatrix();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Register to Current Scene
	//-----------------------------------------------------------------------------------------------------------------------------
	setCollidableGroup<DebugRegistrationCube>();
	setCanUpdate(true);
	setCanDraw(true);
	setCanCollide(true);

	submitAlarmRegistration(_updateToggleAlarmTime, AlarmID::ALARM_0);
	submitAlarmRegistration(_drawToggleAlarmTime, AlarmID::ALARM_1);
	submitAlarmRegistration(_resetPositionAlarmTime, AlarmID::ALARM_2);

	submitKeyRegistration(AZUL_KEY::KEY_A, InputEvent::KEY_PRESS);
	submitKeyRegistration(AZUL_KEY::KEY_D, InputEvent::KEY_RELEASE);
	submitKeyRegistration(AZUL_KEY::KEY_RIGHT_SHIFT, InputEvent::KEY_PRESS);

	setColliderModel(_pGraphicsObject_Cube->getModel(), VolumeType::BSPHERE);
}

DebugRegistrationCube::~DebugRegistrationCube()
{
	//Trace::out("\n-----------------------------------------\n");
	//Trace::out("DebugRegistrationCube: Destructor Called\n");
	delete _pGraphicsObject_Cube;
}

void DebugRegistrationCube::initializeGraphicObjectCube(const std::string& colorTextureName)
{
	// Load Assets
	Model* pCubeModel = ModelManager::GetModel("UnitCube");
	ShaderObject* pLightedTextureShader = ShaderManager::GetDefaultShader(ShaderManager::DefaultShader::LIGHTED_TEXTURE);
	Texture* pCubeTexture = TextureManager::GetTexture(colorTextureName);

	// Set Up Lights
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);

	// Create Graphics Object
	_pGraphicsObject_Cube = new GraphicsObject_TextureLight(pCubeModel, pLightedTextureShader, pCubeTexture, LightColor, LightPos);
}

void DebugRegistrationCube::setPosition(const Vect& position)
{
	_cubePosition.set(position);
}


//-----------------------------------------------------------------------------------------------------------------------------
// Update
//-----------------------------------------------------------------------------------------------------------------------------
void DebugRegistrationCube::update()
{
	updateDebugRegistrationCube();
	updateCollisionData(_pGraphicsObject_Cube->getWorld());
}

void DebugRegistrationCube::updateDebugRegistrationCube()
{
	moveCube(_moveDirection);
	rotateCube(_cubeRotationSpeed);
	updateWorldMatrix();
}

void DebugRegistrationCube::moveCube(const Vect& moveDirection)
{
	_cubePosition += moveDirection * _cubeTransSpeed * TimeManager::GetElaspedFrameTimeInSeconds();
}

void DebugRegistrationCube::rotateCube(float rotationOffset)
{
	_cubeRotation *= Matrix(ROT_Y, rotationOffset);
}

void DebugRegistrationCube::updateWorldMatrix()
{
	Matrix world = _cubeScale * _cubeRotation * Matrix(TRANS, _cubePosition);
	_pGraphicsObject_Cube->SetWorld(world);
}

//-----------------------------------------------------------------------------------------------------------------------------
// Draw
//-----------------------------------------------------------------------------------------------------------------------------
void DebugRegistrationCube::draw()
{
	Camera* pCamera = SceneManager::GetCurrentScene()->getCurrentCamera();
	_pGraphicsObject_Cube->Render(pCamera);
}

//-----------------------------------------------------------------------------------------------------------------------------
// Alarm
//-----------------------------------------------------------------------------------------------------------------------------
void DebugRegistrationCube::alarm0()
{
	float timeDelay = _updateToggleAlarmTime;
	//Trace::out("DebugRegistrationCube: (%s) Alarm0 triggered, will trigger again in %f\n", _name.c_str(), timeDelay);
	toggleUpdate();
	submitAlarmRegistration(timeDelay, AlarmID::ALARM_0);
}

void DebugRegistrationCube::toggleUpdate()
{
	setCanUpdate(!_canUpdate);
}

void DebugRegistrationCube::setCanUpdate(bool canUpdate)
{
	_canUpdate = canUpdate;
	if (_canUpdate)
	{
		//Trace::out("DebugRegistrationCube: (%s) Register Update\n", _name.c_str());
		submitUpdateRegistration();
	}
	else
	{
		//Trace::out("DebugRegistrationCube: (%s) Deregister Update\n", _name.c_str());
		submitUpdateDeregistration();
	}
}

void DebugRegistrationCube::alarm1()
{
	float timeDelay = _drawToggleAlarmTime;
	//Trace::out("DebugRegistrationCube: (%s) Alarm1 triggered, will trigger again in %f\n", _name.c_str(), timeDelay);
	toggleDraw();
	submitAlarmRegistration(timeDelay, AlarmID::ALARM_1);
}

void DebugRegistrationCube::toggleDraw()
{
	setCanDraw(!_canDraw);
}

void DebugRegistrationCube::setCanDraw(bool canDraw)
{
	_canDraw = canDraw;
	if (_canDraw)
	{
		//Trace::out("DebugRegistrationCube: (%s) deregister Update\n", _name.c_str());
		submitDrawRegistration();
	}
	else
	{
		//Trace::out("DebugRegistrationCube: (%s) register Update\n", _name.c_str());
		submitDrawDeregistration();
	}
}

void DebugRegistrationCube::alarm2()
{
	float timeDelay = _resetPositionAlarmTime;
	//Trace::out("DebugRegistrationCube: (%s) Alarm2 triggered, will trigger again in %f\n", _name.c_str(), timeDelay);
	setPosition(_startPosition);
	submitAlarmRegistration(timeDelay, AlarmID::ALARM_2);
}

//-----------------------------------------------------------------------------------------------------------------------------
// Keyboard Input
//-----------------------------------------------------------------------------------------------------------------------------
void DebugRegistrationCube::keyPressed(AZUL_KEY key)
{
	switch (key)
	{
	case AZUL_KEY::KEY_RIGHT_SHIFT:
		toggleCollision();
		break;
	case AZUL_KEY::KEY_A:
		//Trace::out("DebugRegistrationCube: A pressed\n");
		break;
	case AZUL_KEY::KEY_D:
		//Trace::out("DebugRegistrationCube: D pressed SHOULD NOT HAPPEN!\n");
		assert(false);
		break;
	default:
		//Trace::out("DebugRegistrationCube: Some other key was released SHOULD NOT HAPPEN!\n");
		assert(false);
		break;
	}
}

void DebugRegistrationCube::toggleCollision()
{
	setCanCollide(!_canCollide);
}

void DebugRegistrationCube::setCanCollide(bool canCollide)
{
	_canCollide = canCollide;

	if (_canCollide)
	{
		Trace::out("DebugRegistrationCube: (%s) register collision\n", _name.c_str());
		submitCollisionRegistration();
	}
	else
	{
		Trace::out("DebugRegistrationCube: (%s) deregister collision\n", _name.c_str());
		submitCollisionDeregistration();
	}
}

const std::string& DebugRegistrationCube::getName() const
{
	return _name;
}

void DebugRegistrationCube::keyReleased(AZUL_KEY key)
{
	switch (key)
	{
	case AZUL_KEY::KEY_D:
		//Trace::out("DebugRegistrationCube: D release\n");
		break;
	case AZUL_KEY::KEY_A:
		//Trace::out("DebugRegistrationCube: A release SHOULD NOT HAPPEN!\n");
		assert(false);
		break;
	default:
		//Trace::out("DebugRegistrationCube: Some other key was released SHOULD NOT HAPPEN!\n");
		assert(false);
		break;
	}
}

void DebugRegistrationCube::collision(DebugRegistrationCube* pCube)
{
	assert(pCube != this);
	Trace::out("DebugRegistrationCube_collision(DebugCube): (%s) collided with (%s)\n", getName().c_str(), pCube->getName().c_str());
}

void DebugRegistrationCube::printCurrentTime() const
{
	Trace::out("DebugRegistrationCube: (%s) current time %f\n", _name.c_str(), TimeManager::GetTimeInSeconds());
}