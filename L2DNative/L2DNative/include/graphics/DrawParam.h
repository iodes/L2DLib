/**
 * DrawParam.h
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */
#ifndef __LIVE2D_DRAWPARAM_H__
#define __LIVE2D_DRAWPARAM_H__


#include "../Live2D.h"
#include "../memory/LDObject.h"
#include "../type/LDVector.h"

#include "../id/DrawDataID.h"

//------------ LIVE2D NAMESPACE ------------
namespace live2d
{ 


	class TextureInfo :public LDObject{
	public:
		TextureInfo();
		float a;
		float r;
		float g;
		float b;

		float scale;
		float interpolate;

		int blendMode;
	};

	
	class DrawParam  : public live2d::LDObject 
	{
	public:
		static const int DEFAULT_FIXED_TEXTURE_COUNT = 32 ;
		
	public:
		DrawParam();
		virtual ~DrawParam();
	
	public:
		
		virtual void setupDraw(){} ;
	
	
        
		virtual void drawTexture( int textureNo , int indexCount , int vertexCount , l2d_index * indexArray
				 , l2d_pointf * vertexArray , l2d_uvmapf * uvArray , float opacity, int colorCompositionType ) = 0 ;
	
	
		
		virtual int generateModelTextureNo() ;
		
		
		virtual void releaseModelTextureNo(int no) ;
	
		
		virtual void setBaseColor( float alpha , float red , float green , float blue ) ;
	
		
		void setCulling( bool culling ){ this->culling = culling ; }
	
		
	    void setMatrix( float* _matrix4x4 )
	    {
	        for( int i = 0 ; i < 16 ; i++ )
			{
				matrix4x4[i] = _matrix4x4[i] ;
			}
	    }

		void setPremultipliedAlpha(bool enable);
		bool isPremultipliedAlpha();

		void setAnisotropy(int n);
		int getAnisotropy();

		void setTextureColor(int textureNo, float r, float g, float b, float a=1);
		void setTextureScale(int textureNo, float scale);
		void setTextureInterpolate(int textureNo, float interpolate);
		void setTextureBlendMode(int textureNo, int mode);

		bool enabledTextureInfo(int textureNo);

		void setpCurrentDrawDataID(DrawDataID* pDrawDataID);
		DrawDataID* getpCurrentDrawDataID();

	protected:
		int 	fixedTexureCount ;
		
		float 	baseAlpha ;
		float 	baseRed ;
		float 	baseGreen ;
		float 	baseBlue ;
	
		bool	culling	;
		float 	matrix4x4[16] ;
		
		bool 	premultipliedAlpha;
		int 	anisotropy;


		LDVector<TextureInfo*> 		texturesInfo;

		DrawDataID*     pCurrentDrawDataID;

	private:
		//Prevention of copy Constructor
		DrawParam( const DrawParam & ) ;			
		DrawParam& operator=( const DrawParam & ) ;
	};
}
//------------ LIVE2D NAMESPACE ------------

#endif		// __LIVE2D_DRAWPARAM_H__

