using System;
using System.Collections.Generic;
using System.Linq;
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
using L2DLib.Framework;

namespace L2DSample
{
    /// <summary>
    /// MainWindow.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class MainWindow : Window
    {
        #region 객체
        L2DModel model;
        Random rnd = new Random();
        #endregion

        #region 생성자
        public MainWindow()
        {
            InitializeComponent();
        }
        #endregion

        private void BtnLoad_Click(object sender, RoutedEventArgs e)
        {
            // 모델 불러오기
            model = new L2DModel(@"Resources\haru\haru_01.moc");

            // 텍스처 불러오기
            model.SetTexture
                (
                    new string[]
                    {
                        @"Resources\haru\haru_01.1024\texture_00.png",
                        @"Resources\haru\haru_01.1024\texture_01.png",
                        @"Resources\haru\haru_01.1024\texture_02.png"
                    }
                );

            // 모션 불러오기
            List<L2DMotion> motionList = new List<L2DMotion>();
            motionList.Add(new L2DMotion(@"Resources\haru\motions\idle_00.mtn"));
            motionList.Add(new L2DMotion(@"Resources\haru\motions\tapBody_00.mtn"));
            motionList.Add(new L2DMotion(@"Resources\haru\motions\tapBody_01.mtn"));
            motionList.Add(new L2DMotion(@"Resources\haru\motions\tapBody_02.mtn"));
            motionList.Add(new L2DMotion(@"Resources\haru\motions\tapBody_03.mtn"));

            // 모델에 모션 설정
            model.Motion = motionList.ToArray();

            // 모델에 자동 윙크 설정
            model.UseEyeBlink = true;

            // 렌더러에 모델 설정
            RenderView.Model = model;
        }

        private void BtnReset_Click(object sender, RoutedEventArgs e)
        {
            // 모델 메모리 해제
            model.Dispose();
        }

        private void BtnMotion_Click(object sender, RoutedEventArgs e)
        {
            // 무작위 모션 재생
            model.Motion[rnd.Next(0, model.Motion.Length)].StartMotion();
        }
    }
}
