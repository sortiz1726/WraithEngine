#include "TerrainObject.h"
#include "AABBCell.h"
#include "AABBCellIndex.h"
#include "TerrainRectangleArea.h"
#include "TextureTGA.h"
#include "GpuVertTypes.h"
#include "Model.h"
#include "ShaderManager.h"
#include "SceneManager.h"
#include "TextureManager.h"
#include "Scene.h"
#include "Collidable.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeBSphere.h"
#include "MathTools.h"
#include "ScreenLog.h"
#include "Visualizer.h"
#include "Colors.h"
#include <array>
#include <algorithm>

TerrainObject::TerrainObject(const char* fileName,
	float sideLength,
	float maxHeight, float assignedGroundLevel,
	const std::string& textureName,
	int uRepeat, int vRepeat)
	: _pTerrainObjectModel(nullptr), _pTerrainObjectGraphicsObject(nullptr),
	_pTerrainObjectGraphicsObjectWire(nullptr),
	_sideLength(sideLength)
{
	// Extract Data
	GLint imageWidth = -1, imageHeight = -1, Icomponents = 0;
	GLenum dtype = 0;
	GLbyte* imageData = gltReadTGABits(fileName, &imageWidth, &imageHeight, &Icomponents, &dtype);
	assert(imageWidth != 0 && imageWidth == imageHeight); // We need square images for heightmaps

	// Compute number of vertices and triangles
	const int sideCount = imageWidth;
	const int numberOfVertices = sideCount * sideCount;
	const int numberOfTriangles = 2 * ((sideCount - 1) * (sideCount - 1));

	//-------------------Set Up Vertices-------------------

	VertexStride_VUN* pVertexList = new VertexStride_VUN[numberOfVertices];

	computeVertices(sideLength, sideCount, imageData, maxHeight, assignedGroundLevel, pVertexList, uRepeat, vRepeat);

	//-------------------Set Up Triangles-------------------
	TriangleIndex* pTriangleList = new TriangleIndex[numberOfTriangles];

	computeTriangleIndices(sideCount, pTriangleList);

	// --------- Setting up the normals -----------
	computeVertexNormals(sideCount, pTriangleList, pVertexList);

	computeAABBCells(sideCount, pVertexList);

	// Create Model
	_pTerrainObjectModel = new Model(pVertexList, numberOfVertices, pTriangleList, numberOfTriangles);

	delete[] pVertexList;
	delete[] pTriangleList;

	ShaderObject* pShader = nullptr;

	pShader = ShaderManager::GetDefaultShader(ShaderManager::DefaultShader::CONSTANT_COLOR);
	Vect color = Colors::Blue;
	_pTerrainObjectGraphicsObjectWire = new GraphicsObject_WireframeConstantColor(_pTerrainObjectModel, pShader, color);

	Texture* pTexture = TextureManager::GetTexture(textureName);
	pShader = ShaderManager::GetDefaultShader(ShaderManager::DefaultShader::TEXTURE);
	_pTerrainObjectGraphicsObject = new GraphicsObject_TextureFlat(_pTerrainObjectModel, pShader, pTexture);

}

TerrainObject::~TerrainObject()
{
	delete _pTerrainObjectModel;
	delete _pTerrainObjectGraphicsObject;
	delete _pTerrainObjectGraphicsObjectWire;
}

// NOT USED ANY MORE
void TerrainObject::intersect(Collidable* pCollidable) const
{
	CollisionVolumeAABB AABB;

	// Visualizes BSphere and AABB to see which AABB cells it may intersect ith
	//Visualizer::ShowCollisionVolume(pCollidable.getBSphere(), Colors::Green);
	AABB.computeData(pCollidable->getBSphere());
	Visualizer::ShowCollisionVolume(AABB, Colors::Black);

	// The real test
	AABBCellIndex max = getCellIndexAt(AABB.getMinWorldVertex());
	AABBCellIndex min = getCellIndexAt(AABB.getMaxWorldVertex());

	bool doesIntersect = false;

	for (int row = min._row; row <= max._row; row++)
	{
		for (int column = min._column; column <= max._column; column++)
		{
			const AABBCell& cell_1 = _AABBCells[row][column];
			AABB.setMinMaxWorldVertex(cell_1._minVertex, cell_1._maxVertex);

			// If BSphere intersects  AABB cell then...
			if (MathTools::Intersect(pCollidable->getBSphere(), AABB))
			{
				// If Collision Volume intersects  AABB cell then...
				if (MathTools::Intersect(pCollidable->getCollisionVolume(), AABB))
				{
					Visualizer::ShowCollisionVolume(AABB, Colors::Green);
					doesIntersect = true;
				}
				else // else it only intersects with BSphere
				{
					Visualizer::ShowCollisionVolume(AABB, Colors::Yellow);
				}
			}
			else // It does not intersect
			{
				Visualizer::ShowCollisionVolume(AABB, Colors::Red);
			}
		}
	}

	if (doesIntersect)
	{
		Vect terrainPosition = computePointOnTerrainObject(pCollidable->getBSphere().getCenter());
		Vect terrainNormal = computeNormalOnTerrainObject(pCollidable->getBSphere().getCenter());
		pCollidable->terrainCollision();
	}
}

TerrainRectangleArea TerrainObject::getTerrainRectangleArea(Collidable* pCollidable) const
{
	CollisionVolumeAABB AABB;

	AABB.computeData(pCollidable->getBSphere());

	// The real test
	AABBCellIndex max = getCellIndexAt(AABB.getMinWorldVertex());
	AABBCellIndex min = getCellIndexAt(AABB.getMaxWorldVertex());

	return TerrainRectangleArea(this, min, max);
}

const AABBCell& TerrainObject::getAABBCellAt(int row, int column) const
{
	return _AABBCells[row][column];
}

void TerrainObject::visualizeCellAt(const Collidable& collidable) const
{
	visualizeCellAt(collidable.getBSphere().getCenter());
}

void TerrainObject::visualizeCellAt(const Vect& position) const
{
	CollisionVolumeAABB AABB;

	// Visualizes the cell below or above the pCollidable
	AABBCellIndex cellIndex = getCellIndexAt(position);
	const AABBCell& cell = _AABBCells[cellIndex._row][cellIndex._column];
	AABB.setMinMaxWorldVertex(cell._minVertex, cell._maxVertex);
	Visualizer::ShowCollisionVolume(AABB, Colors::Green);

	// Get triangle cell
	CellTriangle cellTriangle = computeCellTriangleAt(position);

	const Vect* pVertexList = _pTerrainObjectModel->getVectList();

	const int sideCount = _normals.size();
	int row = 0, column = 0;

	row = cellTriangle._indexA._row;
	column = cellTriangle._indexA._column;
	const Vect& vertexA = pVertexList[computeVertexIndex(sideCount, row, column)];

	row = cellTriangle._indexB._row;
	column = cellTriangle._indexB._column;
	const Vect& vertexB = pVertexList[computeVertexIndex(sideCount, row, column)];

	row = cellTriangle._indexC._row;
	column = cellTriangle._indexC._column;
	const Vect& vertexC = pVertexList[computeVertexIndex(sideCount, row, column)];

	Visualizer::ShowPointAt(vertexA, Colors::Purple);
	Visualizer::ShowPointAt(vertexB, Colors::Purple);
	Visualizer::ShowPointAt(vertexC, Colors::Purple);

	Vect pointOnTerrain = computePointOnTerrainObject(position);
	Visualizer::ShowPointAt(pointOnTerrain);

	// Shows normal on terrain cell
	Visualizer::ShowRay(pointOnTerrain, computeNormalOnTerrainObject(position) * 4.0f, Colors::Black);
}

const AABBCell& TerrainObject::getCellAt(const Vect& position) const
{
	AABBCellIndex cellIndex = getCellIndexAt(position);
	return _AABBCells[cellIndex._row][cellIndex._column];
}

AABBCellIndex TerrainObject::getCellIndexAt(const Vect& position) const
{
	Vect positionOffset = position;

	Vect offset = Vect(_sideLength, 0.0f, _sideLength) * 0.5f;
	positionOffset -= offset;
	positionOffset *= 1.0f / _cellLength;
	positionOffset *= -1.0f;

	int row = static_cast<int>(positionOffset[z]);
	int column = static_cast<int>(positionOffset[x]);

	row = MathTools::Clamp(row, 0, static_cast<int>(_AABBCells.size()) - 1);
	column = MathTools::Clamp(column, 0, static_cast<int>(_AABBCells.size()) - 1);

	return AABBCellIndex{ row, column };
}

//-----------------------------------------------------------------------------------------------------------------------------
// Compute closest on TerrainObject
//-----------------------------------------------------------------------------------------------------------------------------

Vect TerrainObject::computePointOnTerrainObject(const Vect& position) const
{
	// Get triangle cell
	CellTriangle cellTriangle = computeCellTriangleAt(position);

	const Vect* pVertexList = _pTerrainObjectModel->getVectList();

	const int sideCount = _normals.size();
	int row = 0, column = 0;

	// Getting all three Vertices that make up the triangle
	row = cellTriangle._indexA._row;
	column = cellTriangle._indexA._column;
	const Vect& vertexA = pVertexList[computeVertexIndex(sideCount, row, column)];

	row = cellTriangle._indexB._row;
	column = cellTriangle._indexB._column;
	const Vect& vertexB = pVertexList[computeVertexIndex(sideCount, row, column)];

	row = cellTriangle._indexC._row;
	column = cellTriangle._indexC._column;
	const Vect& vertexC = pVertexList[computeVertexIndex(sideCount, row, column)];

	float beta = 0, gamma = 0;
	outputBetaGamma(position, beta, gamma);
	return interpolate(vertexA, vertexB, vertexC, beta, gamma);
}

Vect TerrainObject::computeNormalOnTerrainObject(const Vect& position) const
{
	// Get triangle cell
	CellTriangle cellTriangle = computeCellTriangleAt(position);

	const int sideCount = _normals.size();
	int row = 0, column = 0;

	row = cellTriangle._indexA._row;
	column = cellTriangle._indexA._column;
	const Vect& normalA = _normals[row][column];

	row = cellTriangle._indexB._row;
	column = cellTriangle._indexB._column;
	const Vect& normalB = _normals[row][column];

	row = cellTriangle._indexC._row;
	column = cellTriangle._indexC._column;
	const Vect& normalC = _normals[row][column];

	float beta = 0, gamma = 0;
	outputBetaGamma(position, beta, gamma);
	return interpolate(normalA, normalB, normalC, beta, gamma);
}

void TerrainObject::submitTerrainDrawRegistration()
{
	Drawable::submitDrawRegistration();
}

void TerrainObject::submitTerrainDrawDeregistration()
{
	Drawable::submitDrawDeregistration();
}

// compute closest helpers
Vect TerrainObject::interpolate(const Vect& vertexQA, const Vect& vertexQB, const Vect& vertexQC, float beta, float gamma) const
{
	return vertexQA + beta * (vertexQB - vertexQA) + gamma * (vertexQC - vertexQB);
}

void TerrainObject::outputBetaGamma(const Vect& position, float& outBeta, float& outGamma) const
{
	// Get triangle cell
	CellTriangle cellTriangle = computeCellTriangleAt(position);

	const Vect* pVertexList = _pTerrainObjectModel->getVectList();

	const int sideCount = _normals.size();
	int row = 0, column = 0;

	row = cellTriangle._indexA._row;
	column = cellTriangle._indexA._column;
	const Vect& vertexA = pVertexList[computeVertexIndex(sideCount, row, column)];

	row = cellTriangle._indexB._row;
	column = cellTriangle._indexB._column;
	const Vect& vertexB = pVertexList[computeVertexIndex(sideCount, row, column)];

	row = cellTriangle._indexC._row;
	column = cellTriangle._indexC._column;
	const Vect& vertexC = pVertexList[computeVertexIndex(sideCount, row, column)];

	outputBetaGamma(position, vertexA, vertexB, vertexC, outBeta, outGamma);
}

void TerrainObject::outputBetaGamma(const Vect& target, const Vect& vertexQA, const Vect& vertexQB, const Vect& vertexQC, float& outBeta, float& outGamma) const
{
	Vect target_Cpy = target; target_Cpy[y] = 0.0f;
	Vect vertexQA_Cpy = vertexQA; vertexQA_Cpy[y] = 0.0f;
	Vect vertexQB_Cpy = vertexQB; vertexQB_Cpy[y] = 0.0f;
	Vect vertexQC_Cpy = vertexQC; vertexQC_Cpy[y] = 0.0f;

	Vect v0 = vertexQB_Cpy - vertexQA_Cpy;
	Vect v1 = vertexQC_Cpy - vertexQB_Cpy;
	Vect v2 = target_Cpy - vertexQA_Cpy;

	float a = v0.dot(v0);
	float b = v1.dot(v0);
	float c = v1.dot(v1);
	float d = v2.dot(v0);
	float e = v2.dot(v1);

	outBeta = (d * c - b * e) / (a * c - b * b);
	outGamma = (a * e - d * b) / (a * c - b * b);
}

//-----------------------------------------------------------------------------------------------------------------------------
// Compute Vertiecs, Triangles, and AABB Cells
//-----------------------------------------------------------------------------------------------------------------------------

void TerrainObject::computeVertices(float sideLength, const int& sideCount, GLbyte* imageData, float maxHeight, float assignedGroundLevel, VertexStride_VUN* pVertexList, int uRepeat, int vRepeat)
{
	//World Offsets
	float xOffset = sideLength / (sideCount - 1);
	float zOffset = sideLength / (sideCount - 1);
	//Texel Offsets
	float uOffset = 1.0f / (sideCount - 1);
	float vOffset = 1.0f / (sideCount - 1);

	//Texel Coordinates
	float uValue, vValue;
	uValue = vValue = 0.0f;
	vValue = 1.0f;
	//sets vertices for each section
	for (int row = 0; row < sideCount; row++)
	{
		if (row % sideCount != 0) vValue -= vOffset;
		for (int column = 0; column < sideCount; column++)
		{
			if (column == 0) uValue = 0.0f;
			//World Coordinates
			float xValue, yValue, zValue;

			xValue = xOffset * column - (sideLength / 2);
			xValue *= -1;

			uint8_t height_val = imageData[computeTexelIndex(sideCount, row, column)];
			yValue = height_val / 255.0f * maxHeight;
			yValue += assignedGroundLevel;

			zValue = zOffset * row - (sideLength / 2);
			zValue *= -1;

			if (column % sideCount != 0) uValue += uOffset;
			//Set up the vertex
			VertexStride_VUN& vertex = pVertexList[computeVertexIndex(sideCount, row, column)];
			vertex.set(xValue, yValue, zValue,
				uValue * uRepeat, vValue * vRepeat
				, 0.0f, 0.0f, 0.0f);
		}
	}
}

void TerrainObject::computeTriangleIndices(const int& sideCount, TriangleIndex* pTriangleList)
{
	int triangleIndex = 0;
	for (int row = 0; row < sideCount - 1; row++)
	{
		for (int column = 0; column < sideCount - 1; column++)
		{
			// Square Indices
			int topLeft, bottomLeft, bottomRight, topRight;

			topLeft = computeVertexIndex(sideCount, row, column);
			bottomLeft = computeVertexIndex(sideCount, row + 1, column);
			bottomRight = computeVertexIndex(sideCount, row + 1, column + 1);
			topRight = computeVertexIndex(sideCount, row, column + 1);

			pTriangleList[triangleIndex + 0].set(topRight, topLeft, bottomLeft);
			pTriangleList[triangleIndex + 1].set(topRight, bottomLeft, bottomRight);

			triangleIndex += 2;
		}
	}
}

void TerrainObject::computeVertexNormals(const int& sideCount, TriangleIndex* pTriangleList, VertexStride_VUN* pVertexList)
{
	Vect normalFaces[6];
	int triangleIndices[6] = {};
	int minTriangleIndex = 0;
	int maxTriangleIndex = computeTriangleIndex(sideCount, sideCount - 2, 2 * (sideCount - 1) - 1);
	_normals.reserve(sideCount);
	for (int row = 0; row < sideCount; row++)
	{
		std::vector<Vect> _normalRow;
		_normalRow.reserve(sideCount);

		for (int column = 0; column < sideCount; column++)
		{
			// Triangle Indices
			triangleIndices[0] = computeTriangleIndex(sideCount, row - 1, 2 * (column - 1));
			triangleIndices[1] = computeTriangleIndex(sideCount, row - 1, 2 * (column - 1) + 1);
			triangleIndices[2] = computeTriangleIndex(sideCount, row - 1, 2 * (column - 1) + 2);
			triangleIndices[3] = computeTriangleIndex(sideCount, row, 2 * (column - 1) + 1);
			triangleIndices[4] = computeTriangleIndex(sideCount, row, 2 * (column - 1) + 2);
			triangleIndices[5] = computeTriangleIndex(sideCount, row, 2 * (column - 1) + 3);

			Vect normalAverage = Vect(0, 0, 0);
			int numberOfVertices = 0;

			for (int i = 0; i < 6; i++)
			{
				int currentTriangleIndex = triangleIndices[i];
				if (currentTriangleIndex >= minTriangleIndex && currentTriangleIndex <= maxTriangleIndex)
				{
					normalAverage += computeFaceNormal(currentTriangleIndex, pTriangleList, pVertexList);
					numberOfVertices += 1;
				};
			}

			normalAverage *= (1.0f / numberOfVertices);
			normalAverage.norm();
			pVertexList[computeVertexIndex(sideCount, row, column)].nx = normalAverage[x];
			pVertexList[computeVertexIndex(sideCount, row, column)].ny = normalAverage[y];
			pVertexList[computeVertexIndex(sideCount, row, column)].nz = normalAverage[z];

			normalAverage[w] = 0.0f;
			_normalRow.push_back(normalAverage);
		}

		_normals.push_back(std::move(_normalRow));
	}
}

void TerrainObject::computeAABBCells(const int& sideCount, VertexStride_VUN* pVertexList)
{
	int cellSideCount = sideCount - 1;
	_cellLength = _sideLength / static_cast<float>(cellSideCount);

	_AABBCells.reserve(cellSideCount);
	for (int row = 0; row < cellSideCount; row++)
	{
		std::vector<AABBCell> AABBCellRow;
		AABBCellRow.reserve(cellSideCount);
		for (int column = 0; column < cellSideCount; column++)
		{
			Vect topLeft = convert(pVertexList[computeVertexIndex(sideCount, row, column)]);
			Vect topRight = convert(pVertexList[computeVertexIndex(sideCount, row, column + 1)]);
			Vect bottomLeft = convert(pVertexList[computeVertexIndex(sideCount, row + 1, column)]);
			Vect bottomRight = convert(pVertexList[computeVertexIndex(sideCount, row + 1, column + 1)]);

			std::array<float, 4> yValues = { topLeft[y], topRight[y], bottomLeft[y], bottomRight[y] };
			float minY = *std::min_element(yValues.begin(), yValues.end());
			float maxY = *std::max_element(yValues.begin(), yValues.end());

			AABBCell cell;
			cell._minVertex = bottomRight;
			cell._minVertex[y] = minY;

			cell._maxVertex = topLeft;
			cell._maxVertex[y] = maxY;

			AABBCellRow.push_back(std::move(cell));
		}
		_AABBCells.push_back(std::move(AABBCellRow));
	}
}

//-----------------------------------------------------------------------------------------------------------------------------
// Compute Index
//-----------------------------------------------------------------------------------------------------------------------------
int TerrainObject::computeTexelIndex(int sideCount, int row, int column) const
{
	size_t pixel_width = 3; // 4 bytes RGBA per pixel
	row %= sideCount;
	column %= sideCount;
	return pixel_width * (((sideCount - 1) - row) * sideCount + column);
}

int TerrainObject::computeVertexIndex(int sideCount, int row, int column) const
{
	if (row >= sideCount || column >= sideCount) return -1;
	return (row * sideCount + column);
}

int TerrainObject::computeTriangleIndex(int sideCount, int row, int column) const
{
	if (row >= sideCount - 1 || row < 0
		|| column >= 2 * (sideCount - 1) || column < 0) return -1;
	return (2 * (sideCount - 1) * row + column);
}

//-----------------------------------------------------------------------------------------------------------------------------
// Compute Face Normals
//-----------------------------------------------------------------------------------------------------------------------------
Vect TerrainObject::computeFaceNormal(const int triangleIndex, const TriangleIndex triangleList[], const VertexStride_VUN vertexList[])
{
	if (triangleIndex < 0) return Vect(0.0f, 0.0f, 0.0f);
	return computeFaceNormal(triangleList[triangleIndex], vertexList);
}

Vect TerrainObject::computeFaceNormal(const TriangleIndex& triangleIndex, const VertexStride_VUN vertexList[])
{
	Vect p1 = convert(vertexList[triangleIndex.v0]);
	Vect p2 = convert(vertexList[triangleIndex.v1]);
	Vect p3 = convert(vertexList[triangleIndex.v2]);
	return computeFaceNormal(p1, p2, p3);
}

Vect TerrainObject::computeFaceNormal(const Vect& p1, const Vect& p2, const Vect& p3)
{
	Vect v1 = p2 - p1;
	Vect v2 = p3 - p2;
	return v1.cross(v2).getNorm();
}

Vect TerrainObject::convert(const VertexStride_VUN& vertexStride) const
{
	return Vect(vertexStride.x, vertexStride.y, vertexStride.z);
}

TerrainObject::CellTriangle TerrainObject::computeCellTriangleAt(const Collidable& collidable) const
{
	return computeCellTriangleAt(collidable.getBSphere().getCenter());
}

TerrainObject::CellTriangle TerrainObject::computeCellTriangleAt(const Vect& position) const
{
	Vect position_Cpy = position;

	AABBCellIndex cellIndex = getCellIndexAt(position);

	const int sideCount = _normals.size();
	const Vect* pVertexList = _pTerrainObjectModel->getVectList();
	const Vect& bottomLeft = pVertexList[computeVertexIndex(sideCount, cellIndex._row + 1, cellIndex._column)];

	Vect offset = bottomLeft;
	position_Cpy -= offset;

	CellTriangle cellTriangle;
	cellTriangle._indexA = { cellIndex._row + 1 ,  cellIndex._column };

	if (position[z] > -position[x])
	{
		cellTriangle._indexB = { cellIndex._row, cellIndex._column };
		cellTriangle._indexC = { cellIndex._row, cellIndex._column + 1 };
	}
	else
	{
		cellTriangle._indexB = { cellIndex._row, cellIndex._column + 1 };
		cellTriangle._indexC = { cellIndex._row + 1, cellIndex._column + 1 };
	}

	return cellTriangle;
}

//-----------------------------------------------------------------------------------------------------------------------------
// Game Object Properties
//-----------------------------------------------------------------------------------------------------------------------------

void TerrainObject::draw()
{
	Camera* pCamera = SceneManager::GetCurrentScene()->getCurrentCamera();
	pCamera;
	_pTerrainObjectGraphicsObject->Render(pCamera);
	//_pTerrainObjectGraphicsObjectWire->Render(pCamera);
}