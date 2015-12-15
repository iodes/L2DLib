/**
 *  UtSystem.h
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#ifndef __LIVE2D_UTSYSTEM_H__
#define __LIVE2D_UTSYSTEM_H__

#include "../Live2D.h"

//--------- LIVE2D NAMESPACE ------------
namespace live2d
{ 
	
	
	
	class UtSystem 
	{
	public:
		
		static bool isBigEndian() ;
	
		
		static l2d_int64 getTimeMSec() ;
	
		//-------------------------------------------------------------
		
		
		
		
		
		
		//-------------------------------------------------------------
		
		static l2d_int64 getUserTimeMSec() ;
	
		
		static void setUserTimeMSec(l2d_int64 t) ;
		
		
		
		static l2d_int64 updateUserTimeMSec() ;
	

		
		static void resetUserTimeMSec();
	

		static void exit(int code) ;
		
	private:
		UtSystem();		
		
		// Prevention of copy Constructor							
		UtSystem( const UtSystem & ) ;				
		UtSystem& operator=( const UtSystem & ) ; 	
		
		~UtSystem();
			
		
	private:
		static const int 	USER_TIME_AUTO = -1 ;	
		static long long 	userTimeMSec ;			//
		
	};
}
//------------------------- LIVE2D NAMESPACE ------------

#endif		// __LIVE2D_UTSYSTEM_H__
