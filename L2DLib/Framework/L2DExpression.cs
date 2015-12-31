using System;
using System.Runtime.InteropServices;
using L2DLib.Core;

namespace L2DLib.Framework
{
    /// <summary>
    /// Live2D 표정과 관련된 기능을 제공합니다.
    /// </summary>
    public class L2DExpression : L2DBase
    {
        #region 속성
        /// <summary>
        /// 표정의 페이드인 시간을 가져옵니다.
        /// </summary>
        public int FadeIn
        {
            get { return _FadeIn; }
        }
        private int _FadeIn;

        /// <summary>
        /// 표정의 페이드 아웃 시간을 가져옵니다.
        /// </summary>
        public int FadeOut
        {
            get { return _FadeOut; }
        }
        private int _FadeOut;
        #endregion

        #region 생성자
        /// <summary>
        /// 표정 객체를 생성합니다.
        /// </summary>
        public L2DExpression()
        {
            HRESULT.Check(NativeMethods.CreateExpression(out _Handle));
            _IsLoaded = true;
        }
        #endregion

        #region 사용자 함수
        /// <summary>
        /// 표정의 재생을 시작합니다.
        /// </summary>
        public void StartExpression()
        {
            HRESULT.Check(NativeMethods.StartExpression(new IntPtr(Handle)));
        }

        /// <summary>
        /// 표정에 표준 형식의 매개변수를 추가합니다.
        /// </summary>
        /// <param name="paramID">매개변수의 고유값입니다.</param>
        /// <param name="calc">매개변수의 계산 형식입니다.</param>
        /// <param name="value">매개변수의 값입니다.</param>
        /// <param name="defaultValue">매개변수의 기본값입니다.</param>
        public void AddParam(string paramID, string calc, float value, float defaultValue)
        {
            HRESULT.Check(NativeMethods.ExpressionAddParam(new IntPtr(Handle), Marshal.StringToHGlobalAnsi(paramID), Marshal.StringToHGlobalAnsi(calc), value, defaultValue));
        }

        /// <summary>
        /// 표정에 구버전 형식의 매개변수를 추가합니다.
        /// </summary>
        /// <param name="paramID">매개변수의 고유값입니다.</param>
        /// <param name="value">매개변수의 값입니다.</param>
        /// <param name="defaultValue">매개변수의 기본값입니다.</param>
        public void AddParamV09(string paramID, string calc, float value, float defaultValue)
        {
            HRESULT.Check(NativeMethods.ExpressionAddParamV09(new IntPtr(Handle), Marshal.StringToHGlobalAnsi(paramID), value, defaultValue));
        }

        /// <summary>
        /// 표정의 페이드인 시간을 설정합니다.
        /// </summary>
        /// <param name="msec">애니메이션을 진행할 밀리초단위의 시간입니다.</param>
        public void SetFadeIn(int msec)
        {
            HRESULT.Check(NativeMethods.ExpressionSetFadeIn(new IntPtr(Handle), msec));
            _FadeIn = msec;
        }

        /// <summary>
        /// 표정의 페이드 아웃 시간을 설정합니다.
        /// </summary>
        /// <param name="msec">애니메이션을 진행할 밀리초단위의 시간입니다.</param>
        public void SetFadeOut(int msec)
        {
            HRESULT.Check(NativeMethods.ExpressionSetFadeOut(new IntPtr(Handle), msec));
            _FadeOut = msec;
        }
        #endregion
    }
}
