using System;
using System.IO;
using System.Linq;
using System.Collections.Generic;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace L2DLib.Framework
{
    public class L2DPose
    {
        #region 속성
        /// <summary>
        /// 파츠 그룹을 가져옵니다.
        /// </summary>
        public List<L2DGroup> Groups
        {
            get { return _Groups; }
        }
        private List<L2DGroup> _Groups = new List<L2DGroup>();
        #endregion

        #region 생성자
        public L2DPose(string path)
        {
            JObject jsonObject = JObject.Parse(File.ReadAllText(path));
            foreach (JObject partsResult in jsonObject["parts_visible"].Children().ToList())
            {
                List<L2DParts> partsList = new List<L2DParts>();
                foreach (JObject groupResult in partsResult["group"].Children().ToList())
                {
                    partsList.Add(JsonConvert.DeserializeObject<L2DParts>(groupResult.ToString()));
                }
                _Groups.Add(new L2DGroup(partsList.ToArray()));
            }
        }
        #endregion
    }
}