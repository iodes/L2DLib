namespace L2DLib.Framework
{
    public class L2DGroup
    {
        #region 속성
        /// <summary>
        /// 그룹에 포함된 파츠 목록을 가져옵니다.
        /// </summary>
        public L2DParts[] Parts
        {
            get { return _Parts; }
        }
        private L2DParts[] _Parts = null;
        #endregion

        #region 생성자
        public L2DGroup(L2DParts[] partsArray)
        {
            _Parts = partsArray;
        }
        #endregion
    }
}
