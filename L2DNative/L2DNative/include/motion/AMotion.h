/**
 *  AMotion.h
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */
#ifndef __LIVE2D_A_MOTION_H__
#define __LIVE2D_A_MOTION_H__


#include "../memory/LDObject.h"

#include "../ALive2DModel.h"

//--------- LIVE2D NAMESPACE ------------
namespace live2d 
{

	class MotionQueueEnt ;

	
	class AMotion : public live2d::LDObject 
	{
	public:
		AMotion();
		virtual ~AMotion() ;

	public:
		
		void updateParam( live2d::ALive2DModel * model , MotionQueueEnt *motionQueueEnt ) ;

	public:

		
		void setFadeIn( int fadeInMsec ){ this->fadeInMsec = fadeInMsec ; }

		
		void setFadeOut( int fadeOutMsec){ this->fadeOutMsec = fadeOutMsec ; }
		
		
		int getFadeOut(){ return this->fadeOutMsec ; }

		
		int getFadeIn(){ return this->fadeInMsec ; }

		
		void setWeight( float weight){ this->weight = weight ; }
		
		
		float getWeight(){ return this->weight ; }

		
		virtual int getDurationMSec(){ return -1 ; }
		
		
		virtual int getLoopDurationMSec(){ return -1 ; }


		
		void setOffsetMSec( int offsetMsec ){ this->offsetMsec = offsetMsec ; }

		
		void reinit(){}

	protected:
		
		virtual void updateParamExe( live2d::ALive2DModel * model , long long timeMSec , float weight , MotionQueueEnt *motionQueueEnt ) = 0 ;

		
		float getEasing( float time , float totalTime , float accelerateTime ) ;

	protected:
		int 	fadeInMsec ;		
		int 	fadeOutMsec ;		
		float 	weight ;			

		int 	offsetMsec ;		

	};

}
//--------- LIVE2D NAMESPACE ------------


#endif		// __LIVE2D_A_MOTION_H__
