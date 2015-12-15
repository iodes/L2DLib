using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using L2DLib.Core;
using System.Windows.Interop;

namespace L2DLib
{
    /// <summary>
    /// RenderView.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class RenderView : UserControl
    {
        #region 속성
        /// <summary>
        /// 렌더링시 투명도를 지원하는지 여부를 나타내는 값을 가져오거나 설정합니다.
        /// </summary>
        public bool AllowTransparency
        {
            get { return _AllowTransparency; }
            set
            {
                _AllowTransparency = value;
                NativeMethods.SetAlpha(value);
            }
        }
        private bool _AllowTransparency = true;

        /// <summary>
        /// 렌더링시 사용할 멀티 샘플링 앤티 앨리어싱 값을 가져오거나 설정합니다.
        /// </summary>
        public uint DesiredSamples
        {
            get { return _DesiredSamples; }
            set
            {
                _DesiredSamples = value;
                HRESULT.Check(NativeMethods.SetNumDesiredSamples(value));
            }
        }
        private uint _DesiredSamples = 4;
        #endregion

        #region 객체
        TimeSpan LastRender;
        #endregion

        #region 생성자
        public RenderView()
        {
            InitializeComponent();
        }
        #endregion

        #region 사용자 함수
        public void Initialize(string model, string[] textures, string[] motions = null)
        {
            HRESULT.Check(NativeMethods.SetSize(512, 512));
            HRESULT.Check(NativeMethods.SetAlpha(AllowTransparency));
            HRESULT.Check(NativeMethods.SetNumDesiredSamples(DesiredSamples));

            NativeStructure.ARGUMENT argument = new NativeStructure.ARGUMENT
            {
                model = Marshal.StringToHGlobalAuto(model),
                textures = new LPWSTRArray(textures).arrayPtr,
                motions = new LPWSTRArray(motions).arrayPtr,
            };
            HRESULT.Check(NativeMethods.SetArgument(argument));

            CompositionTarget.Rendering += CompositionTarget_Rendering;
        }
        #endregion

        #region 렌더링 이벤트
        private void Live2D_Rendering()
        {
            HRESULT.Check(NativeMethods.BeginRender());

            double angleX = (ActualWidth / 2 + Mouse.GetPosition(this).X) - ActualWidth;
            double angleY = ActualWidth / 2 - Mouse.GetPosition(this).Y;

            HRESULT.Check(NativeMethods.SetParamFloat("PARAM_ANGLE_X", (float)(angleX / (ActualWidth / 2) * 30)));
            HRESULT.Check(NativeMethods.SetParamFloat("PARAM_ANGLE_Y", (float)(angleY / (ActualHeight / 2) * 30)));
            HRESULT.Check(NativeMethods.SetParamFloat("PARAM_EYE_BALL_X", (float)(angleX / (ActualWidth / 2))));
            HRESULT.Check(NativeMethods.SetParamFloat("PARAM_EYE_BALL_Y", (float)(angleY / (ActualHeight / 2))));

            HRESULT.Check(NativeMethods.EndRender());
        }

        private void CompositionTarget_Rendering(object sender, EventArgs e)
        {
            RenderingEventArgs args = (RenderingEventArgs)e;

            if (RenderScene.IsFrontBufferAvailable && LastRender != args.RenderingTime)
            {
                IntPtr pSurface = IntPtr.Zero;
                HRESULT.Check(NativeMethods.GetBackBufferNoRef(out pSurface));
                if (pSurface != IntPtr.Zero)
                {
                    RenderScene.Lock();
                    RenderScene.SetBackBuffer(D3DResourceType.IDirect3DSurface9, pSurface);

                    Live2D_Rendering();

                    RenderScene.AddDirtyRect(new Int32Rect(0, 0, RenderScene.PixelWidth, RenderScene.PixelHeight));
                    RenderScene.Unlock();

                    LastRender = args.RenderingTime;
                }
            }
        }
        #endregion
    }
}
