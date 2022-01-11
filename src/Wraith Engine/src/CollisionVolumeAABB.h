#ifndef _CollisionVolumeAABB
#define _CollisionVolumeAABB

#include "AzulCore.h"
#include "CollisionVolume.h"

class CollisionVolumeBSphere;
class CollisionVolumeOBB;
class Triangle;

/**********************************************************************************************//**
 * <summary> A Collision Volume AABB.</summary>
 *
 * <remarks> inherits from CollisionVolume. </remarks>
 **************************************************************************************************/
class CollisionVolumeAABB : public CollisionVolume
{
public:
	CollisionVolumeAABB() = default;
	CollisionVolumeAABB(const CollisionVolumeAABB&) = default;
	CollisionVolumeAABB& operator=(const CollisionVolumeAABB&) = default;
	CollisionVolumeAABB(CollisionVolumeAABB&&) = default;
	CollisionVolumeAABB& operator=(CollisionVolumeAABB&&) = default;
	~CollisionVolumeAABB() = default;

	// Inherited via CollisionVolume

	/**********************************************************************************************//**
	 * <summary> Calculates the data for AABB.
	 * 			 In this case the Max and Min Vertices.</summary>
	 *
	 * <remarks> </remarks>
	 *
	 * <param name="pModel"> the pointer to a model.</param>
	 * <param name="worldMatrix"> The world matrix.</param>
	 **************************************************************************************************/
	virtual void computeData(Model* pModel, const Matrix& worldMatrix) override;

	/**********************************************************************************************//**
	* <summary> Calculates the data for AABB.
	* 			 In this case the Max and Min Vertices.</summary>
	*
	* <remarks> Uses a BSphere. </remarks>
	*
	* <param name="bSphere"> A BSphere.</param>
	**************************************************************************************************/
	void computeData(const CollisionVolumeBSphere& BSphere);

	// Intersection
	virtual bool intersectAccept(const CollisionVolume&) const override;
	virtual bool intersectVisitor(const CollisionVolumeBSphere&) const override;
	virtual bool intersectVisitor(const CollisionVolumeAABB&) const override;
	virtual bool intersectVisitor(const CollisionVolumeOBB&) const override;
	virtual bool intersectVisitor(const CollisionVolumeOctree&) const override;

	// Setters

	/**********************************************************************************************//**
	 * <summary> Sets the minimum and maximum vertex in world space.</summary>
	 *
	 * <remarks> </remarks>
	 *
	 * <param name="minWorldVertex"> The min world vertex.</param>
	 * <param name="maxWorldVertex"> The max world vertex.</param>
	 **************************************************************************************************/
	void setMinMaxWorldVertex(const Vect& minWorldVertex, const Vect& maxWorldVertex);

	// Getters

	/**********************************************************************************************//**
	 * <summary> Gets the minimum vertex in world space.</summary>
	 *
	 * <remarks> </remarks>
	 *
	 * <returns> The minimum vertex.</returns>
	 **************************************************************************************************/
	const Vect& getMinWorldVertex() const;

	/**********************************************************************************************//**
	* <summary> Gets the maximum vertex in world space.</summary>
	*
	* <remarks> </remarks>
	*
	* <returns> The maximum vertex.</returns>
	**************************************************************************************************/
	const Vect& getMaxWorldVertex() const;

	/**********************************************************************************************//**
	* <summary> Gets the world matrix of AABB.</summary>
	*
	* <remarks> </remarks>
	*
	* <returns> The world matrix.</returns>
	**************************************************************************************************/
	const Matrix& getWorldMatrix() const;

	/**********************************************************************************************//**
	* <summary> Gets the inverse world matrix of AABB.</summary>
	*
	* <remarks> </remarks>
	*
	* <returns> The world matrix.</returns>
	**************************************************************************************************/
	const Matrix& getInverseWorldMatrix() const;

	/**********************************************************************************************//**
	* <summary> Gets the minimum vertex in local space.</summary>
	*
	* <remarks> </remarks>
	*
	* <returns> The minimum vertex.</returns>
	**************************************************************************************************/
	const Vect& getMinLocalVertex() const;

	/**********************************************************************************************//**
	* <summary> Gets the maximum vertex in local space.</summary>
	*
	* <remarks> </remarks>
	*
	* <returns> The maximum vertex.</returns>
	**************************************************************************************************/
	const Vect& getMaxLocalVertex() const;

	/**********************************************************************************************//**
	* <summary> Gets the half diagonal of AABB in local space.</summary>
	*
	* <remarks> </remarks>
	*
	* <returns> The half diagonal.</returns>
	**************************************************************************************************/
	const Vect& getLocalHalfDiagonal() const;

	/**********************************************************************************************//**
	* <summary> Gets the center position of AABB in world space.</summary>
	*
	* <remarks> </remarks>
	*
	* <returns> The center.</returns>
	**************************************************************************************************/
	const Vect& getWorldCenter() const;

	/**********************************************************************************************//**
	* <summary> Gets scaling factor sqaured of AABB.</summary>
	*
	* <remarks> </remarks>
	*
	* <returns> The scaling factor squared.</returns>
	**************************************************************************************************/
	float getScalingFactorSquared() const;

	/**********************************************************************************************//**
	* <summary> Calculates the data for AABB.
	* 			 In this case the Max and Min Vertices.</summary>
	*
	* <remarks> Uses a OBB. </remarks>
	*
	* <param name="OBB"> A OBB.</param>
	**************************************************************************************************/
	void computeData(const CollisionVolumeOBB& OBB);

	/**********************************************************************************************//**
	* <summary> Calculates the data for AABB.
	* 			 In this case the Max and Min Vertices.</summary>
	*
	* <remarks> Uses a Triangle. </remarks>
	*
	* <param name="triangle"> A Triangle.</param>
	**************************************************************************************************/
	void computeData(const Triangle& triangle);

	virtual int getMaxDepth() const override;

private:
	// Debugging
	virtual void debugDraw(const Vect& color, int depth) const override;

private:
	Vect _minWorldVertex;
	Vect _maxWorldVertex;

	// Required for AABB
	Matrix _worldMatrix;
	Matrix _inverseWorldMatrix;
	Vect _minLocalVertex;
	Vect _maxLocalVertex;
	Vect _localHalfDiagonal;
	Vect _worldCenter;
	float _scalingFactorSqaured = 0;
};
#endif // !_CollisionVolumeAABB

//-----------------------------------------------------------------------------------------------------------------------------
// CollisionVolumeAABB Comment Template
//-----------------------------------------------------------------------------------------------------------------------------