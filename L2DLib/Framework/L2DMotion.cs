using System;
using L2DLib.Core;

namespace L2DLib.Framework
{
    /// <summary>
    /// Live2D 모션과 관련된 기능을 제공합니다.
    /// </summary>
    public class L2DMotion : L2DBase
    {
        #region 속성
        /// <summary>
        /// 대상의 경로를 가져옵니다.
        /// </summary>
        public string Path
        {
            get { return _Path; }
        }
        protected string _Path;

        /// <summary>
        /// 모션 재생시 재생될 사운드 파일입니다.
        /// </summary>
        public L2DSound Sound
        {
            get { return _Sound; }
            set
            {
                _Sound = value;
            }
        }
        private L2DSound _Sound;

        /// <summary>
        /// 모션의 반복 재생 여부를 가져옵니다.
        /// </summary>
        public bool Loop
        {
            get { return _Loop; }
        }
        private bool _Loop = false;

        /// <summary>
        /// 모션의 페이드인 시간을 가져옵니다.
        /// </summary>
        public int FadeIn
        {
            get { return _FadeIn; }
        }
        private int _FadeIn;

        /// <summary>
        /// 모션의 페이드 아웃 시간을 가져옵니다.
        /// </summary>
        public int FadeOut
        {
            get { return _FadeOut; }
        }
        private int _FadeOut;
        #endregion

        #region 생성자
        /// <summary>
        /// 모션 객체를 생성합니다.
        /// </summary>
        /// <param name="path">모션 파일의 경로입니다.</param>
        public L2DMotion(string path)
        {
            LoadMotion(path);
        }

        /// <summary>
        /// 모션 객체를 생성합니다.
        /// </summary>
        /// <param name="path">모션 파일의 경로입니다.</param>
        /// /// <param name="soundPath">사운드 파일의 경로입니다.</param>
        public L2DMotion(string path, string soundPath)
        {
            LoadMotion(path);
            _Sound = new L2DSound(soundPath);
        }
        #endregion

        #region 내부 함수
        private void LoadMotion(string path)
        {
            _Path = path;
            HRESULT.Check(NativeMethods.LoadMotion(path, out _Handle));
            _IsLoaded = true;
        }
        #endregion

        #region 사용자 함수
        /// <summary>
        /// 모션의 재생을 시작합니다.
        /// </summary>
        public void StartMotion()
        {
            HRESULT.Check(NativeMethods.StartMotion(new IntPtr(Handle)));

            if (Sound != null)
            {
                Sound.Play();
            }
        }

        /// <summary>
        /// 모션의 페이드인 시간을 설정합니다.
        /// </summary>
        /// <param name="msec">애니메이션을 진행할 밀리초단위의 시간입니다.</param>
        public void SetFadeIn(int msec)
        {
            HRESULT.Check(NativeMethods.SetFadeIn(new IntPtr(Handle), msec));
            _FadeIn = msec;
        }

        /// <summary>
        /// 모션의 페이드 아웃 시간을 설정합니다.
        /// </summary>
        /// <param name="msec">애니메이션을 진행할 밀리초단위의 시간입니다.</param>
        public void SetFadeOut(int msec)
        {
            HRESULT.Check(NativeMethods.SetFadeOut(new IntPtr(Handle), msec));
            _FadeOut = msec;
        }

        /// <summary>
        /// 모션의 반복 재생 여부를 설정합니다.
        /// </summary>
        /// <param name="loop">모션의 반복 재생 여부입니다.</param>
        public void SetLoop(bool loop)
        {
            HRESULT.Check(NativeMethods.SetLoop(new IntPtr(Handle), loop));
            _Loop = loop;
        }
        #endregion
    }
}
