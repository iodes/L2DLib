/**
 *  DDTexture.h
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */
#ifndef __LIVE2D_DDTEXTURE_H__
#define __LIVE2D_DDTEXTURE_H__


#ifndef __SKIP_DOC__

#include "../Live2D.h"
#include "IDrawData.h"
#include "../param/PivotManager.h"
#include "IDrawContext.h"

#ifdef L2D_TARGET_D3D
# include <d3dx9.h>
# include "../graphics/DrawParam_D3D.h"
#endif

#ifdef L2D_TARGET_PS4
#include <gnmx.h>
#endif

//------------ LIVE2D NAMESPACE ------------
namespace live2d
{ 
	class DDTextureContext ;
	
	
	
	class DDTexture : public IDrawData
	{
	public:
		static const int OPTION_FLAG_BARCODE_KANOJO_COLOR_CONVERT = 0x1 ;
		
		static const int MASK_COLOR_COMPOSITION = 0x1E ;//011110 
	
		static const int COLOR_COMPOSITION_NORMAL  = 0 ;
		static const int COLOR_COMPOSITION_SCREEN  = 1 ;
		static const int COLOR_COMPOSITION_MULTIPLY= 2 ;
	
		static int INSTANCE_COUNT ;
	
	public:
		DDTexture() ;
		virtual ~DDTexture(void) ;
		
	public:
		virtual void readV2(BReader & br , MemoryParam* memParam ) ;

		void initDirect(MemoryParam* memParam) ;
	
		
		void setTextureNo(int no){ this->textureNo = no ; }
	
		
		int getTextureNo(){ return this->textureNo ; }
		
		
		l2d_uvmapf * getUvMap(){ return this->uvmap ; }
		
		
		int getNumPoints(){ return this->numPts ; }
	
		
		int getNumPolygons(){ return this->numPolygons ; }
		
		virtual IDrawContext* init(ModelContext &mdc) ;
		
		virtual void setupInterpolate(ModelContext &mdc , IDrawContext* cdata ) ;
		
		virtual void setupTransform(ModelContext &mdc , IDrawContext* cdata ) ;
	
		virtual void draw( DrawParam & dp , ModelContext &mdc , IDrawContext* cdata ) ;
	
	#ifdef L2D_TARGET_D3D
	
		void setupBufD3D( DrawParam_D3D& dpD3D , ModelContext &mdc , DDTextureContext* cdata ) ;
	
		virtual void deviceLost( IDrawContext* drawContext ) ;
	#endif
		
		
		virtual int getType(){ return TYPE_DD_TEXTURE ; }
	
		int getOptionFlag(){ return this->optionFlag ; }
	
		virtual void setZ_TestImpl( ModelContext &mdc , IDrawContext* _cdata , float z ) ;
	
		l2d_index*  getIndexArray(int* polygonCount);

	#if AVATAR_OPTION_A
		
		int getOption_KanojoColor(){ return this->optionKanojoColor ; }
	
	#endif
	
	#ifdef L2D_DEBUG
		virtual void dump() ;
	#endif
	
	private:
		// Prevention of copy Constructor
		DDTexture( const DDTexture & ) ;				
		DDTexture& operator=( const DDTexture & ) ;		
	
	private:
		int						textureNo ;				
		int						numPts ;				
		int						numPolygons ;			
		int						optionFlag ;			
		
		
	#if AVATAR_OPTION_A
		int						optionKanojoColor ;		
	#endif
		
		l2d_index *				indexArray ;			
	
		
		
		
		LDVector<l2d_paramf*>*	pivotPoints ;			
		l2d_uvmapf *			uvmap ;					
		int						colorCompositionType ;	
		bool					culling ;				// 1.0beta3
	};
	
	
	class DDTextureContext : public IDrawContext 
	{
	public:
		DDTextureContext(IDrawData* src) ;
		virtual ~DDTextureContext() ;
		
	public:		
		
		
		l2d_pointf* getTransformedPoints( int* pointCount ) ;
	
	public:		
		int 				tmpBaseDataIndex ;		
		l2d_pointf * 		interpolatedPoints ;	
		l2d_pointf * 		transformedPoints ;		
		l2d_pointf * 		drawPoints ;			
		
		unsigned char 		not_updated_count ;		
		
	#ifdef L2D_TARGET_D3D
		LPDIRECT3DVERTEXBUFFER9 		pUvBuf ; 
		LPDIRECT3DINDEXBUFFER9 			pIndexBuf ; 
	#endif

	#ifdef L2D_TARGET_PS4
		bool initializedBuffer;
		float* color;
		sce::Gnm::Buffer buffers[2];//position , textureUV 
	#endif
	} ;
} 
//------------ LIVE2D NAMESPACE ------------

#endif // __SKIP_DOC__

#endif	// __LIVE2D_DDTEXTURE_H__

