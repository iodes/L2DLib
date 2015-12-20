namespace L2DLib.Framework
{
    /// <summary>
    /// Live2D 객체의 최상위 추상 클래스입니다.
    /// </summary>
    public abstract class L2DBase
    {
        /// <summary>
        /// 대상의 경로를 가져옵니다.
        /// </summary>
        public string Path
        {
            get { return _Path; }
        }
        protected string _Path;

        /// <summary>
        /// 대상의 핸들을 가져옵니다.
        /// </summary>
        public long Handle
        {
            get { return _Handle; }
        }
        protected long _Handle = 0;

        /// <summary>
        /// 대상의 로드 여부를 가져옵니다.
        /// </summary>
        public bool IsLoaded
        {
            get { return _IsLoaded; }
        }
        protected bool _IsLoaded = false;
    }
}
