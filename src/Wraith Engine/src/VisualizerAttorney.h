#ifndef _VisualizerAttorney
#define _VisualizerAttorney

#include "Visualizer.h"

/**********************************************************************************************//**
 * <summary> A Visualizer Attorney giving access to certain Visualizer functions
 * 			 to certain classes.</summary>
 * 
 * <remarks> NEVER called by the user. </remarks>
 **************************************************************************************************/
class VisualizerAttorney
{
private:
	VisualizerAttorney() = delete;
	VisualizerAttorney(const VisualizerAttorney&) = delete;
	VisualizerAttorney& operator=(const VisualizerAttorney&) = delete;
	VisualizerAttorney(VisualizerAttorney&&) = delete;
	VisualizerAttorney& operator=(VisualizerAttorney&&) = delete;
	~VisualizerAttorney() = delete;

public:

	/**********************************************************************************************//**
	* <summary> Provides Render access to Visualizer.</summary>
	*
	* <remarks> </remarks>
	**************************************************************************************************/
	class RenderAccess
	{
		friend class Wraith;

		friend class CollisionVolumeBSphere;
		friend class CollisionVolumeAABB;
		friend class CollisionVolumeOBB;

		friend class RenderBSphereCommand;
		friend class RenderAABBCommand;
		friend class RenderOBBCommand;
		friend class RenderPointCommand;
		friend class RenderLineSegmentCommand;

		static void VisualizeAll() { Visualizer::VisualizeAll(); }
		
		static void ShowBSphere(const CollisionVolumeBSphere& collisionBSphere, const Vect& color)
		{ 
			Visualizer::ShowBSphere(collisionBSphere, color); 
		}
		static void ShowAABB(const CollisionVolumeAABB& AABB, const Vect& color)
		{
			Visualizer::ShowAABB(AABB, color);
		}
		static void ShowOBB(const CollisionVolumeOBB& OBB, const Vect& color)
		{
			Visualizer::ShowOBB(OBB, color);
		}

		static void RenderBSphere(Matrix& world, const Vect& color) { Visualizer::GetInstance().renderBSphere(world, color); }
		static void RenderAABB(Matrix& world, const Vect& color) { Visualizer::GetInstance().renderAABB(world, color); }
		static void RenderOBB(Matrix& world, const Vect& color) { Visualizer::GetInstance().renderOBB(world, color); }
		static void RenderPoint(Matrix& world, const Vect& color) { Visualizer::GetInstance().renderPoint(world, color); }
		static void RenderLineSegment(Matrix& world, const Vect& color) { Visualizer::GetInstance().renderLineSegment(world, color); }
		
	};

	/**********************************************************************************************//**
	* <summary> Provides Delete access to Visualizer.</summary>
	*
	* <remarks> </remarks>
	**************************************************************************************************/
	class DeleteAccess
	{
		friend class Wraith;

		static void Delete() { Visualizer::Delete(); }
	};
};
#endif // !_VisualizerAttorney

//-----------------------------------------------------------------------------------------------------------------------------
// VisualizerAttorney Comment Template
//-----------------------------------------------------------------------------------------------------------------------------