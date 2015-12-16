using System;
using System.Runtime.InteropServices;
using L2DLib.Core;

namespace L2DLib.Framework
{
    /// <summary>
    /// Live2D 모델과 관련된 기능을 제공합니다.
    /// </summary>
    public class L2DModel : L2DBase
    {
        #region 객체
        private bool IsModelLoaded = false;
        private bool IsTextureLoaded = false;
        #endregion

        #region 내부 함수
        private void SetLoaded()
        {
            if (IsModelLoaded && IsTextureLoaded)
            {
                _IsLoaded = true;
            }
            else
            {
                _IsLoaded = false;
            }
        }
        #endregion

        #region 사용자 함수
        /// <summary>
        /// 모델을 불러옵니다.
        /// </summary>
        /// <param name="path">모델 파일의 경로입니다.</param>
        public void LoadModel(string path)
        {
            HRESULT.Check(NativeMethods.LoadModel(path, out _Handle));
            IsModelLoaded = true;
            SetLoaded();
        }

        /// <summary>
        /// 텍스처를 설정합니다.
        /// </summary>
        /// <param name="path">텍스처 파일의 경로 배열입니다.</param>
        public void SetTexture(string[] path)
        {
            foreach (string texture in path)
            {
                HRESULT.Check(NativeMethods.SetTexture(new IntPtr(Handle), Marshal.StringToHGlobalAuto(texture)));
            }
            IsTextureLoaded = true;
            SetLoaded();
        }

        /// <summary>
        /// 키에 해당하는 매개변수에 값을 설정합니다.
        /// BeginRender() 함수와 EndRender() 함수 사이에서 호출되어야 합니다.
        /// </summary>
        /// <param name="key">대상 매개변수의 이름입니다.</param>
        /// <param name="value">대상 매개변수에 적용할 값입니다.</param>
        public void SetParamFloat(string key, float value)
        {
            NativeMethods.SetParamFloat(new IntPtr(Handle), key, value);
        }

        /// <summary>
        /// 키에 해당하는 매개변수에 값을 더합니다.
        /// BeginRender() 함수와 EndRender() 함수 사이에서 호출되어야 합니다.
        /// </summary>
        /// <param name="key">대상 매개변수의 이름입니다.</param>
        /// <param name="value">대상 매개변수에 적용할 값입니다.</param>
        public void AddToParamFloat(string key, float value)
        {
            NativeMethods.AddToParamFloat(new IntPtr(Handle), key, value);
        }

        /// <summary>
        /// 키에 해당하는 매개변수에 값을 곱합니다.
        /// BeginRender() 함수와 EndRender() 함수 사이에서 호출되어야 합니다.
        /// </summary>
        /// <param name="key">대상 매개변수의 이름입니다.</param>
        /// <param name="value">대상 매개변수에 적용할 값입니다.</param>
        public void MultParamFloat(string key, float value)
        {
            NativeMethods.MultParamFloat(new IntPtr(Handle), key, value);
        }

        /// <summary>
        /// 키에 해당하는 부분의 투명도를 설정합니다.
        /// BeginRender() 함수와 EndRender() 함수 사이에서 호출되어야 합니다.
        /// </summary>
        /// <param name="key">대상 매개변수의 이름입니다.</param>
        /// <param name="value">대상 매개변수에 적용할 값입니다.</param>
        public void SetPartsOpacity(string key, float value)
        {
            NativeMethods.SetPartsOpacity(new IntPtr(Handle), key, value);
        }

        /// <summary>
        /// 매개변수를 저장합니다.
        /// BeginRender() 함수와 EndRender() 함수 사이에서 호출되어야 합니다.
        /// </summary>
        public void SaveParam()
        {
            NativeMethods.SaveParam(new IntPtr(Handle));
        }

        /// <summary>
        /// 메개변수를 불러옵니다.
        /// BeginRender() 함수와 EndRender() 함수 사이에서 호출되어야 합니다.
        /// </summary>
        public void LoadParam()
        {
            NativeMethods.LoadParam(new IntPtr(Handle));
        }
        #endregion
    }
}
