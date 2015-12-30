using System.Linq;
using System.Collections.Generic;

namespace L2DLib.Framework
{
    public class L2DPose
    {
        #region 속성
        /// <summary>
        /// 파츠 그룹을 설정하거나 가져옵니다.
        /// </summary>
        public List<L2DParts>[] Groups
        {
            get { return _Groups; }
            set { _Groups = value; }
        }
        private List<L2DParts>[] _Groups;

        /// <summary>
        /// 페이드 시간을 설정하거나 가져옵니다.
        /// </summary>
        public int FadeTime
        {
            get { return _FadeTime; }
            set { _FadeTime = value; }
        }
        private int _FadeTime = 500;
        #endregion

        #region 객체
        L2DModel lastModel;
        #endregion

        #region 내부 함수
        private void InitializeParam(L2DModel model)
        {
            int offset = 0;
            for (int i = 0; i < Groups.Count(); i++)
            {
                for (int j = 0; j < Groups[i].Count(); j++)
                {
                    L2DParts parts = Groups[i][j];
                    parts.InitializeIDX(model);

                    int partsIDX = parts.PartsIDX;
                    int paramIDX = parts.ParamIDX;
                    if (partsIDX < 0) continue;

                    model.SetPartsOpacity(partsIDX, j == offset ? 1.0f : 0.0f);
                    model.SetParamFloat(paramIDX, j == offset ? 1.0f : 0.0f);

                    foreach (L2DParts link in parts.Link)
                    {
                        link.InitializeIDX(model);
                    }
                }

                offset += i;
            }
        }
        #endregion

        #region 사용자 함수
        public void UpdateParam(L2DModel model)
        {
            if (model != lastModel)
            {
                InitializeParam(model);
            }
            lastModel = model;

            foreach (List<L2DParts> partsList in Groups)
            {
                foreach (L2DParts parts in partsList)
                {
                    int partsIDX = parts.PartsIDX;
                    int paramIDX = parts.ParamIDX;
                    if (partsIDX < 0) continue;

                    bool visible = (model.GetParamFloat(paramIDX) != 0);
                    model.SetPartsOpacity(partsIDX, (visible ? 1.0f : 0.0f));
                    model.SetParamFloat(paramIDX, (visible ? 1.0f : 0.0f));
                }
            }
        }
        #endregion
    }
}