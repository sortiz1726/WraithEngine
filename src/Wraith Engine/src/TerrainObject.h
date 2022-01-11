#ifndef _TerrainObjectObject
#define _TerrainObjectObject

#include "GameObject.h"
#include "Terrain.h"

struct AABBCell;
struct AABBCellIndex;

/**********************************************************************************************//**
 * <summary> A TerrainObject object used for storing TerrainObject model and texture.
 * 			 As well as having functionality for collision testing
 * 			 </summary>
 *
 * \ingroup TERRAIN
 *
 * <remarks> remarks>
 **************************************************************************************************/

class TerrainObject : public Terrain, public Drawable
{
private:
	struct CellTriangle
	{
		struct VertexIndex
		{
			int _row = 0;
			int _column = 0;
		};

		VertexIndex _indexA;
		VertexIndex _indexB;
		VertexIndex _indexC;
	};

public:
	TerrainObject() = default;
	TerrainObject(const TerrainObject&) = default;
	TerrainObject& operator=(const TerrainObject&) = default;
	TerrainObject(TerrainObject&&) = default;
	TerrainObject& operator=(TerrainObject&&) = default;
	~TerrainObject();

	TerrainObject(const char* fileName,
		float sideLength,
		float maxHeight, float assignedGroundLevel,
		const std::string& textureName,
		int uRepeat, int vRepeat);

	// intersect not being used anymore
	void intersect(Collidable*) const override;

	virtual TerrainRectangleArea getTerrainRectangleArea(Collidable*) const override;
	virtual const AABBCell& getAABBCellAt(int row, int column) const override;

	/**********************************************************************************************//**
	* <summary> Visualizes the cell on the terrain that the collidable is currently above/below.
	*  </summary>
	* \ingroup TERRAIN
	*
	* <remarks> Collidables uses BSphere center for its position. <remarks>
	* 
	* <param name="collidable"> a collidable.</param>
	**************************************************************************************************/
	void visualizeCellAt(const Collidable& collidable) const;

	/**********************************************************************************************//**
	* <summary> Visualizes the cell on the terrain given a position.
	*  </summary>
	* \ingroup TERRAIN
	*
	* <remarks> <remarks>
	*
	* <param name="position"> a Vect position.</param>
	**************************************************************************************************/
	virtual void visualizeCellAt(const Vect& position) const override;

	const AABBCell& getCellAt(const Vect& position) const;
	AABBCellIndex getCellIndexAt(const Vect& position) const;

	/**********************************************************************************************//**
	* <summary> computes the point on the terrain given a position in 3D space </summary>
	* \ingroup TERRAIN
	*
	* <remarks> <remarks>
	*
	* <param name="position"> a position.</param>
	**************************************************************************************************/
	Vect computePointOnTerrainObject(const Vect& position) const;

	/**********************************************************************************************//**
	* <summary> computes the normal on the terrain given a position in 3D space </summary>
	* \ingroup TERRAIN
	*
	* <remarks> <remarks>
	*
	* <param name="position"> a position.</param>
	**************************************************************************************************/
	Vect computeNormalOnTerrainObject(const Vect& position) const;

	virtual void submitTerrainDrawRegistration() override;
	virtual void submitTerrainDrawDeregistration() override;

private:
	// Initialization helpers
	void computeVertices(float sideLength, const int& sideCount, GLbyte* imageData, float maxHeight, float assignedGroundLevel, VertexStride_VUN* pVertexList, int uRepeat, int vRepeat);
	void computeTriangleIndices(const int& sideCount, TriangleIndex* pTriangleList);
	void computeVertexNormals(const int& sideCount, TriangleIndex* pTriangleList, VertexStride_VUN* pVertexList);
	void computeAABBCells(const int& sideCount, VertexStride_VUN* pVertexList);

	int computeTexelIndex(int side, int row, int col) const;
	int computeVertexIndex(int side, int row, int col) const;
	int computeTriangleIndex(int side, int row, int col) const;

	Vect computeFaceNormal(const int triangleIndex, const TriangleIndex triangleList[], const VertexStride_VUN vertexList[]);
	Vect computeFaceNormal(const TriangleIndex& triangleIndex, const VertexStride_VUN vertexList[]);
	Vect computeFaceNormal(const Vect& p1, const Vect& p2, const Vect& p3);

	Vect convert(const VertexStride_VUN&) const;

	CellTriangle computeCellTriangleAt(const Collidable&) const;
	CellTriangle computeCellTriangleAt(const Vect& position) const;

	// compute closest helpers
	Vect interpolate(const Vect& vertexQA, const Vect& vertexQB, const Vect& vertexQC, float beta, float gamma) const;
	void outputBetaGamma(const Vect& target, const Vect& vertexQA, const Vect& vertexQB, const Vect& vertexQC, float& outBeta, float& outGamma) const;
	void outputBetaGamma(const Vect& position, float& outBeta, float& outGamma) const;

	virtual void draw() override;

private:
	Model* _pTerrainObjectModel;

	GraphicsObject* _pTerrainObjectGraphicsObject;
	GraphicsObject* _pTerrainObjectGraphicsObjectWire;

	std::vector<std::vector<AABBCell>> _AABBCells;
	std::vector<std::vector<Vect>> _normals;

	float _sideLength;
	float _cellLength;
};

#endif // !_TerrainObjectObject

//-----------------------------------------------------------------------------------------------------------------------------
// TerrainObjectObject Comment Template
//-----------------------------------------------------------------------------------------------------------------------------