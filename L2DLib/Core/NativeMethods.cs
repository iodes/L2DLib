using System;
using System.Runtime.InteropServices;

namespace L2DLib.Core
{
    /// <summary>
    /// L2DNative 라이브러리의 상호 운용 기능을 제공합니다.
    /// </summary>
    class NativeMethods
    {
        #region Live2D
        /// <summary>
        /// Live2D 초기화에 사용될 명령줄 인수를 설정합니다.
        /// ARGUMENT 구조체 형식을 사용하여 정보를 전달할 수 있습니다.
        /// </summary>
        [DllImport("L2DNative.dll")]
        public static extern int SetArgument(NativeStructure.ARGUMENT argument);

        /// <summary>
        /// 키에 해당하는 매개변수에 값을 설정합니다.
        /// BeginRender() 함수와 EndRender() 함수 사이에서 호출되어야 합니다.
        /// </summary>
        [DllImport("L2DNative.dll")]
        public static extern int SetParamFloat(string key, float value);

        /// <summary>
        /// 키에 해당하는 매개변수에 값을 더합니다.
        /// BeginRender() 함수와 EndRender() 함수 사이에서 호출되어야 합니다.
        /// </summary>
        [DllImport("L2DNative.dll")]
        public static extern int AddToParamFloat(string key, float value);

        /// <summary>
        /// 키에 해당하는 매개변수에 값을 곱합니다.
        /// BeginRender() 함수와 EndRender() 함수 사이에서 호출되어야 합니다.
        /// </summary>
        [DllImport("L2DNative.dll")]
        public static extern int MultParamFloat(string key, float value);

        /// <summary>
        /// 키에 해당하는 부분의 투명도를 설정합니다.
        /// BeginRender() 함수와 EndRender() 함수 사이에서 호출되어야 합니다.
        /// </summary>
        [DllImport("L2DNative.dll")]
        public static extern int SetPartsOpacity(string key, float value);

        /// <summary>
        /// 매개변수를 저장합니다.
        /// BeginRender() 함수와 EndRender() 함수 사이에서 호출되어야 합니다.
        /// </summary>
        [DllImport("L2DNative.dll")]
        public static extern int SaveParam();

        /// <summary>
        /// 메개변수를 불러옵니다.
        /// BeginRender() 함수와 EndRender() 함수 사이에서 호출되어야 합니다.
        /// </summary>
        [DllImport("L2DNative.dll")]
        public static extern int LoadParam();

        /// <summary>
        /// Live2D 렌더링을 시작합니다.
        /// </summary>
        [DllImport("L2DNative.dll")]
        public static extern int BeginRender();

        /// <summary>
        /// Live2D 렌더링을 끝냅니다.
        /// </summary>
        [DllImport("L2DNative.dll")]
        public static extern int EndRender();
        #endregion

        #region DirectX
        /// <summary>
        /// 렌더링 영역의 크기를 설정합니다.
        /// </summary>
        [DllImport("L2DNative.dll")]
        public static extern int SetSize(uint width, uint height);

        /// <summary>
        /// 렌더링시 투명도를 지원하는지 여부를 나타내는 값을 설정합니다.
        /// </summary>
        [DllImport("L2DNative.dll")]
        public static extern int SetAlpha(bool useAlpha);

        /// <summary>
        /// 렌더링시 사용할 멀티 샘플링 앤티 앨리어싱 값을 설정합니다.
        /// </summary>
        [DllImport("L2DNative.dll")]
        public static extern int SetNumDesiredSamples(uint numSamples);

        /// <summary>
        /// 참조를 추가하지 않은 현재의 렌더링 표면을 가져옵니다.
        /// </summary>
        [DllImport("L2DNative.dll")]
        public static extern int GetBackBufferNoRef(out IntPtr pSurface);

        /// <summary>
        /// 렌더링에 사용할 어댑터를 설정합니다.
        /// </summary>
        [DllImport("L2DNative.dll")]
        public static extern int SetAdapter(NativeStructure.POINT screenSpacePoint);

        /// <summary>
        /// 대상의 소멸자를 호출합니다.
        /// </summary>
        [DllImport("L2DNative.dll")]
        public static extern void Destroy();
        #endregion
    }
}
