

#ifndef __LIVE2D_LDALLOCATOR_H__
#define __LIVE2D_LDALLOCATOR_H__

//#include "../Live2D.h"

//--------- LIVE2D NAMESPACE ------------
namespace live2d { 


	
	class LDAllocator 
	{
	public:
		typedef enum {
			MAIN = 0 ,
			GPU 
#ifdef L2D_TARGET_PS4
			,SHADER,
#endif
		} Type ;

	public:
		LDAllocator();
		virtual ~LDAllocator();

		
		virtual void* pageAlloc( unsigned int size , LDAllocator::Type  allocType ) = 0 ;

		
		
		virtual void pageFree( void* ptr , LDAllocator::Type  allocType ) = 0 ;


		
		virtual void init(){}

		
		virtual void dispose(){}

	};

} 
//------------------------- LIVE2D NAMESPACE ------------

#endif
