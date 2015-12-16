using System;
using System.Runtime.InteropServices;
using L2DLib.Core;

namespace L2DLib.Framework
{
    /// <summary>
    /// Live2D 모델과 관련된 기능을 제공합니다.
    /// </summary>
    public class L2DModel : L2DBase, IDisposable
    {
        #region 속성
        /// <summary>
        /// 렌더러가 표시할 모델을 가져옵니다.
        /// </summary>
        public L2DMotion[] Motion
        {
            get { return _Motion; }
            set
            {
                _Motion = value;
            }
        }
        private L2DMotion[] _Motion;

        /// <summary>
        /// 자동 윙크 기능의 사용 여부를 가져오거나 설정합니다.
        /// </summary>
        public bool UseEyeBlink
        {
            get { return _UseEyeBlink; }
            set
            {
                _UseEyeBlink = value;
            }
        }
        private bool _UseEyeBlink = false;
        #endregion

        #region 객체
        private bool IsModelLoaded = false;
        private bool IsTextureLoaded = false;
        #endregion

        #region 생성자
        /// <summary>
        /// 모델 객체를 생성합니다.
        /// </summary>
        /// <param name="path">모델 파일의 경로입니다.</param>
        public L2DModel(string path)
        {
            HRESULT.Check(NativeMethods.LoadModel(path, out _Handle));
            IsModelLoaded = true;
            SetLoaded();
        }
        #endregion

        #region 소멸자
        private bool disposedValue = false;

        protected virtual void Dispose(bool disposing)
        {
            if (!disposedValue)
            {
                _IsLoaded = false;

                if (disposing)
                {
                    IsModelLoaded = false;
                    IsTextureLoaded = false;
                }

                HRESULT.Check(NativeMethods.RemoveModel(new IntPtr(Handle)));

                disposedValue = true;
            }
        }

        ~L2DModel()
        {
            Dispose(false);
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }
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

        private void CheckDispose()
        {
            if (disposedValue)
            {
                throw new ObjectDisposedException(GetType().FullName);
            }
        }
        #endregion

        #region 사용자 함수
        /// <summary>
        /// 텍스처를 설정합니다.
        /// </summary>
        /// <param name="path">텍스처 파일의 경로 배열입니다.</param>
        public void SetTexture(string[] path)
        {
            CheckDispose();
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
            CheckDispose();
            HRESULT.Check(NativeMethods.SetParamFloat(new IntPtr(Handle), key, value));
        }

        /// <summary>
        /// 키에 해당하는 매개변수에 값을 가져옵니다.
        /// BeginRender() 함수와 EndRender() 함수 사이에서 호출되어야 합니다.
        /// </summary>
        /// <param name="key">대상 매개변수의 이름입니다.</param>
        public float GetParamFloat(string key)
        {
            CheckDispose();
            float result = 0;
            HRESULT.Check(NativeMethods.GetParamFloat(new IntPtr(Handle), key, out result));

            return result;
        }

        /// <summary>
        /// 키에 해당하는 매개변수에 값을 더합니다.
        /// BeginRender() 함수와 EndRender() 함수 사이에서 호출되어야 합니다.
        /// </summary>
        /// <param name="key">대상 매개변수의 이름입니다.</param>
        /// <param name="value">대상 매개변수에 적용할 값입니다.</param>
        public void AddToParamFloat(string key, float value)
        {
            CheckDispose();
            HRESULT.Check(NativeMethods.AddToParamFloat(new IntPtr(Handle), key, value));
        }

        /// <summary>
        /// 키에 해당하는 매개변수에 값을 곱합니다.
        /// BeginRender() 함수와 EndRender() 함수 사이에서 호출되어야 합니다.
        /// </summary>
        /// <param name="key">대상 매개변수의 이름입니다.</param>
        /// <param name="value">대상 매개변수에 적용할 값입니다.</param>
        public void MultParamFloat(string key, float value)
        {
            CheckDispose();
            HRESULT.Check(NativeMethods.MultParamFloat(new IntPtr(Handle), key, value));
        }

        /// <summary>
        /// 키에 해당하는 부분의 투명도를 설정합니다.
        /// BeginRender() 함수와 EndRender() 함수 사이에서 호출되어야 합니다.
        /// </summary>
        /// <param name="key">대상 매개변수의 이름입니다.</param>
        /// <param name="value">대상 매개변수에 적용할 값입니다.</param>
        public void SetPartsOpacity(string key, float value)
        {
            CheckDispose();
            HRESULT.Check(NativeMethods.SetPartsOpacity(new IntPtr(Handle), key, value));
        }

        public float GetPartsOpacity(string key)
        {
            CheckDispose();
            float result = 0;
            HRESULT.Check(NativeMethods.GetPartsOpacity(new IntPtr(Handle), key, out result));

            return result;
        }

        /// <summary>
        /// 매개변수를 저장합니다.
        /// BeginRender() 함수와 EndRender() 함수 사이에서 호출되어야 합니다.
        /// </summary>
        public void SaveParam()
        {
            CheckDispose();
            HRESULT.Check(NativeMethods.SaveParam(new IntPtr(Handle)));
        }

        /// <summary>
        /// 메개변수를 불러옵니다.
        /// BeginRender() 함수와 EndRender() 함수 사이에서 호출되어야 합니다.
        /// </summary>
        public void LoadParam()
        {
            CheckDispose();
            HRESULT.Check(NativeMethods.LoadParam(new IntPtr(Handle)));
        }
        #endregion
    }
}
