/**
 *  UtInterpolate.h
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */


#ifndef __LIVE2D_UTINTERPOLATE_H__
#define __LIVE2D_UTINTERPOLATE_H__


#ifndef __SKIP_DOC__

#include "../Live2D.h"
#include "../type/LDVector.h"



//------------ LIVE2D NAMESPACE ------------
namespace live2d
{ 
	class ModelContext ;
	class PivotManager ;
	
	
	class UtInterpolate 
	{
	public:
		
		static void interpolatePoints(
				ModelContext &mdc 
				, PivotManager &pivotManager
				, bool *ret_paramOutside	
				,int numPts 
				, LDVector<l2d_pointf*> &pivotPoints 
				, l2d_pointf * dst_points
				, int pt_offset , int pt_step ) ;
	
		
		static float interpolateFloat(
				ModelContext &mdc , 
				PivotManager &pivotManager	,
				bool *ret_paramOutside	,
				LDVector<float> & pivotValue 
		) ; 
	
		
		static int interpolateInt(
				ModelContext &mdc , 
				PivotManager &pivotManager	,
				bool *ret_paramOutside ,
				LDVector<int> & pivotValue ) ; 
	
	private:
		UtInterpolate();		
	
		//Prevention of copy Constructor
		UtInterpolate( const UtInterpolate & ) ;				
		UtInterpolate& operator=( const UtInterpolate & ) ; 
		
		~UtInterpolate();	
	};
} 
//------------ LIVE2D NAMESPACE ------------

#endif // __SKIP_DOC__

#endif		// __LIVE2D_UTINTERPOLATE_H__
