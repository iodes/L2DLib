/**
 *  MotionQueueEnt.h
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */
#ifndef __LIVE2D_MOTION_QUEUE_ENT_H__
#define __LIVE2D_MOTION_QUEUE_ENT_H__


#ifndef __SKIP_DOC__

#include "../memory/LDObject.h"
#include "../ALive2DModel.h"

#include "../type/LDVector.h"


//--------- LIVE2D NAMESPACE ------------
namespace live2d
{
	class AMotion ;
	class Live2DMotion ;

	
	class MotionQueueEnt : public live2d::LDObject 
	{
		
		friend class MotionQueueManager ;
		friend class AMotion ;
		friend class Live2DMotion ;
		friend class Live2DMotionBin ;
	public:
		MotionQueueEnt();
		virtual ~MotionQueueEnt(void);

	public:
		
		void startFadeout(long long fadeOutMsec)  ;

		
		bool isFinished() { return finished ; }

		
		long long getStartTimeMSec(){ return startTimeMSec ; }

		
		long long getFadeInStartTimeMSec(){ return fadeInStartTimeMSec ; }

		
		long long getEndTimeMSec(){ return endTimeMSec ; }

		
		void setStartTimeMSec(long long t){ this->startTimeMSec = t ; }

		
		void setFadeInStartTimeMSec(long long t){ this->fadeInStartTimeMSec = t ; }

		
		void setEndTimeMSec(long long t){ this->endTimeMSec = t ; }

		
		void setFinished( bool f ){ this->finished = f ; }

		
		bool isAvailable(){ return available ; }

		
		void setAvailable( bool v ){ this->available = v ; }

		//---- state for callback(Unity etc) ----
		
		void setState( long long time , float weight ){ this->state_time = time ; this->state_weight = weight ; }

		
		long long getState_time(){ return this->state_time ; }

		
		float getState_weight(){ return this->state_weight ; }
	    
	private:
		
		bool			autoDelete;					
		AMotion* 		motion;						

		bool 			available;					
		bool 			finished ;					
		bool 			started ;					
		long long 		startTimeMSec ;				
		long long 		fadeInStartTimeMSec ;		

		
		
		
		
		
		
		
		
		long long endTimeMSec ;

		
		static int static_motionQueueEntNo ;
		int motionQueueEntNo ;

	private:
		//---- state for callback(Unity etc) ----
		long long   	state_time ;				
		float       	state_weight ;				
	};

}
//--------- LIVE2D NAMESPACE ------------

#endif // __SKIP_DOC__

#endif	// __LIVE2D_MOTION_QUEUE_ENT_H__
