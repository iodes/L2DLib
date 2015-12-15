/**
 *  Live2DMotion.h
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */
#ifndef __LIVE2D_MOTION_H__
#define __LIVE2D_MOTION_H__


#include "../Live2D.h"
#include "../memory/LDObject.h"
#include "../ALive2DModel.h"
#include "../type/LDVector.h"
#include "AMotion.h"

//--------- LIVE2D NAMESPACE ------------
namespace live2d
{

	class Motion ;
	class MotionQueueEnt ;
	class MemoryParam ;

	
	class Live2DMotion : public live2d::AMotion
	{
	public:
		// Constructor
		Live2DMotion();

		// Destructor
		virtual ~Live2DMotion();
		
	public:
		
		virtual void updateParamExe( live2d::ALive2DModel * model , long long timeMSec , float weight , MotionQueueEnt *motionQueueEnt) ;

		
		void setLoop( bool _loop ){ this->loop = _loop ; }

		
		bool isLoop( ){ return this->loop ; }
		
		
		void setLoopFadeIn( bool _loopFadeIn ){ this->loopFadeIn = _loopFadeIn ; }
		
		
		bool isLoopFadeIn( ){ return this->loopFadeIn ; }
		
		
		virtual int getDurationMSec() ;
		
		
		
		virtual int getLoopDurationMSec()
		{
			return loopDurationMSec ; 
		}

		
		static Live2DMotion * loadMotion( const live2d::LDString & filepath ) ;
		
		static Live2DMotion * loadMotion( const void * buf , int bufSize ) ;
		
		void dump() ;
		

		//SDK2.0
		
		//void setParamFadeIn(const char* paramID,int value);
		//void setParamFadeOut(const char* paramID,int value);
		void setParamFadeIn(LDString paramID,int value);
		void setParamFadeOut(LDString paramID,int value);
		
		int getParamFadeIn(const char* paramID);
		int getParamFadeOut(const char* paramID);


	private:
		live2d::LDVector<Motion*>* 	motionsPtr ;			

		float 						srcFps ;				
		int 						maxLength ;				

		int 						loopDurationMSec ;		
		bool 						loop ;					
		bool 						loopFadeIn;				
		int 						objectNoForDebug ;		
		
		float 						lastWeight ;
		live2d::MemoryParam*		memoryManagement ;
		live2d::AMemoryHolder*		memoryHolderFixedMain ;
	};




#ifndef __SKIP_DOC__

	
	class Motion : public live2d::LDObject
	{
	public:
		static const int MOTION_TYPE_PARAM = 0 ;
		static const int MOTION_TYPE_PARTS_VISIBLE = 1 ;
		static const int MOTION_TYPE_PARAM_FADEIN = 2 ;//SDK2.0
		static const int MOTION_TYPE_PARAM_FADEOUT = 3 ;//SDK2.0
		
		
		static const int MOTION_TYPE_LAYOUT_X = 100 ;
		static const int MOTION_TYPE_LAYOUT_Y = 101 ;
		static const int MOTION_TYPE_LAYOUT_ANCHOR_X = 102 ;
		static const int MOTION_TYPE_LAYOUT_ANCHOR_Y = 103 ;
		static const int MOTION_TYPE_LAYOUT_SCALE_X = 104 ;
		static const int MOTION_TYPE_LAYOUT_SCALE_Y = 105 ;
		
	public:
		Motion(live2d::MemoryParam* memParam) ;
		virtual ~Motion() ;
		
	public:
		int getParamIndex( live2d::ALive2DModel* model ) ;

	public:
		live2d::LDString * 			paramIDStr ;				
		
		live2d::ParamID* 			cached_paramID ;			
		int  						cached_paramIndex ;			//
		live2d::ALive2DModel* 		cached_model_ofParamIndex ;

		live2d::LDVector<float> 	values ;
		
		int 						motionType ;				

		//SDK2.0
		int 	fadeInMsec ;		
		int 	fadeOutMsec ;		
	};

#endif // __SKIP_DOC__

}
//--------- LIVE2D NAMESPACE ------------

#endif		// __LIVE2D_MOTION_H__
