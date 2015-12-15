

#pragma once


#ifndef __SKIP_DOC__

#include "../../Live2D.h"
#include "../LDUnmanagedObject.h"
#include "../APageHeader.h"
#include "../AMemoryHolder.h"


//--------- LIVE2D NAMESPACE ------------
namespace live2d 
{

	class MHPageHeaderFixed : public APageHeader 
	{
	public:
		MHPageHeaderFixed();

		int getPageNo(){ return pageNo ; }
		int getPageAmount(){ return pageAmount ; }

		void* getStartPtr(){ return (char*)this + ENTRY_OFFSET - sizeof(AllocHeader) ; }

		virtual void  free_exe( void* ptr ) ;

	protected:
		~MHPageHeaderFixed(){}

	public:
		MHPageHeaderFixed*	nextPage ;		

	//	char*				startPtr ;		
		char*				endPtr ;		
		l2d_uint32			size ;			

		char*				curPtr ;		
		l2d_uint32			rest ;			
		l2d_uint32			pageNo ;		


		//--- static ---
		static int			pageAmount ;	
	};



}
//--------- LIVE2D NAMESPACE ------------

#endif // __SKIP_DOC__
