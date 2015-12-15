
#ifndef __LIVE2D_BD_BOX_GRID_H__
#define __LIVE2D_BD_BOX_GRID_H__


#ifndef __SKIP_DOC__

#include "../Live2D.h"
#include "../param/PivotManager.h"
#include "IBaseData.h"
#include "IBaseContext.h"


//------------ LIVE2D NAMESPACE ------------
namespace live2d
{ 
	
	class BDBoxGrid : public IBaseData 
	{
	public:
		BDBoxGrid();
		virtual ~BDBoxGrid();

	public:
		void initDirect(MemoryParam*	memParam) ;
	
		virtual void readV2(BReader & br , MemoryParam* memParam ) ;
	
		virtual IBaseContext* init(ModelContext &mdc) ;
	
		virtual void setupInterpolate(ModelContext &mdc , IBaseContext* cdata ) ;
		
		virtual void setupTransform(ModelContext &mdc, IBaseContext* cdata ) ;
		
		virtual void transformPoints( ModelContext &mdc, IBaseContext* cdata 
				, l2d_pointf * srcPoints , l2d_pointf * dstPoints 
				, int numPoint , int pt_offset , int pt_step ) ;
	
	
		
		inline int getNumPts(){ return (col+1)*(row+1) ; }
	
		
		virtual int getType()
		{
			return IBaseData::TYPE_BD_BOX_GRID ;
		}
	
		//-------------------------------------
	#ifdef L2D_DEBUG
		virtual void dump() ;
	#endif
	
	private:
		// Prevention of copy Constructor
		BDBoxGrid( const BDBoxGrid & ) ;
		BDBoxGrid& operator=( const BDBoxGrid & ) ;
	
		void transformPoints_sdk2( l2d_pointf* src , l2d_pointf* dst 
				, int numPoint , int src_offset , int src_step , l2d_pointf* pt , int _col , int _row ) ;

		void transformPoints_sdk1( ModelContext &mdc, IBaseContext* cdata 
				, l2d_pointf * srcPoints , l2d_pointf * dstPoints 
				, int numPoint , int pt_offset , int pt_step ) ;

	private:
		int							col ;			
		int							row ;			
		 
		PivotManager*				pivotManager ;	
		LDVector<l2d_pointf*>*		pivotPoints ;	
	};
	
	
	class BDBoxGridContext : public IBaseContext 
	{
	public:
		BDBoxGridContext(BDBoxGrid *src) ;
		virtual ~BDBoxGridContext() ;
		
	public:
		int 				tmpBaseDataIndex ;		
		l2d_pointf * 		interpolatedPoints ; 	
		l2d_pointf * 		transformedPoints ;		
	} ;
} 
//------------ LIVE2D NAMESPACE ------------

#endif // __SKIP_DOC__

#endif	// __LIVE2D_BD_BOX_GRID_H__


