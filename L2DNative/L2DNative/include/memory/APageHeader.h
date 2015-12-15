

#pragma once


#ifndef __SKIP_DOC__

#include "LDUnmanagedObject.h"
//#include "../memory/MemoryPage.h"
#include "LDAllocator.h"


//--------- LIVE2D NAMESPACE ------------
namespace live2d 
{


	//==========================================================
	//==========================================================
	class APageHeader 
	//class APageHeader  : public LDUnmanagedObject 
	{
	public:
		const static int ENTRY_OFFSET = 64 ;

		APageHeader(){}

		
		virtual void  free_exe( void* ptr ) = 0 ;


	protected:
		~APageHeader(){}

	};


}
//--------- LIVE2D NAMESPACE ------------

#endif // __SKIP_DOC__
