/**
*
*  You can modify and use this source freely
*  only for the development of application related Live2D.
*
*  (c) Live2D Inc. All rights reserved.
*/
#include "stdafx.h"
#include "L2DExpressionMotion.h"

using namespace std;

namespace live2d
{
	namespace framework
	{
		const char L2DExpressionMotion::EXPRESSION_DEFAULT[] = "DEFAULT";
		const int L2DExpressionMotion::TYPE_SET = 0;
		const int L2DExpressionMotion::TYPE_ADD = 1;
		const int L2DExpressionMotion::TYPE_MULT = 2;


		void L2DExpressionMotion::updateParamExe(ALive2DModel* model, INT64 timeMSec, float weight, MotionQueueEnt* motionQueueEnt)
		{
			int len = paramList.size();

			for (int i = 0; i < len; i++)
			{
				L2DExpressionParam& param = paramList[i];

				if (param.type == TYPE_ADD)
				{
					model->addToParamFloat(param.pid.c_str(), param.value, weight);
				}
				else if (param.type == TYPE_MULT)
				{
					model->multParamFloat(param.pid.c_str(), param.value, weight);
				}
				else if (param.type == TYPE_SET)
				{
					model->setParamFloat(param.pid.c_str(), param.value, weight);
				}
			}
		}

		void L2DExpressionMotion::addParam(char* paramID, char* calc, float value, float defaultValue)
		{
			int calcTypeInt;

			if (strcmp(calc, "add") == 0)
			{
				calcTypeInt = TYPE_ADD;
			}
			else if (strcmp(calc, "mult") == 0)
			{
				calcTypeInt = TYPE_MULT;
			}
			else if (strcmp(calc, "set") == 0)
			{
				calcTypeInt = TYPE_SET;
			}
			else
			{
				calcTypeInt = TYPE_ADD;
			}

			if (calcTypeInt == TYPE_ADD)
			{
				value = value - defaultValue;
			}

			else if (calcTypeInt == TYPE_MULT)
			{
				if (defaultValue == 0) defaultValue = 1;
				value = value / defaultValue;
			}


			L2DExpressionParam item;

			std::string str(paramID);

			item.pid = str;
			item.type = calcTypeInt;
			item.value = value;

			paramList.push_back(item);
		}

		void L2DExpressionMotion::addParamV09(char* paramID, float value, float defaultValue)
		{
			L2DExpressionParam item;

			std::string str(paramID);

			item.pid = str;
			item.type = TYPE_ADD;
			item.value = value - defaultValue;
			paramList.push_back(item);
		}

		void L2DExpressionMotion::setFadeIn(int fadeInMsec)
		{
			AMotion::setFadeIn(fadeInMsec);
		}

		void L2DExpressionMotion::setFadeOut(int fadeOutMsec)
		{
			AMotion::setFadeOut(fadeOutMsec);
		}
	}
}