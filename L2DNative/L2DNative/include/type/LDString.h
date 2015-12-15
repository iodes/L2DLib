/**
 *  LDString.h
 * 
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#ifndef __LIVE2D_LD_STRING_H__
#define __LIVE2D_LD_STRING_H__


#include "../memory/LDObject.h"
#include "../io/RefString.h"
# include <string.h>


#define l2d_string			live2d::LDString


//--------- LIVE2D NAMESPACE ------------
namespace live2d 
{ 
	
	class LDString  : public live2d::LDObject 
	{
	public:
		// Constructor
		LDString();
		LDString( const char * s , MemoryParam* memParam = NULL ) ;
		LDString( const char * s , int length , MemoryParam* memParam = NULL) ;
		LDString( const RefString& refStr , MemoryParam* memParam = NULL) ;
		LDString( const LDString & s , MemoryParam* memParam = NULL) ;
		LDString( const char * s , int length , bool useptr , MemoryParam* memParam = NULL) ;
	
		// Destructor
		~LDString();
	
	
	public:
	
		
		LDString& operator=( const LDString & s ) ; 
		LDString& operator=( const char* c ) ;
	
		
		bool operator==( const RefString & s ) const ;
		bool operator==( const LDString & s ) const ;
		bool operator==( const char* c ) const ;
	
		
		bool operator<( const LDString & s ) const ;
		bool operator<( const char* c ) const ;
	
		
		bool operator>( const LDString & s ) const ;
		bool operator>( const char* c ) const ;
	
		bool equals( const RefString& refStr ) const 
		{
			if( refStr.length != this->_length ) return false ;
			const char *c1 = this->_ptr ;
			const char *c2 = refStr.ptr_not_zero_end ;
			
			for( int i = this->_length -1 ; i >= 0 ; --i )
			{
				if( c1[i] != c2[i] ) return false ;
			}
			return true ;
		}
	
		
		LDString operator+( const LDString & s ) const ;
		LDString operator+( const char* s ) const ;
	
		
		LDString& operator+=( const LDString & s ) ;
		LDString& operator+=( const char* s ) ;
	
		// 
		LDString& append( const char* p , int length ) ;
		LDString& append( int count , const char p ) ;
	
		
		unsigned int length() const {	return _length ; }
	
		
		int size() const {	return _length ; }
	
		
		const char* c_str() const 
		{ 
			return _ptr ; 
		}
	
		
		void clear() ;
	
		
		int getHashcode()
		{
			if( _hashcode == -1 ) _hashcode = calcHashcode( this->_ptr , this->_length ) ;
			return _hashcode ;
		}
	
	protected:
		void copy( const char* ptr , int length ) ;

		void init( const char * s , int length , bool useptr ) ;
		int calcHashcode( const char* p1 , int length ) ;
	
	private:
		static const int DEFAULT_SIZE = 10 ;
	
	private:
		char * 				_ptr ;					
		int 				_length ;				
		int 				_hashcode ;				//
	
		int 				instanceNo ;			
		static int 			totalInstanceNo ;		
	
		MemoryParam* 		memParam ;				//
	};

} 
//------------------------- LIVE2D NAMESPACE -----------

#endif	// __LIVE2D_LD_STRING_H__
