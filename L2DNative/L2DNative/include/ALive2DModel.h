/**
 *  ALive2DModel.h
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */
#ifndef __LIVE2D_ALIVE_2D_MODE_H__
#define __LIVE2D_ALIVE_2D_MODE_H__


#include "type/LDVector.h"
#include "Live2D.h"
#include "memory/LDObject.h"
#include "ModelContext.h"
#include "id/ParamID.h"
#include "id/DrawDataID.h"
#include "id/PartsDataID.h"

//------------ LIVE2D NAMESPACE ------------
namespace live2d
{ 
	class ModelImpl ;
	class DrawParam ;
	
	
	class ALive2DModel : public LDObject
	{
	public:
		static const int FILE_LOAD_EOF_ERROR = 1 ;			
		static const int FILE_LOAD_VERSION_ERROR = 2 ;		
		
		static int INSTANCE_COUNT ;	
	
	
	public:	
		ALive2DModel() ;
		virtual ~ALive2DModel() ;
	
		
	
		
		float getParamFloat( const char * paramID ) ;
		
		
		void setParamFloat( const char * paramID , float value , float weight = 1.0f ) ;
		
		
		void addToParamFloat( const char * paramID , float value , float weight = 1.0f ) ;
	
		
		void multParamFloat( const char * paramID , float mult , float weight = 1.0f  ) ;
		
		
		inline int getParamIndex( const char * paramID )
		{
			return modelContext->getParamIndex(ParamID::getID(paramID)) ;
		}
	
		
		inline int getParamIndex( ParamID* paramID )
		{
			return modelContext->getParamIndex( paramID ) ;
		}	

		inline float getParamFloat( int paramIndex )
		{
			return modelContext->getParamFloat( paramIndex ) ;
		}
	
		inline void setParamFloat( int paramIndex , float value , float weight = 1.0f)
		{
			if(weight==1)modelContext->setParamFloat( paramIndex , value ) ;
			else modelContext->setParamFloat( paramIndex ,  modelContext->getParamFloat( paramIndex )*(1-weight) + value*weight ) ;
		}
	
		inline void addToParamFloat( int paramIndex, float value , float weight = 1.0f)
		{
			modelContext->setParamFloat( paramIndex , modelContext->getParamFloat( paramIndex ) + value*weight ) ;
		}
	
		inline void multParamFloat( int paramIndex , float mult , float weight = 1.0f)
		{
			modelContext->setParamFloat( paramIndex , modelContext->getParamFloat( paramIndex )*(1.0f + (mult - 1.0f)*weight ) ) ;
		}
	
		
		void loadParam() ;

		
		void saveParam() ;
	
		
		virtual void init() ;
	
		
		virtual void update() ;

		
		virtual void draw()  ;
		
		
		void setPartsOpacity( const char *partsID , float opacity ) ;
		void setPartsOpacity( int partsIndex , float opacity ) ;

		
		float getPartsOpacity( const char *partsID ) ;
		float getPartsOpacity( int partsIndex ) ;
		
		
		void setupPartsOpacityGroup_alphaImpl( const char* paramGroup[] , float deltaTimeSec ) ;
	
		
		void setModelImpl(ModelImpl* m) ;

		
		ModelImpl* getModelImpl() ;
	
		
		ModelContext * getModelContext(){ return modelContext ; }

		
		int getErrorFlags(){ return Live2D::getError() ; }
		
		
		virtual int generateModelTextureNo() ;
		
		
		virtual void releaseModelTextureNo(int no) ;
	
		
		float getCanvasWidth() ;

		
		float getCanvasHeight() ;
	
		
		virtual DrawParam* getDrawParam(){ return NULL ; }
	
		
		virtual int getDrawDataIndex( const char * drawDataID )
		{
			return modelContext->getDrawDataIndex( DrawDataID::getID(drawDataID)) ;
		}
	
		
		virtual IDrawData* getDrawData( int drawIndex )
		{
			return modelContext->getDrawData( drawIndex ) ;
		}
		
		
		virtual l2d_pointf* getTransformedPoints( int drawIndex , int*pointCount) ;
		virtual l2d_index* getIndexArray( int drawIndex , int*polygonCount) ;
	
		
		
		void updateZBuffer_TestImpl( float startZ , float stepZ )
		{
			modelContext->updateZBuffer_TestImpl( startZ , stepZ ) ;
		}
	
		
		inline int getPartsDataIndex( const char * partsID )
		{
			return modelContext->getPartsDataIndex(PartsDataID::getID(partsID)) ;
		}
		
		
		inline int getPartsDataIndex( PartsDataID* partsID )
		{
			return modelContext->getPartsDataIndex( partsID ) ;
		}

		
		void setPremultipliedAlpha(bool b);
		bool isPremultipliedAlpha();
		
		void setAnisotropy(int n);
		int getAnisotropy();


	#if L2D_ALPHA_IMPL_LAYOUT
		
		
		//{ x , y , anchorX , anchorY , scaleX , scaleY }
		float* getLayout_alphaImpl(){ return layout_alphaImpl ; }
	#endif
		
	#ifdef L2D_DEBUG
		void dump() ;
	#endif
	
	protected:
		//------------ static method ------------
		
		static l2d_uint32 loadModel_exe( ALive2DModel *ret , const LDString & filepath ) ;
		static l2d_uint32 loadModel_exe( ALive2DModel *ret , const void * buf , int bufSize ) ;
	
	private:
		//Prevention of copy Constructor
		ALive2DModel( const ALive2DModel & ) ;				
		ALive2DModel& operator=( const ALive2DModel & ) ;
	
		
	protected:
		//------------ field ------------
		ModelImpl*			modelImpl ;						
		ModelContext*		modelContext ;					
//		int					errorFlags ;					
	
	#if L2D_ALPHA_IMPL_LAYOUT
		float layout_alphaImpl[6] ;//{ x , y , anchorX , anchorY , scaleX , scaleY }
	#endif
		
	};

} 
//------------ LIVE2D NAMESPACE ------------

#endif		// __LIVE2D_ALIVE_2D_MODE_H__
