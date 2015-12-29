/**
*
*  You can modify and use this source freely
*  only for the development of application related Live2D.
*
*  (c) Live2D Inc. All rights reserved.
*/
#pragma once


//Live2D lib
#include "motion/AMotion.h"
#include "util/Json.h"
#include "ALive2DModel.h"
#include "util/UtFile.h"
#include <vector>
#include <string>

namespace live2d
{
	namespace framework
	{
		struct L2DExpressionParam
		{
			std::string pid;
			//int index=-1;
			int type;
			float value;

		};

		class L2DExpressionMotion : public AMotion
		{
		private:
			static const char EXPRESSION_DEFAULT[];
			static const int TYPE_ADD;
			static const int TYPE_MULT;
			static const int TYPE_SET;

			std::vector<L2DExpressionParam> paramList;

		public:
			L2DExpressionMotion() {}
			virtual ~L2DExpressionMotion(void) {}

			virtual void addParam(char* paramID, char* calc, float value, float defaultValue);
			virtual void addParamV09(char* paramID, float value, float defaultValue);
			virtual void setFadeIn(int fadeInMsec);
			virtual void setFadeOut(int fadeOutMsec);
			
			virtual void updateParamExe(live2d::ALive2DModel * model, INT64 timeMSec, float weight, MotionQueueEnt *motionQueueEnt);
		};
	}
}