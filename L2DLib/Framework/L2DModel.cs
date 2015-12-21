using System;
using System.Collections.Generic;
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
        /// 대상의 경로를 가져옵니다.
        /// </summary>
        public string Path
        {
            get { return _Path; }
        }
        protected string _Path;

        /// <summary>
        /// 모델의 포즈를 설정하거나 가져옵니다.
        /// </summary>
        public L2DPose Pose
        {
            get { return _Pose; }
            set
            {
                _Pose = value;
            }
        }
        private L2DPose _Pose;

        /// <summary>
        /// 모델의 모션을 설정하거나 가져옵니다.
        /// </summary>
        public Dictionary<string, L2DMotion[]> Motion
        {
            get { return _Motion; }
            set
            {
                _Motion = value;
            }
        }
        private Dictionary<string, L2DMotion[]> _Motion;

        /// <summary>
        /// 모델의 물리를 설정하거나 가져옵니다.
        /// </summary>
        public L2DPhysics[] Physics
        {
            get { return _Physics; }
            set
            {
                _Physics = value;
            }
        }
        private L2DPhysics[] _Physics;

        /// <summary>
        /// 모델의 자동 윙크 기능의 사용 여부를 가져오거나 설정합니다.
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
            _Path = path;
            HRESULT.Check(NativeMethods.LoadModel(Marshal.StringToHGlobalAnsi(path), out _Handle));
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
        /// <param name="key">대상 매개변수의 인덱스입니다.</param>
        /// <param name="value">대상 매개변수에 적용할 값입니다.</param>
        public void SetParamFloat(int key, float value)
        {
            CheckDispose();
            HRESULT.Check(NativeMethods.SetParamFloatInt(new IntPtr(Handle), key, value));
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
            HRESULT.Check(NativeMethods.SetParamFloatString(new IntPtr(Handle), Marshal.StringToHGlobalAnsi(key), value));
        }

        /// <summary>
        /// 키에 해당하는 매개변수에 값을 가져옵니다.
        /// BeginRender() 함수와 EndRender() 함수 사이에서 호출되어야 합니다.
        /// </summary>
        /// <param name="key">대상 매개변수의 인덱스입니다.</param>
        public float GetParamFloat(int key)
        {
            CheckDispose();
            float result = 0;
            HRESULT.Check(NativeMethods.GetParamFloatInt(new IntPtr(Handle), key, out result));

            return result;
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
            HRESULT.Check(NativeMethods.GetParamFloatString(new IntPtr(Handle), Marshal.StringToHGlobalAnsi(key), out result));

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
            HRESULT.Check(NativeMethods.AddToParamFloat(new IntPtr(Handle), Marshal.StringToHGlobalAnsi(key), value));
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
            HRESULT.Check(NativeMethods.MultParamFloat(new IntPtr(Handle), Marshal.StringToHGlobalAnsi(key), value));
        }

        /// <summary>
        /// 키에 해당하는 파츠의 투명도를 설정합니다.
        /// BeginRender() 함수와 EndRender() 함수 사이에서 호출되어야 합니다.
        /// </summary>
        /// <param name="key">대상 매개변수의 인덱스입니다.</param>
        /// <param name="value">대상 매개변수에 적용할 값입니다.</param>
        public void SetPartsOpacity(int key, float value)
        {
            CheckDispose();
            HRESULT.Check(NativeMethods.SetPartsOpacityInt(new IntPtr(Handle), key, value));
        }

        /// <summary>
        /// 키에 해당하는 파츠의 투명도를 설정합니다.
        /// BeginRender() 함수와 EndRender() 함수 사이에서 호출되어야 합니다.
        /// </summary>
        /// <param name="key">대상 매개변수의 이름입니다.</param>
        /// <param name="value">대상 매개변수에 적용할 값입니다.</param>
        public void SetPartsOpacity(string key, float value)
        {
            CheckDispose();
            HRESULT.Check(NativeMethods.SetPartsOpacityString(new IntPtr(Handle), Marshal.StringToHGlobalAnsi(key), value));
        }

        /// <summary>
        /// 키에 해당하는 파츠의 투명도를 가져옵니다.
        /// BeginRender() 함수와 EndRender() 함수 사이에서 호출되어야 합니다.
        /// </summary>
        /// <param name="key">대상 매개변수의 인덱스입니다.</param>
        public float GetPartsOpacity(int key)
        {
            CheckDispose();
            float result = 0;
            HRESULT.Check(NativeMethods.GetPartsOpacityInt(new IntPtr(Handle), key, out result));

            return result;
        }

        /// <summary>
        /// 키에 해당하는 파츠의 투명도를 가져옵니다.
        /// BeginRender() 함수와 EndRender() 함수 사이에서 호출되어야 합니다.
        /// </summary>
        /// <param name="key">대상 매개변수의 이름입니다.</param>
        public float GetPartsOpacity(string key)
        {
            CheckDispose();
            float result = 0;
            HRESULT.Check(NativeMethods.GetPartsOpacityString(new IntPtr(Handle), Marshal.StringToHGlobalAnsi(key), out result));

            return result;
        }

        /// <summary>
        /// 키에 해당하는 매개변수의 인덱스를 가져옵니다.
        /// BeginRender() 함수와 EndRender() 함수 사이에서 호출되어야 합니다.
        /// </summary>
        /// <param name="key">대상 매개변수의 이름입니다.</param>
        public int GetParamIndex(string key)
        {
            CheckDispose();
            int result = 0;
            HRESULT.Check(NativeMethods.GetParamIndex(new IntPtr(Handle), Marshal.StringToHGlobalAnsi(key), out result));

            return result;
        }

        /// <summary>
        /// 키에 해당하는 파츠의 데이터 인덱스를 가져옵니다.
        /// BeginRender() 함수와 EndRender() 함수 사이에서 호출되어야 합니다.
        /// </summary>
        /// <param name="key">대상 파츠의 이름입니다.</param>
        public int GetPartsDataIndex(string key)
        {
            CheckDispose();
            int result = 0;
            HRESULT.Check(NativeMethods.GetPartsDataIndex(new IntPtr(Handle), Marshal.StringToHGlobalAnsi(key), out result));

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
