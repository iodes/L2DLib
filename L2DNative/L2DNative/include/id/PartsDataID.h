/**
 *  PartsDataID.h
 * 
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */
#ifndef __LIVE2D_PARTS_DATA_ID_H__
#define __LIVE2D_PARTS_DATA_ID_H__


#include "../Live2D.h"
#include "ID.h"

//------------ LIVE2D NAMESPACE ------------
namespace live2d
{ 
	
	class PartsDataID  : public ID
	{
	public:
		const static int L2D_PARTS_ID_INITIAL_CAPACITY = 64 ;
		
	public:
		
		
		
		static PartsDataID * getID(const live2d::LDString &str ) ;

		static PartsDataID * getID(  const RefString& refStr ) ;
	
		
		static void releaseStored_notForClientCall() ;
	
	public:
		
		const char * toChar(){ return id.c_str() ; }
	
	private:	
		// Constructor
		PartsDataID() ;									
		PartsDataID( const char* str ) ;					
		PartsDataID(const live2d::LDString &str );		

		//Prevention of copy Constructor	
		PartsDataID( const RefString& refStr ) ;		
		PartsDataID( const PartsDataID & ) ;			
		PartsDataID& operator=( const PartsDataID & ) ; 

		// Destructor
		virtual ~PartsDataID();
		
	private:	
		//------------ static ------------
		static LDVector<PartsDataID*>*		idlist ;
		
	private:	
		//------------ this ------------
		live2d::LDString 					id ;
	};
}
//------------ LIVE2D NAMESPACE ------------

#endif		// __LIVE2D_PARTS_DATA_ID_H__
