
#ifndef __IBASE_CONTEXT__
#define __IBASE_CONTEXT__


#ifndef __SKIP_DOC__

#include "../memory/LDObject.h"


//------------ LIVE2D NAMESPACE ------------
namespace live2d
{ 
	class IBaseData ;
		
	class IBaseContext : public live2d::LDObject 
	{
	public:
		IBaseContext(IBaseData* src) ;
		virtual ~IBaseContext(){}

		void* getSrcPtr(){ return this->srcPtr ; } 
		
		void setPartsIndex( int p ){ this->partsIndex = p ; }
		int getPartsIndex() { return this->partsIndex ; }

		bool isOutsideParam() {	return this->outsideParam;	}
		void setOutsideParam( bool outsideParam ) {	this->outsideParam = outsideParam ;	}

		bool isAvailable()
		{
			return available && ! outsideParam ;
		}

		void setAvailable(bool available)
		{
			this->available = available;
		}

		
		float getTotalScale()
		{
			return totalScale ;
		}
	
		void setTotalScale_notForClient(float totalScale)
		{
			this->totalScale = totalScale ;
		}

		float getInterpolatedOpacity(){	return interpolatedOpacity ;}

		void setInterpolatedOpacity(float interpolatedOpacity){this->interpolatedOpacity = interpolatedOpacity ;}

		float getTotalOpacity(){return totalOpacity ;}
	
		void setTotalOpacity(float totalOpacity){this->totalOpacity = totalOpacity ;}


	private:
		IBaseData* srcPtr ;
		int partsIndex ;
		
		bool outsideParam ;
		bool available ;

		
	protected:
		
		
		
		
		
		float		totalScale;

		
		float		interpolatedOpacity;		
		float		totalOpacity;				

	};
}
//------------ LIVE2D NAMESPACE ------------

#endif // __SKIP_DOC__

#endif // __IBASE_CONTEXT__
