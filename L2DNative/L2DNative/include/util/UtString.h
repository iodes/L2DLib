/**
 *  UtString.h
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#ifndef __LIVE2D_UTSTRING_H__
#define __LIVE2D_UTSTRING_H__



#ifndef __SKIP_DOC__

#include "../type/LDVector.h"



//--------- LIVE2D NAMESPACE ------------
namespace live2d 
{ 
	class UtString 
	{
	public:
		
		
		static live2d::LDString toString( const char * msg , ... ) ;
	
		
		static bool startsWith( const char * text , const char * startWord ) ;
	
		
		static float strToFloat( const char* str , int len , int pos , int* ret_endpos ) ;
	
	private:
		UtString();									
	
		//Prevention of copy Constructor
		UtString( const UtString & ) ;				
		UtString& operator=( const UtString & ) ; 	
		
		~UtString();
	
	};
	
}
//------------------------- LIVE2D NAMESPACE ------------

#endif // __SKIP_DOC__

#endif		// __LIVE2D_UTSTRING_H__
