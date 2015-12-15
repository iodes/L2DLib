/**
 *  MotionQueueManager.h
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */
#ifndef __LIVE2D_MOTION_QUEUE_MANAGER_H__
#define __LIVE2D_MOTION_QUEUE_MANAGER_H__


#include "../memory/LDObject.h"
#include "../ALive2DModel.h"

#include "../type/LDVector.h"
#include "AMotion.h"

//--------- LIVE2D NAMESPACE ------------
namespace live2d
{
	class Live2DMotion ;
	class MotionQueueEnt ;
	class MemoryParam ;


	
	class MotionQueueManager : public live2d::LDObject 
	{
	public:
		MotionQueueManager();
		virtual ~MotionQueueManager();
		
		
		
		int startMotion( AMotion * motion , bool autoDelete ) ;
		
		
		bool updateParam( live2d::ALive2DModel * model ) ;

		
		bool isFinished() ;
		
		
		bool isFinished(int motionQueueEntNo ) ;


		
		void stopAllMotions() ;

		
		void setMotionDebugMode( bool f ){ this->motionDebugMode = f ; }

		
		MotionQueueEnt* getMotionQueueEnt( int entNo ) ;
	    
	#if L2D_VERBOSE
		void DUMP() ;
	#endif

	private:
		live2d::LDVector<MotionQueueEnt *> *motions ;

		bool motionDebugMode ;

		live2d::MemoryParam*  memoryManagement ;
		live2d::AMemoryHolder*	memoryHolderFixedMain ;
	};

}
//--------- LIVE2D NAMESPACE ------------

#endif		// __LIVE2D_MOTION_QUEUE_MANAGER_H__
