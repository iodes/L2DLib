


#pragma once


#ifndef __SKIP_DOC__

#include "LDUnmanagedObject.h"
#include "fixed/MemoryHolderFixed.h"
#include "tmp/MemoryHolderTmp.h"
#include "LDAllocator.h"

//--------- LIVE2D NAMESPACE ------------
namespace live2d 
{


	class MemoryPage ;

	//----------------------------------------
	class MemoryStackEnt : public LDUnmanagedObject
	{
		friend class MemoryParam ;
	public:
		MemoryStackEnt() : nextEnt(NULL), allocType(0) , align(0) , holder(NULL)
		{
		}

		virtual ~MemoryStackEnt(){}

	private:
		MemoryStackEnt*		nextEnt ;

		int					allocType ;
		int					align ;
		AMemoryHolder*		holder ;
	} ;


	//----------------------------------------
	class MemoryParam : public LDObject
	{
	public:

	//	MemoryParam();
		MemoryParam(AMemoryHolder* main , AMemoryHolder* gpu);
		
		virtual ~MemoryParam() ;

		
		LDAllocator::Type  setAllocType( LDAllocator::Type  allocType )
		{
			LDAllocator::Type  ret = this->curAllocType	 ;
			this->curAllocType	= allocType ;
			this->curMemoryHolder	= getMemoryHolder( allocType ) ;	
			return ret ;
		}

		
		int  setAllocAlign( int align )
		{
			int ret = this->curAlign ;
			this->curAlign = align ;
			return ret ;
		}

		
		LDAllocator::Type getAllocType( )
		{
			return this->curAllocType ;
		}

		
		int  getAllocAlign( )
		{
			return curAlign ;
		}


		void* malloc_exe( l2d_size_t size  )
		{
			return curMemoryHolder->malloc_exe( size , curAlign ) ;
		}

		AMemoryHolder*  getCurMemoryHolder()
		{
			return curMemoryHolder ;
		}

		AMemoryHolder*  getMemoryHolder( LDAllocator::Type  allocType ) ;

		void clear() ;

		
		void setMemoryHolderMain(AMemoryHolder*	h)
		{
			this->memoryHolderMain = h ;
		}

		
		void setMemoryHolderGPU(AMemoryHolder*	h)
		{
			this->memoryHolderGPU = h ;
		}

		void checkMemory()
		{
			memoryHolderMain->healthCheck();
			memoryHolderGPU->healthCheck();
		}
	private:

		AMemoryHolder*			curMemoryHolder ;
		LDAllocator::Type		curAllocType ;
		int						curAlign ;

		AMemoryHolder*			memoryHolderMain ;	
		AMemoryHolder*			memoryHolderGPU ;	

	};


}
//--------- LIVE2D NAMESPACE ------------

#endif // __SKIP_DOC__
