/**
 *  BReader.h
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */
#ifndef __LIVE2D_B_READER_H__
#define __LIVE2D_B_READER_H__


#ifndef __SKIP_DOC__


#include "../memory/LDObject.h"
#include "ByteBuffer.h"

#include "../type/LDVector.h"

//--------- LIVE2D NAMESPACE ------------
namespace live2d
{
	class AMemoryHolder ;
	
	
	class BReader : public live2d::LDObject 
	{
	public:
		static const int FLAG_READ_AS_USHORT_ARRAY	= 0x1 ;
		static const int FLAG_MALLOC_ON_GPU			= 0x2 ;
	
	
		
		
		
		
		static const int LOAD_OBJECT_INITIAL_CAPACITY = 10000 ; 
	
	
	    
		//BReader( const char * buf , int length , bool deleteBufOnDestructor );
		BReader( const char * buf , int length );
		virtual ~BReader();
		
		
		int getFormatVersion(){ return formatVersion ; }
	
		void setFormatVersion(int version){ formatVersion = version ; }
		
		void rollback( int byteLen ) ;
	
		
		//	FLAG_READ_AS_USHORT_ARRAY	= 0x1 ;
		//	FLAG_MALLOC_ON_GPU			= 0x2 ;
		void * readObject( MemoryParam * memParam , int cno = -1 , int flags = 0 ) ;
		bool readBit() ;
		int readNum(){ return bin.readNum() ; } ;
		float readFloat(){	checkBits() ; return bin.readFloat() ;	}
		double readDouble(){ checkBits() ; return bin.readDouble() ;	}
		long long readLong(){ checkBits() ; return bin.readLong() ;	}
		int readInt() { checkBits() ; return bin.readInt() ;}
		bool readBoolean(){ checkBits() ; return bin.readBoolean() ;}
		char readByte(){ checkBits() ; return bin.readByte() ;}
		short readShort(){ checkBits() ; return bin.readShort() ;	}
	
		
		double* readArrayDouble(MemoryParam* memParam,int *ret_length){ checkBits() ; return bin.readArrayDouble(memParam, ret_length) ;	}
		float* readArrayFloat(MemoryParam* memParam,int *ret_length){ checkBits() ; return bin.readArrayFloat(memParam, ret_length) ;	}
	
		int * readArrayInt(MemoryParam* memParam,int *ret_length){ checkBits() ; return bin.readArrayInt(memParam, ret_length ) ;}
		unsigned short * readArrayIntAsUShort(MemoryParam* memParam,int *ret_length){ checkBits() ; return bin.readArrayIntAsUShort(memParam, ret_length ) ;}
	
		LDVector<double>* readArrayDoubleAsVector(MemoryParam* memParam){ checkBits() ; return bin.readArrayDoubleAsVector(memParam) ;	}
		LDVector<float>* readArrayFloatAsVector(MemoryParam* memParam){ checkBits() ; return bin.readArrayFloatAsVector(memParam) ;	}
		LDVector<int> * readArrayIntAsVector(MemoryParam* memParam){ checkBits() ; return bin.readArrayIntAsVector(memParam) ;}
		
		
		live2d::LDString* readString(MemoryParam* memParam ){ checkBits() ; return bin.readString(memParam) ;	}
		RefString& readStringAsRef(){ checkBits() ; return bin.readStringAsRef() ;	}
	
		
		const char* readCStr(){ checkBits() ; return bin.readCStr() ; }
		char* getCurPtr(){ return bin.getCurPtr() ; }
		void setEndian( bool isBigEndian ) { bin.setEndian(isBigEndian) ; }
		void skip( int bytes ){ bin.skip( bytes ) ; }

		
		
		void setChangeEndian( bool change ) { bin.setChangeEndian( change ) ; }
	
	#if L2D_SAMPLE
		static void TEST_1() ;
		static void TEST_MODEL_LOAD() ;
	#endif
	
		
	private:
		void* read_array_ent( MemoryParam* memParam ,int targetClassNo, int restDimension) ;
	
		void checkBits()
		{
			if( bitCount != 0 ) bitCount = 0 ;
		}
		
		int formatVersion ;
		
		ByteBuffer bin ;
		int bitCount ; //= 0 ;
		int bitBuff ;//= 0 ;
	
		
		LDVector<void*> loadObjects ;
		
	};
}
//------------------------- LIVE2D NAMESPACE -------------

#endif // __SKIP_DOC__

#endif		// __LIVE2D_B_READER_H__
