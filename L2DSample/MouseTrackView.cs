using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using L2DLib.Framework;

namespace L2DSample
{
    class MouseTrackView : L2DView
    {
        public override void Rendering()
        {
            double angleX = (ActualWidth / 2 + Mouse.GetPosition(this).X) - ActualWidth;
            double angleY = ActualWidth / 2 - Mouse.GetPosition(this).Y;

            Model.SetParamFloat("PARAM_ANGLE_X", (float)(angleX / (ActualWidth / 2) * 30));
            Model.SetParamFloat("PARAM_ANGLE_Y", (float)(angleY / (ActualHeight / 2) * 30));
            Model.SetParamFloat("PARAM_EYE_BALL_X", (float)(angleX / (ActualWidth / 2)));
            Model.SetParamFloat("PARAM_EYE_BALL_Y", (float)(angleY / (ActualHeight / 2)));
            Model.SetParamFloat("PARAM_BODY_ANGLE_X", (float)(angleX / (ActualWidth / 2) * 10));
        }
    }
}
