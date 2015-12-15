/**
 *  EyeBlinkMotion.h
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */
#ifndef __LIVE2D_EYE_BLINK_MOTION_H__
#define __LIVE2D_EYE_BLINK_MOTION_H__


#include "../memory/LDObject.h"

#include "../type/LDVector.h"

#include "../ALive2DModel.h"


//--------- LIVE2D NAMESPACE ------------
namespace live2d 
{

	
	class EyeBlinkMotion : public live2d::LDObject 
	{

	public:
		
		enum EYE_STATE{
			STATE_FIRST = 0 , 
			STATE_INTERVAL ,
			STATE_CLOSING ,
			STATE_CLOSED , 
			STATE_OPENING ,
		};

	public:
		// Constructor
		EyeBlinkMotion();

		// Destructor
		virtual ~EyeBlinkMotion();

	public:
		
		long long calcNextBlink() ;

		
		void setInterval( int blinkIntervalMsec) ;

		
		void setEyeMotion( int closingMotionMsec , int closedMotionMsec , int openingMotionMsec ) ;

		
		void setParam( live2d::ALive2DModel *model ) ;

	private:
		long long 			nextBlinkTime ;				
		
		int 				eyeState ;					
		long long 			stateStartTime ;			

		bool 				closeIfZero;				
		
		live2d::LDString 	eyeID_L ;					
		live2d::LDString 	eyeID_R ;					

		int					blinkIntervalMsec ;			
		int 				closingMotionMsec ;			
		int 				closedMotionMsec  ;			
		int 				openingMotionMsec ;			

	};

}
//--------- LIVE2D NAMESPACE ------------


#endif		// __LIVE2D_EYE_BLINK_MOTION_H__
