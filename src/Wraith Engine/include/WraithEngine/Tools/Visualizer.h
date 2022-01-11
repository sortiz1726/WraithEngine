#ifndef _Visualizer
#define _Visualizer

#include "AzulCore.h"
#include "CollisionVolume.h"
#include <list>

class CollisionVolume;
class CollisionVolumeBSphere;
class CollisionVolumeAABB;
class CollisionVolumeOBB;
class RenderCommand;

/**********************************************************************************************//**
 * <summary> A visualizer responsible to drawing wireframe collision models for user debugging.</summary>
 *
 * <remarks> </remarks>
 **************************************************************************************************/
class Visualizer
{
	friend class VisualizerAttorney;

	typedef std::list<RenderCommand*> CommandList;
private:
	static Visualizer* pVisualzierInstance;

	Visualizer();
	Visualizer(const Visualizer&) = delete;
	Visualizer& operator=(const Visualizer&) = delete;
	Visualizer(Visualizer&&) = delete;
	Visualizer& operator=(Visualizer&&) = delete;
	~Visualizer();

	static Visualizer& GetInstance();

	void privShowCollisionVolume(const CollisionVolume&, const Vect& color, int depth);

	void privShowRay(const Vect& start, const Vect& direction, const Vect& color);

	void privShowPointAt(const Vect& position, const Vect& color);
	/**********************************************************************************************//**
	* <summary> Renders the AABB wireframe onto the screen.</summary>
	*
	* <remarks> DELAY called by RenderAABBCommand::execute()
	* 			 through VisualizerAttorney::RenderAccess::RenderAABBphere(). </remarks>
	*
	* <param name="world"> The world matrix.</param>
	* <param name="color">		  The color.</param>
	**************************************************************************************************/
	void renderPoint(Matrix& world, const Vect& color);

	void privShowLineSegment(const Vect& position_1, const Vect& position_2, const Vect& color);
	/**********************************************************************************************//**
	* <summary> Renders the AABB wireframe onto the screen.</summary>
	*
	* <remarks> DELAY called by RenderAABBCommand::execute()
	* 			 through VisualizerAttorney::RenderAccess::RenderAABBphere(). </remarks>
	*
	* <param name="world"> The world matrix.</param>
	* <param name="color">		  The color.</param>
	**************************************************************************************************/
	void renderLineSegment(Matrix& world, const Vect& color);

	/**********************************************************************************************//**
	 * <summary> Render all visualization commands of collision models.</summary>
	 *
	 * <remarks> ONLY called by ScreenManager::privDraw() 
	 * 			 through VisualizerAttorney::RenderAccess::VisualizeAll(). </remarks>
	 **************************************************************************************************/
	static void VisualizeAll()
	{
		GetInstance().privVisualizeAll();
	}
	void privVisualizeAll();

	/**********************************************************************************************//**
	* <summary> Shows the Bsphere to be rendered.</summary>
	*
	* <remarks> </remarks>
	*
	* <param name="collisionBSphere"> The collision BSphere.</param>
	* <param name="color">			   (Optional) The color.</param>
	**************************************************************************************************/
	static void ShowBSphere(const CollisionVolumeBSphere& collisionBSphere, const Vect& color)
	{
		GetInstance().privShowBSphere(collisionBSphere, color);
	}
	void privShowBSphere(const CollisionVolumeBSphere&, const Vect& color);
	
	/**********************************************************************************************//**
	 * <summary> Renders the BSphere wireframe onto the screen.</summary>
	 *
	 * <remarks> DELAY called by RenderBSphereCommand::execute() 
	 * 			 through VisualizerAttorney::RenderAccess::RenderBSphere(). </remarks>
	 *
	 * <param name="world"> The world matrix.</param>
	 * <param name="color">		  The color.</param>
	 **************************************************************************************************/
	void renderBSphere(Matrix& world, const Vect& color);

	/**********************************************************************************************//**
	* <summary> Shows the AABB to be rendered.</summary>
	*
	* <remarks> </remarks>
	*
	* <param name="AABB"> An AABB.</param>
	* <param name="color"> (Optional) The color.</param>
	**************************************************************************************************/
	static void ShowAABB(const CollisionVolumeAABB& AABB, const Vect& color)
	{
		GetInstance().privShowAABB(AABB, color);
	}
	void privShowAABB(const CollisionVolumeAABB&, const Vect& color);
	
	/**********************************************************************************************//**
	 * <summary> Renders the AABB wireframe onto the screen.</summary>
	 *
	 * <remarks> DELAY called by RenderAABBCommand::execute()
	 * 			 through VisualizerAttorney::RenderAccess::RenderAABBphere(). </remarks>
	 *
	 * <param name="world"> The world matrix.</param>
	 * <param name="color">		  The color.</param>
	 **************************************************************************************************/
	void renderAABB(Matrix& world, const Vect& color);

	/**********************************************************************************************//**
	* <summary> Shows the OBB to be rendered.</summary>
	*
	* <remarks> </remarks>
	*
	* <param name="OBB"> An OBB.</param>
	* <param name="color"> The color.</param>
	**************************************************************************************************/
	static void ShowOBB(const CollisionVolumeOBB& OBB, const Vect& color)
	{
		GetInstance().privShowOBB(OBB, color);
	}
	void privShowOBB(const CollisionVolumeOBB&, const Vect& color);

	/**********************************************************************************************//**
	 * <summary> Renders the OBB wireframe onto the screen.</summary>
	 *
	 * <remarks> DELAY called by RenderOBBCommand::execute()
	 * 			 through VisualizerAttorney::RenderAccess::RenderOBBphere(). </remarks>
	 *
	 * <param name="world"> The world matrix.</param>
	 * <param name="color">		  The color.</param>
	 **************************************************************************************************/
	void renderOBB(Matrix& world, const Vect& color);

	/**********************************************************************************************//**
	 * <summary> Terminates Visualizer.</summary>
	 *
	 * <remarks> ONLY called by Wraith::UnLoadContent() 
	 * 			 through VisualizerAttorney::DeleteAccess::Terminate(). </remarks>
	 **************************************************************************************************/
	static void Delete();

public:
	/**********************************************************************************************//**
	* <summary> Shows the Collision Volume to be rendered.</summary>
	* \ingroup VISUALIZER
	* <remarks> Depth is only used for Octree Collision models.
	*			All other collsion volumes ignore depth value. </remarks>
	*
	* <param name="collisionVolume"> The collision volume.</param>
	**************************************************************************************************/
	static void ShowCollisionVolume(const CollisionVolume& collisionVolume)
	{
		GetInstance().privShowCollisionVolume(collisionVolume, DEFAULT_COLOR, collisionVolume.getMaxDepth());
	}
	
	/**********************************************************************************************//**
	* <summary> Shows the Collision Volume to be rendered.</summary>
	* \ingroup VISUALIZER
	* <remarks> </remarks>
	*
	* <param name="collisionVolume"> The collision volume.</param>
	* <param name="color">			  The color.</param>
	**************************************************************************************************/
	static void ShowCollisionVolume(const CollisionVolume& collisionVolume, const Vect& color)
	{
		GetInstance().privShowCollisionVolume(collisionVolume, color, collisionVolume.getMaxDepth());
	}

	/**********************************************************************************************//**
	* <summary> Shows the Collision Volume to be rendered.</summary>
	* \ingroup VISUALIZER
	* <remarks> Depth is only used for Octree Collision models.
	*			All other collsion volumes ignore depth value. </remarks>
	*
	* <param name="collisionVolume"> The collision volume.</param>
	* <param name="color">			  The color.</param>
	* <param name="depth">			  The depth.</param>
	**************************************************************************************************/
	static void ShowCollisionVolume(const CollisionVolume& collisionVolume, const Vect& color, int depth)
	{
		GetInstance().privShowCollisionVolume(collisionVolume, color, depth);
	}

	/**********************************************************************************************//**
	* <summary> Shows a ray in space to be rendered.</summary>
	* \ingroup VISUALIZER
	* <remarks> By using the length, direction is normalized </remarks>
	*
	* <param name="start"> The position of the segment.</param>
	* <param name="direction"> The position of the segment.</param>
	* <param name="length"> length of ray.</param>
	* <param name="color">			   (Optional) The color.</param>
	**************************************************************************************************/
	static void ShowRay(const Vect& start, const Vect& direction, float length, const Vect& color = Visualizer::DEFAULT_COLOR)
	{
		ShowRay(start, direction.getNorm() * length, color);
	}

	/**********************************************************************************************//**
	* <summary> Shows a ray in space to be rendered.</summary>
	* \ingroup VISUALIZER
	* <remarks> The length is determined by the direction. </remarks>
	*
	* <param name="start"> The position of the segment.</param>
	* <param name="direction"> The position of the segment.</param>
	* <param name="color">			   (Optional) The color.</param>
	**************************************************************************************************/
	static void ShowRay(const Vect& start, const Vect& direction, const Vect& color = Visualizer::DEFAULT_COLOR)
	{
		GetInstance().privShowRay(start, direction, color);
	}

	/**********************************************************************************************//**
	* <summary> Shows a point in space to be rendered.</summary>
	* \ingroup VISUALIZER
	* <remarks> </remarks>
	*
	* <param name="position"> The position of the point.</param>
	* <param name="color">			   (Optional) The color.</param>
	**************************************************************************************************/
	static void ShowPointAt(const Vect& position, const Vect& color = Visualizer::DEFAULT_COLOR)
	{
		GetInstance().privShowPointAt(position, color);
	}

	/**********************************************************************************************//**
	* <summary> Shows a line segment in space to be rendered.</summary>
	* \ingroup VISUALIZER
	* <remarks> </remarks>
	*
	* <param name="position_1"> The position of the segment.</param>
	* <param name="position_2"> The position of the segment.</param>
	* <param name="color">			   (Optional) The color.</param>
	**************************************************************************************************/
	static void ShowLineSegment(const Vect& position_1, const Vect& position_2, const Vect& color = Visualizer::DEFAULT_COLOR)
	{
		GetInstance().privShowLineSegment(position_1, position_2, color);
	}

private:
	static Vect DEFAULT_COLOR;
	
	GraphicsObject_WireframeConstantColor* _pSphereGraphicsObject;
	GraphicsObject_WireframeConstantColor* _pCubeGraphicsObject;

	CommandList _renderCommands;
};
#endif // !_Visualizer

//-----------------------------------------------------------------------------------------------------------------------------
// Visualizer Comment Template
//-----------------------------------------------------------------------------------------------------------------------------