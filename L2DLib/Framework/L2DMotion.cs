using System;
using L2DLib.Core;

namespace L2DLib.Framework
{
    /// <summary>
    /// Live2D 모션과 관련된 기능을 제공합니다.
    /// </summary>
    public class L2DMotion : L2DBase
    {
        #region 생성자
        /// <summary>
        /// 모션 객체를 생성합니다.
        /// </summary>
        /// <param name="path">모션 파일의 경로입니다.</param>
        public L2DMotion(string path)
        {
            HRESULT.Check(NativeMethods.LoadMotion(path, out _Handle));
            _IsLoaded = true;
        }
        #endregion

        #region 사용자 함수
        /// <summary>
        /// 모션의 재생을 시작합니다.
        /// </summary>
        public void StartMotion()
        {
            HRESULT.Check(NativeMethods.StartMotion(new IntPtr(Handle)));
        }

        /// <summary>
        /// 모션의 페이드인 시간을 설정합니다.
        /// </summary>
        /// <param name="msec">애니메이션을 진행할 밀리초단위의 시간입니다.</param>
        public void SetFadeIn(int msec)
        {
            HRESULT.Check(NativeMethods.SetFadeIn(new IntPtr(Handle), new IntPtr(msec)));
        }

        /// <summary>
        /// 모션의 페이드 아웃 시간을 설정합니다.
        /// </summary>
        /// <param name="msec">애니메이션을 진행할 밀리초단위의 시간입니다.</param>
        public void SetFadeOut(int msec)
        {
            HRESULT.Check(NativeMethods.SetFadeOut(new IntPtr(Handle), new IntPtr(msec)));
        }

        /// <summary>
        /// 모션의 반복 재생 여부를 설정합니다.
        /// </summary>
        /// <param name="loop">모션의 반복 재생 여부입니다.</param>
        public void SetLoop(bool loop)
        {
            HRESULT.Check(NativeMethods.SetLoop(new IntPtr(Handle), loop));
        }
        #endregion
    }
}
