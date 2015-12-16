using System;
using System.Runtime.InteropServices;

namespace L2DLib.Core
{
    /// <summary>
    /// L2DNative 라이브러리와 상호 운용 가능성을 제공합니다.
    /// </summary>
    class NativeMethods
    {
        #region Live2D
        [DllImport("L2DNative.dll")]
        public static extern int LoadModel(string modelPath, out long ret);

        [DllImport("L2DNative.dll")]
        public static extern int RemoveModel(IntPtr model);

        [DllImport("L2DNative.dll")]
        public static extern int SetTexture(IntPtr model, IntPtr texturePath);

        [DllImport("L2DNative.dll")]
        public static extern int SetParamFloat(IntPtr model, string key, float value);

        [DllImport("L2DNative.dll")]
        public static extern int GetParamFloat(IntPtr model, string key, out float ret);

        [DllImport("L2DNative.dll")]
        public static extern int AddToParamFloat(IntPtr model, string key, float value);

        [DllImport("L2DNative.dll")]
        public static extern int MultParamFloat(IntPtr model, string key, float value);

        [DllImport("L2DNative.dll")]
        public static extern int SetPartsOpacity(IntPtr model, string key, float value);

        [DllImport("L2DNative.dll")]
        public static extern int GetPartsOpacity(IntPtr model, string key, out float ret);

        [DllImport("L2DNative.dll")]
        public static extern int SaveParam(IntPtr model);

        [DllImport("L2DNative.dll")]
        public static extern int LoadParam(IntPtr model);

        [DllImport("L2DNative.dll")]
        public static extern int LoadMotion(string motionPath, out long ret);

        [DllImport("L2DNative.dll")]
        public static extern int SetFadeIn(IntPtr motion, IntPtr msec);

        [DllImport("L2DNative.dll")]
        public static extern int SetFadeOut(IntPtr motion, IntPtr msec);

        [DllImport("L2DNative.dll")]
        public static extern int SetLoop(IntPtr motion, bool loop);

        [DllImport("L2DNative.dll")]
        public static extern int StartMotion(IntPtr motion);

        [DllImport("L2DNative.dll")]
        public static extern int BeginRender(IntPtr model);

        [DllImport("L2DNative.dll")]
        public static extern int EndRender(IntPtr model);

        [DllImport("L2DNative.dll")]
        public static extern int Dispose();
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
        public static extern int Destroy();
        #endregion
    }
}
