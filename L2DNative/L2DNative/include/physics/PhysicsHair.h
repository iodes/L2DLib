/**
 *  PhysicsHair.h
 *
 *  Created on: 2010/11/29
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */
#ifndef __LIVE2D_PHYSICS_HAIR_H__
#define __LIVE2D_PHYSICS_HAIR_H__


#include "../Live2D.h"
#include "../memory/LDObject.h"
#include "../ALive2DModel.h"
#define _USE_MATH_DEFINES

#include	"../util/UtMath.h"

//--------- LIVE2D NAMESPACE ------------
namespace live2d 
{
	class IPhysicsSrc ;
	class IPhysicsTarget ;
	class MemoryParam ;

#ifndef __SKIP_DOC__

	
	class PhysicsPoint  : public live2d::LDObject 
	{
	public:
		PhysicsPoint()
			: mass(1) , x(0) ,y(0) ,vx(0),vy(0) ,ax(0),ay(0) , fx(0) , fy(0)
			, last_x(0) , last_y(0) , last_vx(0) , last_vy(0)
		{

		}
		
		void setupLast()
		{
			this->last_x = x ;
			this->last_y = y ;
			this->last_vx = vx ;
			this->last_vy = vy ;
		}

	public:
		float 	mass ;					
		
		float 	x  , y ;				
		float 	vx ,vy ;				
		float 	ax ,ay ;				
			
		float 	fx ,fy ;				

		float 	last_x , last_y ;		
		float 	last_vx , last_vy ;		
		
	} ;

	
#endif // __SKIP_DOC__


	
	class PhysicsHair : public live2d::LDObject 
	{
	public:
		typedef enum 
		{
			SRC_TO_X = 0 ,
			SRC_TO_Y ,
			SRC_TO_G_ANGLE 
		} Src ;

		typedef enum 
		{
			TARGET_FROM_ANGLE = 0 ,
			TARGET_FROM_ANGLE_V  
		} Target ;

	public:
		// Constructor
		PhysicsHair() ;
		PhysicsHair(float baseLengthM , float airRegistance, float mass ) ;

		// Destructor
		virtual ~PhysicsHair();

	public:
		
		
		
		
		void setup(float baseLengthM , float airRegistance, float mass ) ;

		
		void setup() ;


		
		void addSrcParam( PhysicsHair::Src srcType , const char * paramID , float scale , float weight ) ;

		
		void addTargetParam( PhysicsHair::Target targetType , const char * paramID , float scale , float weight ) ;
		
		
		void update(live2d::ALive2DModel * model , long long time);

		
		PhysicsPoint & getPhysicsPoint1(){ return p1 ; }

		
		PhysicsPoint & getPhysicsPoint2(){ return p2 ; }

		
		float getGravityAngleDeg(){ return this->gravityAngleDeg ; }

		
		void setGravityAngleDeg(float angleDeg){ this->gravityAngleDeg = angleDeg ; }
		
		
		float getAngleP1toP2Deg(){ return angleP1toP2Deg ; }

		
		float getAngleP1toP2Deg_velocity(){ return angleP1toP2Deg_v ; }
		

	private:
		
		void update_exe(live2d::ALive2DModel *& model, float dt);

		inline float calc_angleP1toP2()
		{
			return (float)(-180*(L2D_ATAN2(p1.x - p2.x, -(p1.y - p2.y)))/M_PI_F) ;
		}

	private:
		PhysicsPoint 						p1 ;							
		PhysicsPoint 						p2 ;							

		float		 						baseLengthM;					
		float 								gravityAngleDeg;				
		float 								airResistance;					

		float 								angleP1toP2Deg ;				
		float 								last_angleP1toP2Deg ;

		float 								angleP1toP2Deg_v ;				

		
		long long 							startTime;						
		long long 							lastTime;						

	    
		live2d::LDVector<IPhysicsSrc*>* 	srcListPtr ;					

	   
		live2d::LDVector<IPhysicsTarget*>*	targetListPtr ;				 	

		live2d::MemoryParam*  				memoryManagement ;
		live2d::AMemoryHolder*				memoryHolderFixedMain ;

	};

}
//--------- LIVE2D NAMESPACE ------------



#endif	// __LIVE2D_PHYSICS_HAIR_H__
