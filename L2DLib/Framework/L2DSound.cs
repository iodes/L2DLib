using System;
using System.Windows.Media;

namespace L2DLib.Framework
{
    public class L2DSound
    {
        #region 속성
        /// <summary>
        /// 대상의 경로를 가져옵니다.
        /// </summary>
        public string Path
        {
            get { return _Path; }
        }
        private string _Path;
        #endregion

        #region 객체
        MediaPlayer player = new MediaPlayer();
        #endregion

        #region 생성자
        public L2DSound(string path)
        {
            _Path = path;
            player.Open(new Uri(path, UriKind.RelativeOrAbsolute));
            player.MediaEnded += Player_MediaEnded;
            player.MediaFailed += Player_MediaFailed;
        }
        #endregion

        #region 사용자 함수
        public void Play()
        {
            player.Play();
        }
        #endregion

        #region 플레이어 이벤트
        private void Player_MediaEnded(object sender, EventArgs e)
        {
            player.Stop();
        }

        private void Player_MediaFailed(object sender, ExceptionEventArgs e)
        {
            Console.WriteLine(e.ErrorException.Message);
        }
        #endregion
    }
}
