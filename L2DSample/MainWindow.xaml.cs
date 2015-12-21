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
using L2DLib.Utility;

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
            model = L2DFunctions.LoadModel(@"Resources\haru\haru.model.json");

            // 모델 자동 호흡 설정
            model.UseBreath = true;

            // 모델 자동 윙크 설정
            model.UseEyeBlink = true;

            // 렌더러에 대상 모델 설정
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
            L2DMotion[] motions = model.Motion["tap_body"];
            L2DMotion motion = motions[rnd.Next(0, motions.Length)];
            motion.StartMotion();
        }
    }
}
