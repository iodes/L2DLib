
#ifndef __LIVE2D_BASE_DATA_ID_H__
#define __LIVE2D_BASE_DATA_ID_H__


#include "../Live2D.h"
#include "../type/LDVector.h"
#include "ID.h"

//------------ LIVE2D NAMESPACE ------------
namespace live2d
{
	
	class BaseDataID : public ID
	{
	public:
		const static int L2D_BASEDATA_ID_INITIAL_CAPACITY = 128 ;
	
	public:
	
		
		
		
		static BaseDataID * getID(const live2d::LDString &str ) ;
	
		static BaseDataID * getID(  const RefString& refStr ) ;
	
		static BaseDataID * DST_BASE_ID()
		{
			if( dstBaseId == NULL )
			{
				dstBaseId = getID("DST_BASE");
			}
			return dstBaseId ;
		}
	
		
		
		static void releaseStored_notForClientCall() ;
	
	public:
		
		const char * toChar(){ return id.c_str() ; }
		
	private:	
		BaseDataID() ;									
		BaseDataID(const live2d::LDString &str );		
		BaseDataID( const char* str ) ;					
		BaseDataID( const RefString& refStr ) ;			
	
		//Prevention of copy Constructor
		BaseDataID( const BaseDataID & ) ;				
		BaseDataID& operator=( const BaseDataID & ) ; 	
	
	
		virtual ~BaseDataID();
		
	private:
		static LDVector<BaseDataID*>* 		idlist_BaseDataID ;
		static BaseDataID * 				dstBaseId ;
		
	private:
		live2d::LDString 					id ;				
	};
	
}

#endif		// __LIVE2D_BASE_DATA_ID_H__
//------------ LIVE2D NAMESPACE ------------

