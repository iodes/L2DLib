

#ifndef __LIVE2D_I_DRAW_DATA_H__
#define __LIVE2D_I_DRAW_DATA_H__


#ifndef __SKIP_DOC__

#include "../memory/LDObject.h"

//------------ LIVE2D NAMESPACE ------------
namespace live2d
{ 
	class IDrawData ;
	
	class IDrawContext : public live2d::LDObject 
	{
	public:
		IDrawContext(IDrawData* src) ;
		virtual ~IDrawContext(){}
	
		void* getSrcPtr(){ return this->srcPtr ; } 
	
		
		void setPartsIndex( int p ){ this->partsIndex = p ; }
	
		
		int getPartsIndex() { return this->partsIndex ; }
	
		
		bool isAvailable(){ return available && ! paramOutside ; }
	
	public:
		int 			interpolatedDrawOrder ;		
		float 			interpolatedOpacity ;		
		
		bool			paramOutside ;				
		
		float			partsOpacity ;				
		bool			available ;					
	
	    float			baseOpacity;		        

	private:
		IDrawData* 		srcPtr ;					
		int 			partsIndex ;				
	};
}
//------------ LIVE2D NAMESPACE ------------

#endif // __SKIP_DOC__

#endif	// __LIVE2D_I_DRAW_DATA_H__

