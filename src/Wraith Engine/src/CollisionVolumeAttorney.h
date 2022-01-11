#ifndef _CollisionVolumeAttorney
#define _CollisionVolumeAttorney

class Vect;
class CollisionVolume;
class CollisionVolumeBSphere;

/**********************************************************************************************//**
 * <summary> A collision volume attorney used to grant access to private functions
 * 			 of collision volume to some other classes.</summary>
 *
 * <remarks> </remarks>
 **************************************************************************************************/
class CollisionVolumeAttorney
{
private:
	CollisionVolumeAttorney() = delete;
	CollisionVolumeAttorney(const CollisionVolumeAttorney&) = delete;
	CollisionVolumeAttorney& operator=(const CollisionVolumeAttorney&) = delete;
	CollisionVolumeAttorney(CollisionVolumeAttorney&&) = delete;
	CollisionVolumeAttorney& operator=(CollisionVolumeAttorney&&) = delete;
	~CollisionVolumeAttorney() = delete;;

public:
	/**********************************************************************************************//**
	* <summary> Provides Insersect access to CollisionVolumes.</summary>
	*
	* <remarks> Used by MathTools and CollisionVolumeBSphere. </remarks>
	**************************************************************************************************/
	class IntersectAccess
	{
		//friend class MathTools;
		friend class CollisionVolumeBSphere;
		friend class CollisionVolumeAABB;

		static bool IntersectAccept(const CollisionVolume&, const CollisionVolume&);
		static bool IntersectVisitor(const CollisionVolume&, const CollisionVolumeBSphere&);
		static bool IntersectVisitor(const CollisionVolume&, const CollisionVolumeAABB&);
	};

	/**********************************************************************************************//**
	* <summary> Provides Debug Draw access to CollisionVolumes.</summary>
	*
	* <remarks> Used by Visualizer.</remarks>
	**************************************************************************************************/
	class DebugDrawAccess
	{
		friend class Visualizer;

		static void DebugDraw(const CollisionVolume&, const Vect& color, int depth);
	};
};
#endif // !_CollisionVolumeAttorney

//-----------------------------------------------------------------------------------------------------------------------------
// CollisionVolumeAttorney Comment Template
//-----------------------------------------------------------------------------------------------------------------------------