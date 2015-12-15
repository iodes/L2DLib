/**
 *  IBaseData.h
 * 
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */
#ifndef __LIVE2D_I_BASE_DATA_H__
#define __LIVE2D_I_BASE_DATA_H__


#ifndef __SKIP_DOC__

#include "../Live2D.h"
#include "../io/ISerializableV2.h"
#include "../id/BaseDataID.h"


//------------ LIVE2D NAMESPACE ------------
namespace live2d
{
	class ModelContext ;
	class BaseDataID ;
	class IBaseContext ;
	class PivotManager ;

	
	class IBaseData : public ISerializableV2
	{
	public:
		static const int BASE_INDEX_NOT_INIT = -2 ;
	
		
		static const int TYPE_BD_AFFINE = 1 ;
		static const int TYPE_BD_BOX_GRID = 2 ;
		
	public:
		IBaseData();
		virtual ~IBaseData(void);
		
	public:
			
		inline void setTargetBaseDataID(BaseDataID *id){ targetBaseDataID = id ; } 
	
		
		inline void setBaseDataID(BaseDataID *id){ baseDataID = id ; } 
		
		
		inline BaseDataID * getTargetBaseDataID() const { return targetBaseDataID ; }
	
		
		inline BaseDataID * getBaseDataID() const { return baseDataID ; }
	
		
		bool needTransform()
		{
			return ( targetBaseDataID 
					&& (targetBaseDataID != BaseDataID::DST_BASE_ID()) ) ;
		}
		
		
		
		virtual IBaseContext* init(ModelContext &mdc) = 0;

		
		virtual void readV2(BReader & br , MemoryParam* memParam ) ;
	
		
		virtual void setupInterpolate(ModelContext &mdc , IBaseContext* cdata ) = 0;
	
		//-------------------------------------
		
		virtual void setupTransform(ModelContext &mdc, IBaseContext* cdata ) = 0;
	
		
		virtual void transformPoints(ModelContext &mdc, IBaseContext* cdata , l2d_pointf * srcPoints , l2d_pointf * dstPoints 
				, int numPoint , int pt_offset , int pt_step ) = 0;
	
		
		virtual int getType() = 0 ;
		
#ifdef L2D_DEBUG
		virtual void dump() = 0 ;
#endif

	//SDK2.0
	protected:
		void readV2_opacity(BReader & br , MemoryParam* memParam) ;
		void interpolateOpacity(ModelContext & mdc, PivotManager * pivotMgr , IBaseContext * _data, bool* ret_paramOutside);

	private:
		//Prevention of copy Constructor
		IBaseData( const IBaseData & ) ;				
		IBaseData& operator=( const IBaseData & ) ; 
	
	private:
		BaseDataID* 			baseDataID ;			
		BaseDataID* 			targetBaseDataID ;		
	
		bool 					dirty ;					

		// SDK 2.0 (.moc ) LIVE2D_FORMAT_VERSION_V2_10_SDK2
		
		
		LDVector<float>*                  pivotOpacity;
	};
}
//------------ LIVE2D NAMESPACE ------------

#endif // __SKIP_DOC__

#endif	// __LIVE2D_I_BASE_DATA_H__
