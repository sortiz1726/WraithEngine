#include "Visualizer.h"
#include "Colors.h"

#include "ModelManager.h"
#include "ShaderManager.h"
#include "SceneManager.h"
#include "Scene.h"

#include "CollisionVolumeAttorney.h"
#include "CollisionVolumeBSphere.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeOBB.h"

#include "RenderBSphereCommandPool.h"
#include "RenderBSphereCommand.h"
#include "RenderAABBCommandPool.h"
#include "RenderAABBCommand.h"
#include "RenderOBBCommandPool.h"
#include "RenderOBBCommand.h"
#include "RenderPointCommandPool.h"
#include "RenderPointCommand.h"
#include "RenderLineSegmentCommandPool.h"
#include "RenderLineSegmentCommand.h"

#include "MathTools.h"

Visualizer* Visualizer::pVisualzierInstance = nullptr;
Vect Visualizer::DEFAULT_COLOR = Colors::Blue;

Visualizer& Visualizer::GetInstance()
{
	if (Visualizer::pVisualzierInstance == nullptr)
	{
		Visualizer::pVisualzierInstance = new Visualizer();
	}
	assert(Visualizer::pVisualzierInstance != nullptr);
	return *Visualizer::pVisualzierInstance;
}

Visualizer::Visualizer()
	: _pSphereGraphicsObject(nullptr),
	_pCubeGraphicsObject(nullptr)
{
	ShaderObject* pShader = ShaderManager::GetDefaultShader(ShaderManager::DefaultShader::CONSTANT_COLOR);
	Model* pSphereModel = ModelManager::GetModel("UnitSphere");
	Model* pBoxModel = ModelManager::GetModel("UnitCube");
	
	_pSphereGraphicsObject = new GraphicsObject_WireframeConstantColor(pSphereModel, pShader, Visualizer::DEFAULT_COLOR);
	_pCubeGraphicsObject = new GraphicsObject_WireframeConstantColor(pBoxModel, pShader, Visualizer::DEFAULT_COLOR);
}

//-----------------------------------------------------------------------------------------------------------------------------
// Show Volume
//-----------------------------------------------------------------------------------------------------------------------------
void Visualizer::privShowCollisionVolume(const CollisionVolume& collisionVolume, const Vect& color, int depth)
{
	assert(depth == 0 || (depth > 0 && depth <= collisionVolume.getMaxDepth()));
	CollisionVolumeAttorney::DebugDrawAccess::DebugDraw(collisionVolume, color, depth);
}

void Visualizer::privShowBSphere(const CollisionVolumeBSphere& BSphere, const Vect& color)
{
	Matrix world = Matrix(IDENTITY);
	Vect uniformScale = Vect(1.0f, 1.0f, 1.0f) * BSphere.getRadius();
	world *= Matrix(SCALE, uniformScale);
	world *= Matrix(TRANS, BSphere.getCenter());

	RenderBSphereCommand* pRenderBSphereCommand = RenderBSphereCommandPool::GetCommand();

	pRenderBSphereCommand->setWorld(world);
	pRenderBSphereCommand->setColor(color);

	_renderCommands.push_back(pRenderBSphereCommand);
}

void Visualizer::privShowAABB(const CollisionVolumeAABB& AABB, const Vect& color)
{
	Matrix world = Matrix(IDENTITY);
	world *= Matrix(SCALE, AABB.getMaxWorldVertex() - AABB.getMinWorldVertex());
	world *= Matrix(TRANS, (AABB.getMaxWorldVertex() + AABB.getMinWorldVertex()) * 0.5f);

	RenderAABBCommand* pRenderAABBCommand = RenderAABBCommandPool::GetCommand();

	pRenderAABBCommand->setWorld(world);
	pRenderAABBCommand->setColor(color);

	_renderCommands.push_back(pRenderAABBCommand);
}

void Visualizer::privShowOBB(const CollisionVolumeOBB& OBB, const Vect& color)
{
	Matrix world = Matrix(IDENTITY);
	world *= Matrix(SCALE, OBB.getMaxLocalVertex() - OBB.getMinLocalVertex());
	world *= Matrix(TRANS, (OBB.getMaxLocalVertex() + OBB.getMinLocalVertex()) * 0.5f );
	world *= OBB.getWorldMatrix();

	RenderOBBCommand* pRenderOBBCommand = RenderOBBCommandPool::GetCommand();

	pRenderOBBCommand->setWorld(world);
	pRenderOBBCommand->setColor(color);

	_renderCommands.push_back(pRenderOBBCommand);
}

void Visualizer::privShowRay(const Vect& start, const Vect& direction, const Vect& color)
{
	privShowPointAt(start, color);
	privShowLineSegment(start, start + direction, color);
}

void Visualizer::privShowPointAt(const Vect& position, const Vect& color)
{
	Matrix world = Matrix(IDENTITY);
	Vect uniformScale = Vect(1.0f, 1.0f, 1.0f) * 0.5f;
	world *= Matrix(SCALE, uniformScale);
	world *= Matrix(TRANS, position);

	RenderPointCommand* pRenderPointCommand = RenderPointCommandPool::GetCommand();

	pRenderPointCommand->setWorld(world);
	pRenderPointCommand->setColor(color);

	_renderCommands.push_back(pRenderPointCommand);
}

void Visualizer::privShowLineSegment(const Vect& position_1, const Vect& position_2, const Vect& color)
{
	Matrix world = Matrix(IDENTITY);
	
	float sqaureDimension = 0.1f;
	float length = (position_2 - position_1).mag();
	Vect scale = Vect(length, sqaureDimension, sqaureDimension);
	world *= Matrix(SCALE, scale);
	
	Vect center = (position_1 + position_2) * 0.5f;
	Vect target = position_2 - center;
	Vect current = Vect(1.0f, 0.0f, 0.0f);
	
	world *= MathTools::RotationFromTowards(current, target);

	Vect translation = (position_2 + position_1) * 0.5f;
	world *= Matrix(TRANS, translation);

	RenderLineSegmentCommand* pRenderLineSegmentCommand = RenderLineSegmentCommandPool::GetCommand();

	pRenderLineSegmentCommand->setWorld(world);
	pRenderLineSegmentCommand->setColor(color);

	_renderCommands.push_back(pRenderLineSegmentCommand);
}

//-----------------------------------------------------------------------------------------------------------------------------
// VRender Visaulization
//-----------------------------------------------------------------------------------------------------------------------------
void Visualizer::privVisualizeAll()
{
	for (RenderCommand* pRenderCommand : _renderCommands)
	{
		pRenderCommand->execute();
	}
	_renderCommands.clear();
}

void Visualizer::renderBSphere(Matrix& world, const Vect& color)
{
	_pSphereGraphicsObject->SetWorld(world);
	_pSphereGraphicsObject->SetColor(color);

	Camera* pCamera = SceneManager::GetCurrentScene()->getCurrentCamera();
	_pSphereGraphicsObject->Render(pCamera);
}

void Visualizer::renderAABB(Matrix& world, const Vect& color)
{
	_pCubeGraphicsObject->SetWorld(world);
	_pCubeGraphicsObject->SetColor(color);

	Camera* pCamera = SceneManager::GetCurrentScene()->getCurrentCamera();
	_pCubeGraphicsObject->Render(pCamera);
}

void Visualizer::renderOBB(Matrix& world, const Vect& color)
{
	_pCubeGraphicsObject->SetWorld(world);
	_pCubeGraphicsObject->SetColor(color);

	Camera* pCamera = SceneManager::GetCurrentScene()->getCurrentCamera();
	_pCubeGraphicsObject->Render(pCamera);
}

void Visualizer::renderPoint(Matrix& world, const Vect& color)
{
	_pCubeGraphicsObject->SetWorld(world);
	_pCubeGraphicsObject->SetColor(color);

	Camera* pCamera = SceneManager::GetCurrentScene()->getCurrentCamera();
	_pCubeGraphicsObject->Render(pCamera);
}

void Visualizer::renderLineSegment(Matrix& world, const Vect& color)
{
	_pCubeGraphicsObject->SetWorld(world);
	_pCubeGraphicsObject->SetColor(color);

	Camera* pCamera = SceneManager::GetCurrentScene()->getCurrentCamera();
	_pCubeGraphicsObject->Render(pCamera);
}

//-----------------------------------------------------------------------------------------------------------------------------
// Termination
//-----------------------------------------------------------------------------------------------------------------------------
void Visualizer::Delete()
{
	delete Visualizer::pVisualzierInstance;
	Visualizer::pVisualzierInstance = nullptr;
}

Visualizer::~Visualizer()
{
	delete _pSphereGraphicsObject;
	delete _pCubeGraphicsObject;
	_renderCommands.clear();
}