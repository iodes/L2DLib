/**
 *  Live2DMotionBin.h
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#pragma once


#include "../Live2D.h"
#include "../ALive2DModel.h"
#include "../type/LDVector.h"
#include <vector>
#include "AMotion.h"


//--------- LIVE2D NAMESPACE ------------
namespace live2d
{
	class MotionBin ;
	class MotionQueueEnt ;



	
	class Live2DMotionBin : public AMotion{
	public:

		
		typedef enum {
			
			DO_NOTHING_ON_DESTRUCT ,		
			DUPLICATE_AND_DESTRUCT ,		

			
			FREE_ON_DESTRUCT ,				
			DELETE_ARRAY_ON_DESTRUCT , 		
			DELETE_NORMAL_ON_DESTRUCT  , 	
			
			L2D_FREE_ON_DESTRUCT ,			
			UTFILE_RELEASE_ON_DESTRUCT		
		} BufType ;



		Live2DMotionBin();
		virtual ~Live2DMotionBin();
		
		virtual void updateParamExe( live2d::ALive2DModel * model , long long timeMSec , float weight , MotionQueueEnt *motionQueueEnt) ;


		void setLoop( bool _loop ){ this->loop = _loop ; }
		bool isLoop( ){ return this->loop ; }
		
		
		virtual int getDurationMSec() ;
		
		
		
		virtual int getLoopDurationMSec(){ 
			return loopDurationMSec ; 
		}

		
		static Live2DMotionBin * loadMotion( const l2d_string & filepath ) ;

		
		static Live2DMotionBin * loadMotion( 
						const void * buf ,					
						int bufSize ,						
						Live2DMotionBin::BufType  bufType	
					) ;
		


		void dump() ;
		


	private:
		const void *				buf ;

		Live2DMotionBin::BufType	bufType ;
	//	bool						deleteBufOnDestructor ;

		//---- 
		MotionBin**					motionPtrArray ;
		int							paramCount ;//count of MotionBin

		
		float 						srcFps ;
		int 						maxLength ;

		int 						loopDurationMSec ;
		bool 						loop ;
		int 						objectNoForDebug ;
		
		float 						lastWeight ;
		live2d::MemoryParam*		memoryManagement ;
		live2d::AMemoryHolder*		memoryHolderFixedMain ;

	};




#ifndef __SKIP_DOC__

	//=================================================
	
	//=================================================
	class MotionBin : public live2d::LDObject
	{
	public:
		static const int MOTION_TYPE_PARAM = 0 ;
		static const int MOTION_TYPE_PARTS_VISIBLE = 1 ;
		
		
		static const int MOTION_TYPE_LAYOUT_X = 100 ;
		static const int MOTION_TYPE_LAYOUT_Y = 101 ;
		static const int MOTION_TYPE_LAYOUT_ANCHOR_X = 102 ;
		static const int MOTION_TYPE_LAYOUT_ANCHOR_Y = 103 ;
		static const int MOTION_TYPE_LAYOUT_SCALE_X = 104 ;
		static const int MOTION_TYPE_LAYOUT_SCALE_Y = 105 ;
		
		MotionBin(void);
		virtual ~MotionBin(void);
		
		int getParamIndex( live2d::ALive2DModel* model ) ;

	public:
		//--- fields ---
		l2d_string * 			paramIDStr ;

		
		live2d::ParamID* 		cached_paramID ;
		int  					cached_paramIndex ;//
		live2d::ALive2DModel* 	cached_model_ofParamIndex ;

	//	l2d_vector<float> 		values ;

		
		
		
		

		
		bool					isShortArray ;

		void*					valuePtr ;
		float					minValue ;
		float					maxValue ;
		
		int						valueCount ;
		
		int 					motionType ;
	};

#endif // __SKIP_DOC__

}
//--------- LIVE2D NAMESPACE ------------
