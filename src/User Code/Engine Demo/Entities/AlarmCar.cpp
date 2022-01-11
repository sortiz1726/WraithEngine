#include "AlarmCar.h"

// include Resource Managers header files
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"

// include Scene Manager and Scene header files
#include "SceneManager.h"
#include "Scene.h"

AlarmCar::AlarmCar()
{
	// Get Resources from Managers using user defined keys.
	Model* pAlarmCarModel = ModelManager::GetModel("Car");
	// Shader Manager takes in keys and enums for shaders. (Enums are for preloaded shaders)
	ShaderObject* pAlarmCarShader = ShaderManager::GetDefaultShader(ShaderManager::DefaultShader::TEXTURE);
	Texture* pAlarmCarTexture = TextureManager::GetTexture("CarTexture");

	// Initialize a Graphics Object 
	_pCarGraphicsObject = new GraphicsObject_TextureFlat(pAlarmCarModel, pAlarmCarShader, pAlarmCarTexture);

	// Initialize world matrix.
	Matrix scale = Matrix(SCALE, 1.0f, 1.0f, 1.0f);
	Matrix rotation = Matrix(IDENTITY);
	Matrix translation = Matrix(TRANS, 0.0f, 0.0f, 0.0f);

	Matrix world = scale * rotation * translation;

	_pCarGraphicsObject->SetWorld(world);

	// Submit Registrations
	submitDrawRegistration();

	// set the alarm0 to trigger in 3 seconds
	submitAlarmRegistration(3.0f, AlarmID::ALARM_0);
}

AlarmCar::~AlarmCar()
{
	delete _pCarGraphicsObject;
}

void AlarmCar::draw()
{
	// Get Camera for drawing graphics object
	Camera* pCamera = SceneManager::GetCurrentScene()->getCurrentCamera();

	// Then for every graphics object call render and pass in the camera
	_pCarGraphicsObject->Render(pCamera);
}

void AlarmCar::alarm0()
{
	Trace::out("AlarmCar: Alarm 0 triggered\n");
	// Does something, in this case changes car position
	Matrix translation(TRANS, 5.0f, 0.0f, 0.0f);
	_pCarGraphicsObject->SetWorld(translation);

	// set alarm 1 to trigger in 1 second
	submitAlarmRegistration(1.0f, AlarmID::ALARM_1);
}

void AlarmCar::alarm1()
{
	Trace::out("AlarmCar: Alarm 1 triggered\n");
	// Does something, in this case changes car position
	Matrix translation(TRANS, 0.0f, 0.0f, 5.0f);
	_pCarGraphicsObject->SetWorld(translation);

	// set alarm 2 to trigger in 2 second
	submitAlarmRegistration(2.0f, AlarmID::ALARM_2);
}

void AlarmCar::alarm2()
{
	Trace::out("AlarmCar: Alarm 2 triggered\n");
	// Does something, in this case changes car position
	Matrix translation(TRANS, 0.0f, 0.0f, 0.0f);
	_pCarGraphicsObject->SetWorld(translation);

	// set alarm 0 to trigger in 3 second
	submitAlarmRegistration(3.0f, AlarmID::ALARM_0);
}
