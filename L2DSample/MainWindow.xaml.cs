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

        private void LoadModelJSON_Click(object sender, RoutedEventArgs e)
        {
            // Live2D
            // 모델 불러오기
            model = L2DFunctions.LoadModel(@"Resources\haru\haru.model.json");

            // 모델 자동 호흡 설정
            model.UseBreath = true;

            // 모델 자동 윙크 설정
            model.UseEyeBlink = true;

            // 렌더러에 대상 모델 설정
            RenderView.Model = model;

            // Application
            // 모션 목록 갱신
            foreach (L2DMotion[] group in model.Motion.Values)
            {
                foreach (L2DMotion motion in group)
                {
                    ListMotion.Items.Add(System.IO.Path.GetFileName(motion.Path));
                }
            }

            // 표정 목록 갱신
            for (int i = 0; i < model.Expression.Count; i++)
            {
                ListExpression.Items.Add(model.Expression.Keys.ElementAt(i));
            }
        }

        private void ListMotion_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            // 모션 선택 이벤트
            foreach (L2DMotion[] group in model.Motion.Values)
            {
                foreach (L2DMotion motion in group)
                {
                    if (System.IO.Path.GetFileName(motion.Path) == ListMotion.SelectedItem.ToString())
                    {
                        motion.StartMotion();
                        break;
                    }
                }
            }
        }

        private void ListExpression_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            // 표정 선택 이벤트
            model.Expression.Values.ElementAt(ListExpression.SelectedIndex).StartExpression();
        }
    }
}
