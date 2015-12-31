using System;
using L2DLib.Core;
using L2DLib.Utility;

namespace L2DLib.Framework
{
    /// <summary>
    /// Live2D 렌더링과 관련된 기능을 제공합니다.
    /// </summary>
    public class L2DRender
    {
        #region 속성
        /// <summary>
        /// 렌더러가 표시할 모델을 가져옵니다.
        /// </summary>
        public L2DModel Model
        {
            get { return _Model; }
        }
        private L2DModel _Model;
        #endregion

        #region 생성자
        public L2DRender(L2DModel model)
        {
            _Model = model;
        }
        #endregion

        #region 사용자 함수
        /// <summary>
        /// 렌더링을 시작합니다.
        /// </summary>
        public void BeginRender()
        {
            HRESULT.Check(NativeMethods.BeginRender(new IntPtr(Model.Handle)));
        }

        /// <summary>
        /// 렌더링을 끝냅니다.
        /// </summary>
        public void EndRender()
        {
            HRESULT.Check(NativeMethods.EndRender(new IntPtr(Model.Handle)));
        }

        /// <summary>
        /// 포즈 렌더링을 갱신합니다.
        /// BeginRender() 함수와 EndRender() 함수 사이에서 호출되어야 합니다.
        /// </summary>
        public void UpdatePose()
        {
            if (Model != null && Model.Pose != null)
            {
                Model.Pose.UpdateParam(Model);
            }
        }

        /// <summary>
        /// 물리 렌더링을 갱신합니다.
        /// BeginRender() 함수와 EndRender() 함수 사이에서 호출되어야 합니다.
        /// </summary>
        public void UpdatePhysics()
        {
            if (Model.Physics != null && Model.Physics?.Length > 0)
            {
                foreach (L2DPhysics physics in Model.Physics)
                {
                    physics.UpdateParam(Model);
                }
            }
        }

        /// <summary>
        /// 모션 렌더링을 갱신합니다.
        /// BeginRender() 함수와 EndRender() 함수 사이에서 호출되어야 합니다.
        /// </summary>
        public void UpdateMotion()
        {
            if (Model != null && Model.Motion?.Count > 0)
            {
                Model.LoadParam();
                HRESULT.Check(NativeMethods.UpdateMotion(new IntPtr(Model.Handle)));
                Model.SaveParam();
            }
        }

        /// <summary>
        /// 표정 렌더링을 갱신합니다.
        /// BeginRender() 함수와 EndRender() 함수 사이에서 호출되어야 합니다.
        /// </summary>
        public void UpdateExpression()
        {
            if (Model != null && Model.Expression?.Count > 0)
            {
                HRESULT.Check(NativeMethods.UpdateExpression(new IntPtr(Model.Handle)));
            }
        }

        /// <summary>
        /// 자동 호흡 렌더링을 갱신합니다.
        /// BeginRender() 함수와 EndRender() 함수 사이에서 호출되어야 합니다.
        /// </summary>
        public void UpdateBreath()
        {
            if (Model != null && Model.UseBreath)
            {
                double t = (L2DUtility.GetUserTimeMSec() / 1000.0) * 2 * 3.14;
                Model.SetParamFloat("PARAM_BREATH", (float)(0.5f + 0.5f * Math.Sin(t / 3.2345)));
            }
        }

        /// <summary>
        /// 자동 윙크 렌더링을 갱신합니다.
        /// BeginRender() 함수와 EndRender() 함수 사이에서 호출되어야 합니다.
        /// </summary>
        public void UpdateEyeBlink()
        {
            if (Model != null && Model.UseEyeBlink)
            {
                HRESULT.Check(NativeMethods.EyeBlinkUpdate(new IntPtr(Model.Handle)));
            }
        }
        #endregion
    }
}
