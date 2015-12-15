/**
 *  FileFormat2.h
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */
#include "../io/BReader.h"

#ifndef __LIVE2D_FILE_FORMAT2_H__
#define __LIVE2D_FILE_FORMAT2_H__


#ifndef __SKIP_DOC__

#include "../memory/LDObject.h"

//--------- LIVE2D NAMESPACE ------------
namespace live2d
{ 
	class ClassDef ;
	
	
	class FileFormat2 : public live2d::LDObject 
	{
	public:
		
		static const int LIVE2D_FORMAT_VERSION_V2_6_INTIAL 		= 6;	
		static const int LIVE2D_FORMAT_VERSION_V2_7_OPACITY 	= 7;	
		static const int LIVE2D_FORMAT_VERSION_V2_8_TEX_OPTION 	= 8;	
		static const int LIVE2D_FORMAT_VERSION_V2_9_AVATAR_PARTS= 9;	
		static const int LIVE2D_FORMAT_VERSION_V2_10_SDK2       = 10 ;//SDK2.0

		
		static const int LIVE2D_FORMAT_VERSION_AVAILABLE	 	= LIVE2D_FORMAT_VERSION_V2_10_SDK2 ;
	
		
		static const int LIVE2D_FORMAT_EOF_VALUE = 0x88888888;			
	
		
	//	static const int FILE_FORMAT_VERSION = 0 ;
		static const int NULL_NO	= 0;		
		static const int ARRAY_NO	= 23;		
		static const int OBJECT_REF = 33;		
	
	public:
		FileFormat2();
		virtual ~FileFormat2();
		
	public:
		
		static ClassDef * getClass( int classNo ) ;
		
		static void * newInstance(MemoryParam* memParam , int classNo) ;

		static bool isSerializable(int classNo) ;

		
		static bool isPrimitive(int classNo){ return ( 2 <= classNo && classNo <= 9 ) ; }
	
		
		static bool isPrimitiveDouble(int classNo){ return classNo == 30 ; } 

		
		static bool isPrimitiveFloat(int classNo){ return classNo == 31 ; }

		
		static bool isPrimitiveInt(int classNo){ return classNo == 29 ; }
	
	};
} 
//------------------------- LIVE2D NAMESPACE ------------

#endif // __SKIP_DOC__

#endif		// __LIVE2D_FILE_FORMAT2_H__
