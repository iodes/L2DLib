/**
 *  MemoryInfoSet.h
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#pragma once


#ifndef __SKIP_DOC__

#include "../../Live2D.h"

#ifndef NULL
#  define NULL    0
#endif


//--------- LIVE2D NAMESPACE ------------
namespace live2d 
{

	class AMemoryHolder ;
	class MemoryParam ;
	class MemoryInfo ;


	//******************************************************
	class MemoryInfoSet 
	{
		friend class UtMemory ;
		friend class MemoryInfo ;
	public:
		MemoryInfoSet(const char* setName);
		~MemoryInfoSet(void);

		void dump(const char* message = NULL ) ;
		void dumpList( MemoryInfo *info ) ;

		void addMemoryInfo( void* ptr , MemoryParam* owner , l2d_size_t size , const char* filename , int lineno ) ;
		void removeMemoryInfo( void* ptr ) ;

		int getMallocTotal(){ return mallocTotal ; }	
		int	getRestCount(){ return restCount ; }		
		int	getTotalMemory(){ return totalMemory ; }	

		int getCurMemory(){ return curMemory ; }		
		int getPeakMemory(){ return peakMemory ; }		

	private:
		const char*		setName ;

		int				mallocTotal ;			
		int				restCount ;				
		int				totalMemory ;			
		int				curMemory ;				
		int				peakMemory ;			

		MemoryInfo*		usingMemoryInfo ;		
		MemoryInfo*		lastUsingMemoryInfo ;	
		MemoryInfo*		freeMemoryInfo ;		
		MemoryInfo*		lastFreeMemoryInfo ;	
	};
}
//--------- LIVE2D NAMESPACE ------------

#endif // __SKIP_DOC__

