
#ifndef __LIVE2D_PARAMPIVOTS_H__
#define __LIVE2D_PARAMPIVOTS_H__


#ifndef __SKIP_DOC__


#include "../Live2D.h"
#include "../type/LDVector.h"
#include "../ModelContext.h"
#include "../io/ISerializableV2.h"


//------------ LIVE2D NAMESPACE ------------
namespace live2d
{
	class ParamID ;
	
	
	class ParamPivots : public ISerializableV2 
	{
	public:
		static const int PARAM_INDEX_NOT_INIT = -2 ;	
	
	public:
		ParamPivots();
		virtual ~ParamPivots();

	public:
		virtual void readV2(BReader & br , MemoryParam* memParam ) ;
	
	public:
		
		inline int getParamIndex( int initVersion )
		{ 
			if( this->indexInitVersion != initVersion ) 
			{
				_paramIndex = PARAM_INDEX_NOT_INIT ;
			}
	
			return _paramIndex ;
		}

		
		inline void setParamIndex_(int index , int initVersion )
		{ 
			this->_paramIndex = index ;
			this->indexInitVersion = initVersion ;
		}
	
		
		inline ParamID * getParamID() const { return paramID ; }
	
		
		inline void setParamID(ParamID * v){ paramID = v ; }
	
		
		inline int getPivotCount(){ return pivotCount ; }
	
	
		
		inline l2d_paramf * getPivotValue(){ return pivotValue ; } 
	
		
		inline void setPivotValue(int _pivotCount , l2d_paramf * _values)
		{
			this->pivotCount = _pivotCount ;
			this->pivotValue = _values ; 
		} 
	
		
		inline int getTmpPivotIndex(){ return tmpPivotIndex ; } 
	
		
		inline void setTmpPivotIndex(int v){ tmpPivotIndex = v ; } 
	
		
		inline float getTmpT(){ return tmpT ; } 
	
		
		inline void setTmpT(float t){ tmpT = t ; } 
	
		
#if L2D_SAMPLE
		void DUMP() ;
#endif
	
	
	private:
		//Prevention of copy Constructor
		ParamPivots( const ParamPivots & ) ;			
		ParamPivots& operator=( const ParamPivots & ) ;
	
		
	private:
		//---- Field ----
		int				pivotCount ;
		ParamID*		paramID ;			
		l2d_paramf*		pivotValue ;		
		
		
		int				_paramIndex ;		
		int				indexInitVersion ;	
		
		int				tmpPivotIndex ;		
		float			tmpT ;				
	};
} 
//------------ LIVE2D NAMESPACE ------------

#endif // __SKIP_DOC__

#endif		// __LIVE2D_PARAMPIVOTS_H__
