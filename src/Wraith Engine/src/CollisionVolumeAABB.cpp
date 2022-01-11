#include "CollisionVolumeAABB.h"
#include "CollisionVolumeBSphere.h"
#include "CollisionVolumeOBB.h"
#include "Triangle.h"
#include "VisualizerAttorney.h"
#include "MathTools.h"

void CollisionVolumeAABB::computeData(Model* pModel, const Matrix& worldMatrix)
{
	// Get Vectex collection information
	int numberOfVertices = pModel->getVectNum();
	Vect* vertices = pModel->getVectList();

	// IMPORTANT: transformOffset vertex by worldMatrix matrix

	// Initialize min and max vertex a vertex in the collection
	Vect minWorldVertex = vertices[0] * worldMatrix;
	Vect maxWorldVertex = minWorldVertex;

	// Go through every vertex and calculate min and max vertex
	for (int i = 1; i < numberOfVertices; i++)
	{
		const Vect& vertex = vertices[i] * worldMatrix;
		minWorldVertex = MathTools::Min(minWorldVertex, vertex);
		maxWorldVertex = MathTools::Max(maxWorldVertex, vertex);
	}

	// Now set our min and max values
	setMinMaxWorldVertex(minWorldVertex, maxWorldVertex);
}

void CollisionVolumeAABB::computeData(const CollisionVolumeBSphere& BSphere)
{
	float radius = BSphere.getRadius();
	const Vect& center = BSphere.getCenter();

	Vect halfDiagonal = Vect(radius, radius, radius);

	Vect minWorldVertex = center - halfDiagonal;
	Vect maxWorldVertex = center + halfDiagonal;

	setMinMaxWorldVertex(minWorldVertex, maxWorldVertex);
}

//-----------------------------------------------------------------------------------------------------------------------------
// Intersections
//-----------------------------------------------------------------------------------------------------------------------------
bool CollisionVolumeAABB::intersectAccept(const CollisionVolume& collisionVolume) const
{
	return collisionVolume.intersectVisitor(*this);
}

bool CollisionVolumeAABB::intersectVisitor(const CollisionVolumeBSphere& BSphere) const
{
	return MathTools::Intersect(BSphere, *this);
}

bool CollisionVolumeAABB::intersectVisitor(const CollisionVolumeAABB& AABB) const
{
	return MathTools::Intersect(AABB, *this);
}

bool CollisionVolumeAABB::intersectVisitor(const CollisionVolumeOBB& OBB) const
{
	return MathTools::Intersect(*this, OBB);
}

bool CollisionVolumeAABB::intersectVisitor(const CollisionVolumeOctree& Octree) const
{
	return MathTools::Intersect(*this, Octree);
}

//-----------------------------------------------------------------------------------------------------------------------------
// Debugging
//-----------------------------------------------------------------------------------------------------------------------------
void CollisionVolumeAABB::debugDraw(const Vect& color, int depth) const
{
	depth; // is ignored
	VisualizerAttorney::RenderAccess::ShowAABB(*this, color);
}

//-----------------------------------------------------------------------------------------------------------------------------
// Getters
//-----------------------------------------------------------------------------------------------------------------------------

void CollisionVolumeAABB::setMinMaxWorldVertex(const Vect& minWorldVertex, const Vect& maxWorldVertex)
{
	_minWorldVertex = minWorldVertex;
	_maxWorldVertex = maxWorldVertex;

	// For OBB stuff
	_worldMatrix = Matrix(IDENTITY);
	_inverseWorldMatrix = _worldMatrix;

	_minLocalVertex = _minWorldVertex;
	_maxLocalVertex = _maxWorldVertex;
	_localHalfDiagonal = 0.5f * (_maxLocalVertex - _minLocalVertex);
	_worldCenter = (_minLocalVertex + _localHalfDiagonal) * _worldMatrix;
	_scalingFactorSqaured = _worldMatrix.get(MatrixRowType::ROW_0).magSqr();
}

const Vect& CollisionVolumeAABB::getMinWorldVertex() const
{
	return _minWorldVertex;
}

const Vect& CollisionVolumeAABB::getMaxWorldVertex() const
{
	return _maxWorldVertex;
}

// OBB stuff
const Matrix& CollisionVolumeAABB::getWorldMatrix() const
{
	return _worldMatrix;
}

const Matrix& CollisionVolumeAABB::getInverseWorldMatrix() const
{
	return _inverseWorldMatrix;
}

const Vect& CollisionVolumeAABB::getMinLocalVertex() const
{
	return _minLocalVertex;
}

const Vect& CollisionVolumeAABB::getMaxLocalVertex() const
{
	return _maxLocalVertex;
}

const Vect& CollisionVolumeAABB::getLocalHalfDiagonal() const
{
	return _localHalfDiagonal;
}

const Vect& CollisionVolumeAABB::getWorldCenter() const
{
	return _worldCenter;
}

float CollisionVolumeAABB::getScalingFactorSquared() const
{
	return _scalingFactorSqaured;
}


void CollisionVolumeAABB::computeData(const CollisionVolumeOBB& OBB)
{
	//Matrix world = MathTools::ExtractScaleMatrix(OBB.getWorldMatrix()) * MathTools::ExtractTranslationMatrix(OBB.getWorldMatrix());
	
	Vect worldMax = OBB.getMaxLocalVertex() * OBB.getWorldMatrix();
	Vect worldMin = OBB.getMinLocalVertex() * OBB.getWorldMatrix();

	setMinMaxWorldVertex(worldMin, worldMax);
}

void CollisionVolumeAABB::computeData(const Triangle& triangle)
{
	Vect minValues = MathTools::Min(triangle.getVertex0(), triangle.getVertex1());
	Vect maxValues = MathTools::Max(triangle.getVertex0(), triangle.getVertex1());
	minValues = MathTools::Min(minValues, triangle.getVertex2());
	maxValues = MathTools::Max(maxValues, triangle.getVertex2());

	setMinMaxWorldVertex(minValues, maxValues);
}

int CollisionVolumeAABB::getMaxDepth() const
{
	return 0;
}
