using System;
using L2DLib.Utility;
using L2DLib.Framework;

namespace L2DSample.View
{
    class HeadShakeView : L2DView
    {
        public override void Rendering()
        {
            double t = (L2DUtility.GetUserTimeMSec() / 1000.0) * 2 * 3.14;
            double cycle = 1.0;
            double value = Math.Sin(t / cycle);
            Model.SetParamFloat("PARAM_ANGLE_X", (float)(30 * value));
        }
    }
}
