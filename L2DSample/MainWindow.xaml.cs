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

namespace L2DSample
{
    /// <summary>
    /// MainWindow.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void BtnLoad_Click(object sender, RoutedEventArgs e)
        {
            // Live2D 초기화
            L2DRenderView.Initialize
            (
                @"Resources\haru\haru.moc",
                new string[]
                {
                    @"Resources\haru\haru.1024\texture_00.png",
                    @"Resources\haru\haru.1024\texture_01.png",
                    @"Resources\haru\haru.1024\texture_02.png",
                    null
                }
            );
        }

        private void BtnReset_Click(object sender, RoutedEventArgs e)
        {
            // Live2D 리소스 해제
            L2DRenderView.Dispose();
        }
    }
}
