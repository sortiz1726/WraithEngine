#include "Octree.h"
#include <cassert>
#include "MathTools.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "Colors.h"

Octree::Octree()
	: _pBoxGraphicsObject(nullptr)
{
	ShaderObject* pShader = ShaderManager::GetDefaultShader(ShaderManager::DefaultShader::CONSTANT_COLOR);
	Model* pBoxModel = ModelManager::GetModel("UnitCube");
	Vect color = Colors::Red;
	_pBoxGraphicsObject = new GraphicsObject_WireframeConstantColor(pBoxModel, pShader, color);

	for (auto& pOctree : _octrees)
	{
		pOctree = nullptr;
	}
}

Octree::~Octree()
{
	delete _pBoxGraphicsObject;
	for (Octree* pOctree : _octrees)
	{
		delete pOctree;
	}
}

Octree::Octree(Model* pModel, const Matrix& worldMatrix)
	: Octree::Octree()
{
	_pColliderModel = pModel;
	_originalWorld = worldMatrix;

	// Create Box Graphics Object for Rendering
	Vect scale = _pColliderModel->getMaxAABB() - _pColliderModel->getMinAABB();
	Vect center = (_pColliderModel->getMaxAABB() + _pColliderModel->getMinAABB()) * 0.5f;
	Matrix world = _originalWorld * Matrix(SCALE, scale) * Matrix(TRANS, center);
	_pBoxGraphicsObject->SetWorld(world);
}

void Octree::setColliderModel(Model* pModel, int depth)
{
	_pColliderModel = pModel;
	_originalWorld = Matrix(IDENTITY);

	Vect unit = Vect(1.0f, 1.0f, 1.0f) * 0.25f;

	setMinAndMax(_pColliderModel->getMinAABB() - unit, _pColliderModel->getMaxAABB() + unit);

	//Create More Boxes?

	depth -= 1;
	if (depth == 0) return;

	Vect* vertices = _pColliderModel->getVectList();
	int numOfVertieces = _pColliderModel->getVectNum();

	for (int i = 0; i < numOfVertieces; i++)
	{
		const Vect& vertex = vertices[i];

		int index = computeOctantIndex(vertex, _minVert, _maxVert);
		Octree*& pOctree = _octrees.at(index);
		if (pOctree == nullptr)
		{
			pOctree = createOctantAtIndex(index, _pColliderModel, _originalWorld);
		}

		pOctree->generateMoreOctrees(vertex, depth);
	}

	//Vect eightScale = Vect(1.0f, 1.0f, 1.0f) * 0.5f;
	//int index = 0;
	//
	//_octrees.at(index) = new Octree();
	//_octrees.at(index)->computeData(pModel, _originalWorld * Matrix(SCALE, eightScale) * Matrix(TRANS, Vect(0.25f, 0.25f, 0.25f)), depth);
	//index += 1;
	//
	//_octrees.at(index) = new Octree();
	//_octrees.at(index)->computeData(pModel, _originalWorld * Matrix(SCALE, eightScale) * Matrix(TRANS, Vect(-0.25f, 0.25f, 0.25f)), depth);
	//index += 1;
	//
	//_octrees.at(index) = new Octree();
	//_octrees.at(index)->computeData(pModel, _originalWorld * Matrix(SCALE, eightScale) * Matrix(TRANS, Vect(0.25f, -0.25f, 0.25f)), depth);
	//index += 1;
	//
	//_octrees.at(index) = new Octree();
	//_octrees.at(index)->computeData(pModel, _originalWorld * Matrix(SCALE, eightScale) * Matrix(TRANS, Vect(0.25f, 0.25f, -0.25f)), depth);
	//index += 1;
	//
	//_octrees.at(index) = new Octree();
	//_octrees.at(index)->computeData(pModel, _originalWorld * Matrix(SCALE, eightScale) * Matrix(TRANS, Vect(-0.25f, -0.25f, 0.25f)), depth);
	//index += 1;
	//
	//_octrees.at(index) = new Octree();
	//_octrees.at(index)->computeData(pModel, _originalWorld * Matrix(SCALE, eightScale) * Matrix(TRANS, Vect(-0.25f, 0.25f, -0.25f)), depth);
	//index += 1;
	//
	//_octrees.at(index) = new Octree();
	//_octrees.at(index)->computeData(pModel, _originalWorld * Matrix(SCALE, eightScale) * Matrix(TRANS, Vect(0.25f, -0.25f, -0.25f)), depth);
	//index += 1;
	//
	//_octrees.at(index) = new Octree();
	//_octrees.at(index)->computeData(pModel, _originalWorld * Matrix(SCALE, eightScale) * Matrix(TRANS, Vect(-0.25f, -0.25f, -0.25f)), depth);
	//index += 1;
}

void Octree::setMinAndMax(const Vect& min, const Vect& max)
{
	_minVert = min;
	_maxVert = max;

	// Create Box Graphics Object for Rendering
	Vect scale = _maxVert - _minVert;
	Vect center = (_maxVert + _minVert) * 0.5f;
	Matrix world = _originalWorld * Matrix(SCALE, scale) * Matrix(TRANS, center);
	_pBoxGraphicsObject->SetWorld(world);
}

int Octree::computeOctantIndex(const Vect& vect, const Vect& minVect, const Vect& maxVect)
{
	Vect center = (maxVect + minVect) * 0.5f;
	assert(MathTools::IsLessThan(minVect, maxVect));
	//assert(MathTools::IsInRange(vect, minVect, maxVect));

	// Octant 1: left-top-front
	if ((vect[x] > center[x]) && (vect[y] > center[y]) && (vect[z] > center[z]))
	{
		return 0;
	}

	// Octant 2: right-top-front
	if (!(vect[x] > center[x]) && (vect[y] > center[y]) && (vect[z] > center[z]))
	{
		return 1;
	}

	// Octant 3: left-down-front
	if ((vect[x] > center[x]) && !(vect[y] > center[y]) && (vect[z] > center[z]))
	{
		return 2;
	}

	// Octant 4: left-top-back
	if ((vect[x] > center[x]) && (vect[y] > center[y]) && !(vect[z] > center[z]))
	{
		return 3;
	}

	// Octant 5: right-down-front
	if (!(vect[x] > center[x]) && !(vect[y] > center[y]) && (vect[z] > center[z]))
	{
		return 4;
	}

	// Octant 6: right-top-back
	if (!(vect[x] > center[x]) && (vect[y] > center[y]) && !(vect[z] > center[z]))
	{
		return 5;
	}

	// Octant 7: left-down-back
	if ((vect[x] > center[x]) && !(vect[y] > center[y]) && !(vect[z] > center[z]))
	{
		return 6;
	}

	// Octant 7: right-down-back
	if (!(vect[x] > center[x]) && !(vect[y] > center[y]) && !(vect[z] > center[z]))
	{
		return 7;
	}

	assert(false);
	return -1;
}

Octree* Octree::createOctantAtIndex(int index, Model*, const Matrix& worldMatrix)
{
	Vect eightScale = Vect(1.0f, 1.0f, 1.0f) * 0.5f;
	Vect offset = Vect(0.0f, 0.0f, 0.0f);

	switch (index)
	{
	case 0:
		offset = Vect(0.25f, 0.25f, 0.25f);
		break;
	case 1:
		offset = Vect(-0.25f, 0.25f, 0.25f);
		break;
	case 2:
		offset = Vect(0.25f, -0.25f, 0.25f);
		break;
	case 3:
		offset = Vect(0.25f, 0.25f, -0.25f);
		break;
	case 4:
		offset = Vect(-0.25f, -0.25f, 0.25f);
		break;
	case 5:
		offset = Vect(-0.25f, 0.25f, -0.25f);
		break;
	case 6:
		offset = Vect(0.25f, -0.25f, -0.25f);
		break;
	case 7:
		offset = Vect(-0.25f, -0.25f, -0.25f);
		break;
	}

	//Octree* pOctree = new Octree(pModel, worldMatrix * Matrix(SCALE, eightScale) * Matrix(TRANS, offset));
	Octree* pOctree = new Octree();
	pOctree->_pColliderModel = this->_pColliderModel;
	pOctree->_originalWorld = worldMatrix; //* Matrix(SCALE, eightScale) * Matrix(TRANS, offset);

	Vect center = (_maxVert + _minVert) * 0.5f;
	Vect offsetToOctant = MathTools::MultiplyComponents((_maxVert - _minVert), offset);

	Matrix transform = Matrix(TRANS, -center) * Matrix(SCALE, eightScale) * Matrix(TRANS, center) * Matrix(TRANS, offsetToOctant);

	pOctree->setMinAndMax(this->_minVert * transform, this->_maxVert * transform);
	//pOctree->_minVert = (this->_minVert * Matrix(TRANS, -center) * Matrix(SCALE, eightScale) * Matrix(TRANS, center) * Matrix(TRANS, offsetToOctant));
	//pOctree->_maxVert = (this->_maxVert * Matrix(TRANS, -center) * Matrix(SCALE, eightScale) * Matrix(TRANS, center) * Matrix(TRANS, offsetToOctant));

	return pOctree;
}

void Octree::generateMoreOctrees(const Vect& vect, int depth)
{
	// Create More Boxes?
	depth -= 1;
	if (depth <= 0) return;

	int index = computeOctantIndex(vect, _minVert, _maxVert);
	Octree*& pOctree = _octrees.at(index);
	if (pOctree == nullptr)
	{
		pOctree = createOctantAtIndex(index, _pColliderModel, _originalWorld);
	}

	pOctree->generateMoreOctrees(vect, depth);
}


void Octree::render(Camera* pCamera)
{
	Matrix oldWorld = _pBoxGraphicsObject->getWorld();
	Matrix world = oldWorld;
	world *= _matrix;
	_pBoxGraphicsObject->SetWorld(world);
	_pBoxGraphicsObject->Render(pCamera);
	_pBoxGraphicsObject->SetWorld(oldWorld);

	for (Octree* _pOctree : _octrees)
	{
		if (_pOctree != nullptr)
		{
			_pOctree->render(pCamera);
		}
	}
}

void Octree::render(Camera* pCamera, int depth)
{
	if (depth == 1)
	{
		Matrix oldWorld = _pBoxGraphicsObject->getWorld();
		Matrix world = oldWorld;
		world *= _matrix;
		_pBoxGraphicsObject->SetWorld(world);
		_pBoxGraphicsObject->Render(pCamera);
		_pBoxGraphicsObject->SetWorld(oldWorld);
		return;
	}

	for (Octree* _pOctree : _octrees)
	{
		if (_pOctree != nullptr)
		{
			_pOctree->render(pCamera, depth - 1);
		}
	}
}

void Octree::initialize(Model* pModel, const Matrix& worldMatrix)
{
	// Create Box Graphics Object for Rendering
	Vect scale = pModel->getMaxAABB() - pModel->getMinAABB();
	Vect center = (pModel->getMaxAABB() + pModel->getMinAABB()) * 0.5f;
	Matrix world = worldMatrix * Matrix(SCALE, scale) * Matrix(TRANS, center);
	_pBoxGraphicsObject->SetWorld(world);
}

void Octree::update(const Matrix& worldMatrix)
{
	_matrix = worldMatrix;
	for (Octree* _pOctree : _octrees)
	{
		if (_pOctree != nullptr)
		{
			_pOctree->update(worldMatrix);
		}
	}
}

bool Octree::isPointWithin(const Vect& point) const
{
	return MathTools::IsInRange(point, _pColliderModel->getMinAABB() * _originalWorld, _pColliderModel->getMaxAABB() * _originalWorld);
}


void Octree::computeData(Model* pModel, const Matrix& worldMatrix, int depth)
{
	_pColliderModel = pModel;
	_originalWorld = worldMatrix;

	Vect scale = pModel->getMaxAABB() - pModel->getMinAABB();
	Vect center = (pModel->getMaxAABB() + pModel->getMinAABB()) * 0.5f;
	Matrix world = worldMatrix * Matrix(SCALE, scale) * Matrix(TRANS, center);
	_pBoxGraphicsObject->SetWorld(world);

	depth -= 1;
	if (depth == 0) return;

	Vect eightScale = Vect(1.0f, 1.0f, 1.0f) * 0.5f;
	int index = 0;

	_octrees.at(index) = new Octree();
	_octrees.at(index)->computeData(pModel, worldMatrix * Matrix(SCALE, eightScale) * Matrix(TRANS, Vect(0.25f, 0.25f, 0.25f)), depth);
	index += 1;

	_octrees.at(index) = new Octree();
	_octrees.at(index)->computeData(pModel, worldMatrix * Matrix(SCALE, eightScale) * Matrix(TRANS, Vect(-0.25f, 0.25f, 0.25f)), depth);
	index += 1;

	_octrees.at(index) = new Octree();
	_octrees.at(index)->computeData(pModel, worldMatrix * Matrix(SCALE, eightScale) * Matrix(TRANS, Vect(0.25f, -0.25f, 0.25f)), depth);
	index += 1;

	_octrees.at(index) = new Octree();
	_octrees.at(index)->computeData(pModel, worldMatrix * Matrix(SCALE, eightScale) * Matrix(TRANS, Vect(0.25f, 0.25f, -0.25f)), depth);
	index += 1;

	_octrees.at(index) = new Octree();
	_octrees.at(index)->computeData(pModel, worldMatrix * Matrix(SCALE, eightScale) * Matrix(TRANS, Vect(-0.25f, -0.25f, 0.25f)), depth);
	index += 1;

	_octrees.at(index) = new Octree();
	_octrees.at(index)->computeData(pModel, worldMatrix * Matrix(SCALE, eightScale) * Matrix(TRANS, Vect(-0.25f, 0.25f, -0.25f)), depth);
	index += 1;

	_octrees.at(index) = new Octree();
	_octrees.at(index)->computeData(pModel, worldMatrix * Matrix(SCALE, eightScale) * Matrix(TRANS, Vect(0.25f, -0.25f, -0.25f)), depth);
	index += 1;

	_octrees.at(index) = new Octree();
	_octrees.at(index)->computeData(pModel, worldMatrix * Matrix(SCALE, eightScale) * Matrix(TRANS, Vect(-0.25f, -0.25f, -0.25f)), depth);
	index += 1;

	for (size_t i = 0; i < _octrees.size(); i++)
	{
		if (!_octrees.at(i)->doesBoxContainModel())
		{
			delete _octrees.at(i);
			_octrees.at(i) = nullptr;
		}
	}
}
bool Octree::doesBoxContainModel() const
{
	Vect* vertices = _pColliderModel->getVectList();
	int numOfVertieces = _pColliderModel->getVectNum();

	bool isModelWithinBox = false;

	for (int i = 0; i < numOfVertieces; i++)
	{
		const Vect& point = vertices[i];
		if (isPointWithin(point))
		{
			isModelWithinBox = true;
			break;
		}
	}

	return isModelWithinBox;
}
void Octree::setColliderModel(const Vect&, Model*, const Matrix, int)
{
}