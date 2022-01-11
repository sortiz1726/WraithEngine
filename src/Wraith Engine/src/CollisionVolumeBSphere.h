#ifndef _CollisionVolumeBSphere
#define _CollisionVolumeBSphere

#include "AzulCore.h"
#include "CollisionVolume.h"

class Triangle;
class CollisionVolumeOBB;

/**********************************************************************************************//**
 * <summary> A Collision Volume Bsphere.</summary>
 *
 * <remarks> inherits from CollisionVolume. </remarks>
 **************************************************************************************************/
class CollisionVolumeBSphere : public CollisionVolume
{
public:
	CollisionVolumeBSphere();
	CollisionVolumeBSphere(const CollisionVolumeBSphere&) = default;
	CollisionVolumeBSphere& operator=(const CollisionVolumeBSphere&) = default;
	CollisionVolumeBSphere(CollisionVolumeBSphere&&) = default;
	CollisionVolumeBSphere& operator=(CollisionVolumeBSphere&&) = default;
	~CollisionVolumeBSphere() = default;

	// Inherited via CollisionVolume

	/**********************************************************************************************//**
	 * <summary> Calculates the data for BSphere. 
	 * 			 In this case the radius and center position.</summary>
	 *
	 * <remarks> </remarks>
	 *
	 * <param name="pModel"> the pointer to a model.</param>
	 * <param name="worldMatrix"> The world matrix.</param>
	 **************************************************************************************************/
	virtual void computeData(Model* pModel, const Matrix& worldMatrix) override;
	
	/**********************************************************************************************//**
	* <summary> Calculates the data for BSphere.
	* 			 In this case the radius and center position.</summary>
	*
	* <remarks> </remarks>
	*
	* <param name="OBB"> the OBB.</param>
	**************************************************************************************************/
	void computeData(const CollisionVolumeOBB& OBB);

	/**********************************************************************************************//**
	* <summary> Calculates the data for BSphere.
	* 			 In this case the radius and center position.</summary>
	*
	* <remarks> </remarks>
	*
	* <param name="triangle"> the triangle.</param>
	**************************************************************************************************/
	void computeData(const Triangle& triangle);

	virtual bool intersectAccept(const CollisionVolume&) const override;
	virtual bool intersectVisitor(const CollisionVolumeBSphere&) const override;
	virtual bool intersectVisitor(const CollisionVolumeAABB&) const override;
	virtual bool intersectVisitor(const CollisionVolumeOBB&) const override;
	virtual bool intersectVisitor(const CollisionVolumeOctree&) const override;

	/**********************************************************************************************//**
	 * <summary> Gets the center position of BSphere.</summary>
	 *
	 * <remarks> </remarks>
	 *
	 * <returns> The center.</returns>
	 **************************************************************************************************/
	const Vect& getCenter() const;

	/**********************************************************************************************//**
	 * <summary> Gets the radius of the BSphere.</summary>
	 *
	 * <remarks> </remarks>
	 *
	 * <returns> The radius.</returns>
	 **************************************************************************************************/
	float getRadius() const;

	virtual int getMaxDepth() const override;

private:
	virtual void debugDraw(const Vect& color, int depth) const override;

private:
	Vect _center;
	float _radius;
};
#endif // !_CollisionVolumeBSphere

//-----------------------------------------------------------------------------------------------------------------------------
// CollisionVolumeBSphere Comment Template
//-----------------------------------------------------------------------------------------------------------------------------