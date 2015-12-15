/**
 *  ModelContext.h
 * 
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */
#ifndef __LIVE2D_MODEL_CONTEXT_H__
#define __LIVE2D_MODEL_CONTEXT_H__


#include "Live2D.h"
#include "memory/LDObject.h"
#include "type/LDVector.h"
#include "DEF.h"

#if L2D_VERBOSE
#include "util/UtDebug.h"
#endif

//------------ LIVE2D NAMESPACE ------------
namespace live2d
{ 
	
	class ParamID ;
	class BaseDataID ;
	class PartsDataID ;
	class DrawDataID ;
	class IBaseData ;
	class IDrawData ;
	class PartsData ;
	class ALive2DModel ;
	class DrawParam ;
	class IBaseContext ;
	class IDrawContext ;
	class PartsDataContext ;
		
	#define _PARAM_FLOAT_MIN_ (-1000000) 
	#define _PARAM_FLOAT_MAX_ ( 1000000) 
	
	
	class ModelContext : public live2d::LDObject 
	{
	public:
		static const unsigned short NOT_USED_ORDER ; 
		static const unsigned short NO_NEXT ; 
	
	
	public:
		ModelContext(ALive2DModel *model) ;
		virtual ~ModelContext(void) ;
	
	public:
		
		void release() ;
		
		
		void init() ;
	
		
		MemoryParam*  getMemoryParam(){ return memoryManagement ; }
	
		
		inline int getInitVersion() const { return initVersion ; }
	
		inline bool requireSetup() const { return needSetup ; }
		
		
		bool update() ;
	
		
		void draw(DrawParam &dp) ;
	
	
				
		inline bool isParamUpdated( int paramIndex ) const { 
# if L2D_FORCE_UPDATE
			return true ;
# else
			return (*updatedFloatParamFlagsPtr)[ paramIndex ] == PARAM_UPDATED ; 
# endif
		}

		
		int getParamIndex( ParamID * paramID )   ;

		
		int getBaseDataIndex( BaseDataID * baseID ) ;

		
		int getPartsDataIndex( PartsDataID * partsID ) ;

		
		int getDrawDataIndex( DrawDataID * drawDataID ) ;
	
		inline unsigned short * getTmpPivotTableIndicesRef(){ return tmpPivotTableIndices_short ; }
		inline float * getTmpT_ArrayRef(){ return tmpT_array ; }
		
	
		
		int addFloatParam( ParamID * id , l2d_paramf value , l2d_paramf min , l2d_paramf max ) ;
	
	
		void setBaseData( unsigned int baseDataIndex , IBaseData * baseData ) ;
	
	
		void setParamFloat( unsigned int paramIndex , l2d_paramf value ) ;
	
		float getParamMax( unsigned int paramIndex ){ return (*floatParamMaxListPtr)[paramIndex] ; }
		float getParamMin( unsigned int paramIndex ){ return (*floatParamMinListPtr)[paramIndex] ; }
		
		
		void loadParam() ;

		
		void saveParam() ;
	
		
		void setPartsOpacity( int partIndex , float opacity ) ;
	
		
		float getPartsOpacity( int partIndex ) ;
		
	
		
		inline IBaseData* getBaseData( unsigned int baseDataIndex )
		{

	# if L2D_RANGE_CHECK		
			if( baseDataIndex >= baseDataListPtr->size() )
			{
	
				L2D_THROW( "out of range ModelDrawContext@getBaseData()" ) ;
			}
	# endif
			return (*baseDataListPtr)[ baseDataIndex ] ;
		}

		
		inline IDrawData* getDrawData( unsigned int drawDataIndex )
		{
	# if L2D_RANGE_CHECK		
			if( drawDataIndex >= (*drawDataListPtr).size() )
			{
	
				L2D_THROW( "out of range ModelDrawContext@getBaseData()" ) ;
			}
	# endif
			return (*drawDataListPtr)[ drawDataIndex ] ;
		}
	
		
		inline IBaseContext* getBaseContext( unsigned int baseDataIndex )
		{
			return (*baseContextListPtr)[ baseDataIndex ] ;
		}

		
		inline IDrawContext* getDrawContext( unsigned int drawDataIndex )
		{
			return (*drawContextListPtr)[ drawDataIndex ] ;
		}

		
		inline PartsDataContext* getPartsContext( unsigned int partsDataIndex )
		{
			return (*partsContextListPtr)[ partsDataIndex ] ;
		}

		
		inline int getBaseDataCount(){	return (int)baseDataListPtr->size() ; }

		
		inline int getDrawDataCount(){	return (int)drawDataListPtr->size() ; }

		
		inline int getPartsDataCount(){	return (int)partsDataListPtr->size() ; }
		
		
		inline l2d_paramf getParamFloat( unsigned int paramIndex )
		{

	# if L2D_RANGE_CHECK
			if( paramIndex >= floatParamListPtr->size() )
			{
	
				L2D_THROW( "out of range ModelDrawContext@getParamFloat()" ) ;
			}
	# endif
			return (*floatParamListPtr)[ paramIndex ] ;
		}
		
		
		void deviceLost( ) ;
		
		
		void updateZBuffer_TestImpl( float startZ , float stepZ ) ;
	
	#if L2D_SAMPLE
		void DUMP_PARAMS() ;
	#endif
	
	
	private:
		enum { PARAM_NOT_UPDATED = 0,	PARAM_UPDATED	};
		
		//Prevention of copy Constructor
		ModelContext( const ModelContext & ) ;				
		ModelContext& operator=( const ModelContext & ) ; 	
		
	private:	
		bool 							needSetup ;						
		ALive2DModel * 					model ;							
	
	
		int 							initVersion ;					
		
		LDVector<ParamID *>*			floatParamIDListPtr ;			
		LDVector<l2d_paramf>*			floatParamListPtr ;				
		LDVector<l2d_paramf>*			lastFloatParamListPtr ;			
		
		//-- 
		LDVector<l2d_paramf>*			floatParamMinListPtr ;			
		LDVector<l2d_paramf>*			floatParamMaxListPtr ;			
		
		LDVector<l2d_paramf>*			savedFloatParamListPtr ;		
	
		
		LDVector<char>*					updatedFloatParamFlagsPtr ;		
		
		
		
		
		
		LDVector<IBaseData*>*			baseDataListPtr ;				
		
		
		LDVector<IDrawData*>*			drawDataListPtr ;				
	
		LDVector<PartsData*>*			partsDataListPtr ;				
		
		
		LDVector<IBaseContext*>*		baseContextListPtr ;			
		LDVector<IDrawContext*>*		drawContextListPtr ;			
		LDVector<PartsDataContext*>*	partsContextListPtr ;			
	
		
		
		LDVector<unsigned short>*		orderList_firstDrawIndexPtr ;	
		LDVector<unsigned short>*		orderList_lastDrawIndexPtr  ;	
		
		
		LDVector<unsigned short>*		nextList_drawIndexPtr ;			
		
		
		unsigned short 					tmpPivotTableIndices_short [DEF::PIVOT_TABLE_SIZE] ;	
		float 							tmpT_array[DEF::MAX_INTERPOLATION*2] ;					
	
		MemoryParam*					memoryManagement ;
		AMemoryHolder*					memoryHolderFixedMain ;
		AMemoryHolder*					memoryHolderFixedGPU ;
		
	};
}
//------------ LIVE2D NAMESPACE ------------

#endif		// __LIVE2D_MODEL_CONTEXT_H__
