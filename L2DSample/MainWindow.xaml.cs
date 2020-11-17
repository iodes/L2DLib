using System;
using System.IO;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using L2DLib.Utility;
using L2DLib.Framework;
using Microsoft.Win32;
using L2DLib.Motioning;

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
            //Ensure the loop stop
            OnStopLoop(null, null);
        }

        private void UpdateConfig()
        {
            // 모델 자동 호흡 설정
            model.UseBreath = true;

            // 모델 자동 윙크 설정
            model.UseEyeBlink = true;

            // 렌더러에 대상 모델 설정
            RenderView.Model = model;

            //It can smooth transition and natual
            model.SetFadeIn(1000);

            //Update the motion groups
            LoopMotionGroup.Items.Clear();
            foreach (var item in model.Motion.Keys)
            {
                var menuItem = new MenuItem { Header = item };
                menuItem.Click += OnGroupLoop;
                LoopMotionGroup.Items.Add(menuItem);
            }
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
            var motion = GetMotion(ListMotion.SelectedItem.ToString());
            if (motion!=null)
            {
                motion.StartMotion();
            }
        }
        /// <summary>
        /// Get the motion, if the file name equals to <paramref name="filename"/>
        /// </summary>
        /// <param name="filename">Target file name</param>
        /// <returns></returns>
        protected L2DMotion GetMotion(string filename)
        {
            // 모션 선택 이벤트
            if (model?.Motion != null)//The model will be null
            {
                //Using linq to merge 3 row
                return model.Motion.SelectMany(x => x.Value)
                    .Where(x => Path.GetFileName(x.Path) == filename)
                    .FirstOrDefault();
            }
            return null;
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

        #region LoopSample

        private MotionPlayer motionPlayer;

        private void OnGroupLoop(object sender, RoutedEventArgs e)
        {
            if (model?.Motion != null && sender is MenuItem)
            {
                OnStopLoop(null, null);
                var menuItem = (MenuItem)sender;
                motionPlayer = model.CreatePlayer(RenderView, menuItem.Header.ToString());
                motionPlayer.Loop = true;
                motionPlayer.Begin();
            }
        }
        private void OnLoopAllMotionsClick(object sender, RoutedEventArgs e)
        {
            if (model?.Motion!=null)
            {
                OnStopLoop(null, null);
                var motions = model.Motion.Values.SelectMany(x => x).ToArray();
                motionPlayer = new MotionPlayer(RenderView, motions);
                motionPlayer.Loop = true;
                motionPlayer.Begin();
            }
        }

        private void OnLoopThisMotionsClick(object sender, RoutedEventArgs e)
        {
            if (model?.Motion!=null)
            {
                OnStopLoop(null, null);
                var motion = GetMotion(ListMotion.SelectedItem.ToString());
                if (motion != null)
                {
                    motionPlayer = new MotionPlayer(RenderView, new L2DMotion[] { motion });
                    motionPlayer.Loop = true;
                    motionPlayer.Begin();
                }
            }
        }

        private void OnStopLoop(object sender, RoutedEventArgs e)
        {
            if (motionPlayer != null)
            {
                //If no stop the player, it's going to be weird
                motionPlayer.Stop();
                motionPlayer = null;
            }
        }
        #endregion
        #region EyeBlink

        private void OnCloseEyeBlink(object sender, RoutedEventArgs e)
        {
            if (model!=null)
            {
                model.UseEyeBlink = false;
            }
        }

        private void OnEnableEyeBlink(object sender, RoutedEventArgs e)
        {
            if (model != null)
            {
                model.UseEyeBlink = true;
            }
        }
        #endregion
    }
}
