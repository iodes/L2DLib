using Newtonsoft.Json;

namespace L2DLib.Framework
{
    public class L2DParts
    {
        /// <summary>
        /// 파츠의 대상 매개변수값을 가져옵니다.
        /// </summary>
        public string ID
        {
            get { return _ID; }
        }
        [JsonProperty("id")]
        private string _ID = null;

        /// <summary>
        /// 파츠와 연결된 파츠의 목록을 가져옵니다.
        /// </summary>
        public string[] Link
        {
            get { return _Link; }
        }
        [JsonProperty("link")]
        private string[] _Link = null;
    }
}
