
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
	class MHBin ;


	//==========================================================
	
	
	
	
	
	//==========================================================
	class MHPageHeaderTmp : public APageHeader 
	{
	public:
		
		MHPageHeaderTmp( MemoryHolderTmp* holder , MHBin* bin , l2d_size_t pageSize , l2d_size_t chunkSize , l2d_size_t pageOffset ) ;

		static l2d_size_t  calcChunkCount( l2d_size_t  pageSize , l2d_size_t  chunkSize ) ;

		
		int getFirstEmptyIndexAndSetFlag(MHBin* bin) ;

		void*  getPtr( int index ) ;

		AllocHeader*  getAllocHeaderPtr( int index ) ;

		int  getIndexOfPtr( void* ptr ) ;

		
		void setFlag( int index , bool flag ) ;

		bool getFlag( int index ) ;

		
		virtual void  free_exe( void* ptr ){ holder->free_exe( this , ptr ) ; }
		

	protected:
		~MHPageHeaderTmp(){}

	public:
		
		//void*					vtable			
		MemoryHolderTmp*		holder ;		
		l2d_uint32				bitmask[3] ;	
												
		l2d_uint16				emptyCount ;	
		l2d_uint16				chunkCount ;	
		l2d_uint32				chunkSize ;		
		l2d_uint32				pageSize ;		
		
	
		MHPageHeaderTmp*		nextPage ;		
		l2d_uint8					pageOffset ;	
		l2d_uint8					binNo ;			

		

		
	} ;

}
//--------- LIVE2D NAMESPACE ------------

#endif // __SKIP_DOC__
