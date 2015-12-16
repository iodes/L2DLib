using System;
using L2DLib.Core;

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
        #endregion
    }
}
