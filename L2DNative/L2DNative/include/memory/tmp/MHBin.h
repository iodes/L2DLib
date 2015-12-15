
#pragma once


#ifndef __SKIP_DOC__

#include "../../Live2D.h"
#include "../LDObject.h"
#include "../AMemoryHolder.h"
#include "../APageHeader.h"

//--------- LIVE2D NAMESPACE ------------
namespace live2d 
{

	class MemoryHolderTmp ;
	class MHPageHeaderTmp ;


	//==========================================================
	
	
	//==========================================================
	class MHBin
	{
	public:
		MHBin() ;

		void init( l2d_uint16 binNo , l2d_size_t _chunkSize , l2d_size_t _pageSize ) ;
		
		l2d_size_t	getChunkSize( l2d_size_t  malloc_size ) ;

	public:
		l2d_size_t					chunkSize ;			
		l2d_size_t					pageSize ;			
		l2d_uint16				pageChunkCount ;	
		l2d_uint16				binNo ;				
		l2d_uint32				bitmask[3] ;		

		MHPageHeaderTmp*		filledPages ;		
		MHPageHeaderTmp*		curPages ;			
	} ;

}
//--------- LIVE2D NAMESPACE ------------

#endif // __SKIP_DOC__
