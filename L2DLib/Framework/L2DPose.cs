using System.IO;
using System.Linq;
using System.Collections.Generic;
using Newtonsoft.Json.Linq;

namespace L2DLib.Framework
{
    public class L2DPose
    {
        #region 속성
        /// <summary>
        /// 파츠 그룹을 가져옵니다.
        /// </summary>
        public List<L2DParts>[] Groups
        {
            get { return _Groups; }
        }
        private List<L2DParts>[] _Groups;

        /// <summary>
        /// 페이드인 시간을 가져옵니다.
        /// </summary>
        public int FadeTime
        {
            get { return _FadeTime; }
        }
        private int _FadeTime = 500;
        #endregion

        #region 객체
        L2DModel lastModel;
        #endregion

        #region 생성자
        public L2DPose(string path)
        {
            JObject jsonObject = JObject.Parse(File.ReadAllText(path));

            JToken fadeTime;
            jsonObject.TryGetValue("fade_in", out fadeTime);
            if (fadeTime != null)
            {
                _FadeTime = fadeTime.Value<int>();
            }

            List<List<L2DParts>> groupList = new List<List<L2DParts>>();
            foreach (JObject partsResult in jsonObject["parts_visible"].Children().ToList())
            {
                List<L2DParts> partsGroup = new List<L2DParts>();
                foreach (JObject groupResult in partsResult["group"].Children().ToList())
                {
                    string id = groupResult.GetValue("id").Value<string>();
                    List<L2DParts> linkList = new List<L2DParts>();

                    JToken resultLink;
                    groupResult.TryGetValue("link", out resultLink);
                    if (resultLink != null)
                    {
                        foreach (JValue linkResult in resultLink.Children().ToList())
                        {
                            L2DParts linkParts = new L2DParts(linkResult.Value<string>());
                            linkList.Add(linkParts);
                        }
                    }

                    partsGroup.Add(new L2DParts(id, linkList.ToArray()));
                }

                groupList.Add(partsGroup);
            }

            _Groups = groupList.ToArray();
        }
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