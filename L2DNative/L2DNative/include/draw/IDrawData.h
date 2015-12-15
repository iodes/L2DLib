/**
 *  IDrawData.h
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#ifndef __LIVE2D_IDRAWDATA_H__
#define __LIVE2D_IDRAWDATA_H__


#ifndef __SKIP_DOC__

#include "../Live2D.h"
#include "../io/ISerializableV2.h"
#include "../id/BaseDataID.h"
#include "IDrawContext.h"
#include <stdio.h>


//------------ LIVE2D NAMESPACE ------------
namespace live2d
{
	class DrawDataID ;
	class ModelContext ;
	class PivotManager ;
	class DrawParam ;

	
	class IDrawData : public ISerializableV2
	{
	public:
		static const int BASE_INDEX_NOT_INIT 	= -2 ;
		static const int DEFAULT_ORDER 			= 500 ;
		static const int TYPE_DD_TEXTURE 		= 2 ;
	public:	
		IDrawData();
		virtual ~IDrawData();
	
		virtual void readV2(BReader & br , MemoryParam* memParam ) ;
		
		
		inline BaseDataID * getTargetBaseDataID(){ return targetBaseDataID ; } 
		inline void setTargetBaseDataID(BaseDataID *id){ targetBaseDataID = id ; } 
	
		bool needTransform()
		{ 
			return ( targetBaseDataID 
					&& (targetBaseDataID != BaseDataID::DST_BASE_ID() ) ) ;
		}
	
		
		inline DrawDataID * getDrawDataID(){ return drawDataID ; } 

		
		inline void setDrawDataID( DrawDataID *id ){ drawDataID = id ; } 
	
		
		inline float getOpacity( ModelContext &mdc , IDrawContext* cdata ){ return cdata->interpolatedOpacity ; }
	
		
		inline int getDrawOrder(ModelContext &mdc , IDrawContext* cdata ){ return cdata->interpolatedDrawOrder ; }
		
		inline void setDrawOrder(LDVector<int>* orders )
		{
			for( int i = (int)orders->size()-1 ; i >= 0  ; --i )
			{
				int order = (*orders)[i] ;

				if( order < totalMinOrder ) 		totalMinOrder = order ;
				else if( order > totalMaxOrder ) 	totalMaxOrder = order ;
			}
		} 
	
		
		inline static int getTotalMinOrder(){ return totalMinOrder ; } 
		inline static int getTotalMaxOrder(){ return totalMaxOrder ; } 
		
		
		
		virtual IDrawContext* init(ModelContext &mdc) = 0;
		
		
		virtual void setupInterpolate(ModelContext &mdc , IDrawContext* cdata ) ;
		
		
		virtual void setupTransform(ModelContext &mdc , IDrawContext* cdata ) ;
	
		
		virtual void draw( DrawParam & dp , ModelContext &mdc , IDrawContext* cdata ) = 0 ;
	
		
		virtual int getType() ;
		
		
		virtual void deviceLost( IDrawContext* drawContext ) {}
	
		virtual void setZ_TestImpl( ModelContext &mdc , IDrawContext* _cdata , float z ){}
	
#ifdef L2D_DEBUG
		virtual void dump() = 0 ;
#endif
	
	private:
		//Prevention of copy Constructor
		IDrawData( const IDrawData & ) ;
		IDrawData& operator=( const IDrawData & ) ; 	
	
	private:
		static int			totalMinOrder ;		
		static int			totalMaxOrder ;		
	
	protected:
		PivotManager *		pivotManager ;
		int 				averageDrawOrder ;	
	
	private:
		DrawDataID *		drawDataID ;		
		BaseDataID *		targetBaseDataID ;	
		LDVector<int>*		pivotDrawOrder ;	
		LDVector<float>*	pivotOpacity ;		
	
		bool				dirty ;				
	};
}
//------------ LIVE2D NAMESPACE ------------

#endif // __SKIP_DOC__

#endif	// __LIVE2D_IDRAWDATA_H__
