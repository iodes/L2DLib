using L2DLib.Framework;
using System.Windows.Input;

namespace L2DSample.View
{
    class MouseDragView : L2DView
    {
        public MouseDragView()
        {
            MouseLeftButtonUp += MouseDragView_MouseLeftButtonUp;
            MouseLeftButtonDown += MouseDragView_MouseLeftButtonDown;
        }

        private void MouseDragView_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            ReleaseMouseCapture();
        }

        private void MouseDragView_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            CaptureMouse();
        }

        public override void Rendering()
        {
            if (IsMouseCaptured && Mouse.LeftButton == MouseButtonState.Pressed)
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
}
