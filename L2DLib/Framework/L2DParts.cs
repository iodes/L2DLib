namespace L2DLib.Framework
{
    public class L2DParts
    {
        #region 속성
        /// <summary>
        /// 파츠의 대상 매개변수값을 가져옵니다.
        /// </summary>
        public string ID
        {
            get { return _ID; }
        }
        private string _ID = null;

        /// <summary>
        /// 파츠의 매개변수 인덱스를 가져옵니다.
        /// </summary>
        public int ParamIDX
        {
            get { return _ParamIDX; }
        }
        private int _ParamIDX = -1;

        /// <summary>
        /// 파츠의 파츠 인덱스를 가져옵니다.
        /// </summary>
        public int PartsIDX
        {
            get { return _PartsIDX; }
        }
        private int _PartsIDX = -1;

        /// <summary>
        /// 파츠와 연결된 파츠의 목록을 가져옵니다.
        /// </summary>
        public L2DParts[] Link
        {
            get { return _Link; }
        }
        private L2DParts[] _Link = null;
        #endregion

        #region 생성자
        public L2DParts(string ID)
        {
            _ID = ID;
        }

        public L2DParts(string ID, L2DParts[] Link)
        {
            _ID = ID;
            _Link = Link;
        }
        #endregion

        #region 사용자 함수
        public void InitializeIDX(L2DModel model)
        {
            _ParamIDX = model.GetParamIndex("VISIBLE:" + ID);
            _PartsIDX = model.GetPartsDataIndex(ID);
            model.SetParamFloat(ParamIDX, 1);
        }
        #endregion
    }
}
