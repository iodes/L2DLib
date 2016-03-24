using System;
using System.IO;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using L2DLib.Utility;
using L2DLib.Framework;
using Microsoft.Win32;

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

        #region 내부 함수
        private void ReleaseCheck()
        {
            if (model != null)
            {
                model.Dispose();
            }
        }

        private void UpdateConfig()
        {
            // 모델 자동 호흡 설정
            model.UseBreath = true;

            // 모델 자동 윙크 설정
            model.UseEyeBlink = true;

            // 렌더러에 대상 모델 설정
            RenderView.Model = model;
        }
        #endregion

        private void LoadModel_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                OpenFileDialog dialog = new OpenFileDialog
                {
                    Filter = "MOC 모델|*.moc"
                };

                bool? result = dialog.ShowDialog();
                if (result == true)
                {
                    // 모델 초기화
                    if (model != null)
                    {
                        model.Dispose();
                    }

                    // 모델 불러오기
                    ReleaseCheck();
                    model = new L2DModel(dialog.FileName);

                    // 텍스처 불러오기
                    string texruePath =
                        string.Format("{0}\\{1}.1024",
                        new FileInfo(dialog.FileName).Directory.FullName,
                        Path.GetFileNameWithoutExtension(dialog.FileName));

                    if (Directory.Exists(texruePath))
                    {
                        model.SetTexture(Directory.GetFiles(texruePath));
                    }

                    // 설정 업데이트
                    UpdateConfig();
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "오류", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void LoadModelJSON_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                OpenFileDialog dialog = new OpenFileDialog
                {
                    Filter = "JSON 모델 구성|*.json"
                };

                bool? result = dialog.ShowDialog();
                if (result == true)
                {
                    // Live2D
                    // 모델 불러오기
                    ReleaseCheck();
                    model = L2DFunctions.LoadModel(dialog.FileName);

                    // 설정 업데이트
                    UpdateConfig();

                    // Application
                    // 목록 초기화
                    ListMotion.Items.Clear();
                    ListExpression.Items.Clear();

                    // 모션 목록 갱신
                    if (model.Motion != null)
                    {
                        foreach (L2DMotion[] group in model.Motion.Values)
                        {
                            foreach (L2DMotion motion in group)
                            {
                                ListMotion.Items.Add(Path.GetFileName(motion.Path));
                            }
                        }
                    }

                    // 표정 목록 갱신
                    if (model.Expression != null)
                    {
                        for (int i = 0; i < model.Expression.Count; i++)
                        {
                            ListExpression.Items.Add(model.Expression.Keys.ElementAt(i));
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "오류", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void ListMotion_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            // 모션 선택 이벤트
            if (model.Motion != null)
            {
                foreach (L2DMotion[] group in model.Motion.Values)
                {
                    foreach (L2DMotion motion in group)
                    {
                        if (Path.GetFileName(motion.Path) == ListMotion.SelectedItem.ToString())
                        {
                            motion.StartMotion();
                            break;
                        }
                    }
                }
            }
        }

        private void ListExpression_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            // 표정 선택 이벤트
            if (model.Expression != null)
            {
                model.Expression.Values.ElementAt(ListExpression.SelectedIndex).StartExpression();
            }
        }

        private void UseBreath_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("기능 준비중입니다.");
        }

        private void UseEyeBlink_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("기능 준비중입니다.");
        }

        private void About_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("Live2D For WPF\nPowered By. Managed Live2D", "프로그램 정보", MessageBoxButton.OK, MessageBoxImage.Information);
        }
    }
}
