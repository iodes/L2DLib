using System;
using L2DLib.Core;

namespace L2DLib.Framework
{
    /// <summary>
    /// Live2D 렌더링과 관련된 기능을 제공합니다.
    /// </summary>
    public class L2DRender : L2DBase
    {
        #region 생성자
        public L2DRender(L2DModel model)
        {
            _Handle = model.Handle;
            _IsLoaded = true;
        }
        #endregion

        #region 사용자 함수
        /// <summary>
        /// 렌더링을 시작합니다.
        /// </summary>
        public void BeginRender()
        {
            HRESULT.Check(NativeMethods.BeginRender(new IntPtr(Handle)));
        }

        /// <summary>
        /// 렌더링을 끝냅니다.
        /// </summary>
        public void EndRender()
        {
            HRESULT.Check(NativeMethods.EndRender(new IntPtr(Handle)));
        }
        #endregion
    }
}
