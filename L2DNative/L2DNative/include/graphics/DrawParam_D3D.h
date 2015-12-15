/**
 * DrawParam_D3D.h
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */
#ifndef __LIVE2D_DRAWPARAM_D3D_H__
#define __LIVE2D_DRAWPARAM_D3D_H__

#ifndef __SKIP_DOC__

#include "Live2D.h"

#ifdef L2D_TARGET_D3D

#include "type/LDVector.h"
#include <d3dx9.h>
#include "graphics/DrawParam.h"
#include "type/LDMap.h"//hoge
//------------ LIVE2D NAMESPACE ------------
namespace live2d
{ 
	
	typedef struct LIVE2D_D3D_VERTEX
	{
		D3DXVECTOR3 Position;
	} LIVE2D_D3D_VERTEX;


	
	typedef struct LIVE2D_D3D_UV
	{
		D3DXVECTOR2 Texture;
	} LIVE2D_D3D_UV;


	
	class DrawParam_D3D : public DrawParam 
	{
	public:
		static const int INITIAL_VERTEX_COUNT = 300;		
		static const int INITIAL_INDEX_COUNT = 150;			
		
		//--- error / Direct3D is 6000.. ---
		static const int ERROR_D3D_CREATE_VERTEX_BUFFER	= 6001;
		static const int ERROR_D3D_LOCK_VERTEX_BUFFER	= 6002;
		static const int ERROR_D3D_CREATE_INDEX_BUFFER	= 6003;
		static const int ERROR_D3D_LOCK_INDEX_BUFFER	= 6004;
		static const int ERROR_D3D_DEVICE_NOT_SET		= 6005;
		
	public:
		DrawParam_D3D();
		virtual ~DrawParam_D3D();
		
	public:
		virtual void deleteTextures() ;

		virtual void setupDraw() ;

		void drawTextureD3D( int textureNo , int indexCount , int vertexCount , l2d_index * indexArray 
								, l2d_pointf * vertexArray , l2d_uvmapf * uvArray , float opacity
								, LPDIRECT3DVERTEXBUFFER9 pUvBu 
								, LPDIRECT3DINDEXBUFFER9 pIndexBuf 
								, int colorCompositionType 
							 ) ;

		void drawTexture( int textureNo , int indexCount , int vertexCount , l2d_index * indexArray 
			, l2d_pointf * vertexArray , l2d_uvmapf * uvArray , float opacity
			, int colorCompositionType 
			) ;

	
		void setTexture( int modelTextureNo , LPDIRECT3DTEXTURE9 textureNo ) ;

		
		virtual int generateModelTextureNo() ;
		
		
		virtual void releaseModelTextureNo(int no) ;
		
		
		int getErrorD3D_tmp()
		{
			int ret = error ;
			error = 0 ;
			return ret ;
		}


		
		void setErrorD3D_tmp( int error ){ this->error = error ; }
		

		
		void setDevice( LPDIRECT3DDEVICE9 device ){ this->pd3dDevice = device ; }

		
		LPDIRECT3DDEVICE9 getDevice(){ return pd3dDevice ; }


		
		void setUpBufD3D_UV(int vertexCount_, l2d_uvmapf*	uvArray);

		
		void setUpBufD3D_Index(int indexCount, l2d_index* indexArray);





		
		void deviceLost( ) ;


		
		static HRESULT createUvBuffer(    LPDIRECT3DDEVICE9 pd3dDevice , unsigned int length , IDirect3DVertexBuffer9**  ppVerterxBuffer ) ;
		static HRESULT createIndexBuffer( LPDIRECT3DDEVICE9 pd3dDevice , unsigned int length , IDirect3DIndexBuffer9**   ppIndexBuffer ) ;


	private:
		
		DrawParam_D3D( const DrawParam_D3D & ) ;
		DrawParam_D3D& operator=( const DrawParam_D3D & ) ; 
		
	private:
		//--------- fields ------------
		LDVector<LPDIRECT3DTEXTURE9>	textures ;			

		LPDIRECT3DDEVICE9				pd3dDevice ;		
		LPDIRECT3DVERTEXBUFFER9			pVertexBuf ;		
		int								vertexBuf_length ;	

		IDirect3DVertexDeclaration9*	pDec ;				

		live2d::LDMap<DrawDataID*,LPDIRECT3DVERTEXBUFFER9>  pUVBufMap;
		live2d::LDMap<DrawDataID*,LPDIRECT3DINDEXBUFFER9>   pIndexBufMap;

		live2d::LDVector<DrawDataID*>                       pDrawDataIDs;


		//-- error
		int								error ;				

	};

} 
//------------ LIVE2D NAMESPACE ------------
#endif// L2D_TARGET_D3D

#endif // __SKIP_DOC__

#endif		// __LIVE2D_DRAWPARAM_D3D_H__
