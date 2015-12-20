using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json.Linq;
using L2DLib.Framework;

namespace L2DLib.Utility
{
    public class L2DFunctions
    {
        #region 내부 함수
        private static string FixPath(string path, string value)
        {
            return (Directory.GetParent(path).FullName + "\\" + value).Replace("/", "\\");
        }
        #endregion

        #region 사용자 함수
        /// <summary>
        /// JSON 파일로 간편하게 모델을 불러옵니다.
        /// </summary>
        /// <param name="path">모델 구성을 포함한 JSON 파일입니다.</param>
        public static L2DModel LoadModel(string path)
        {
            // JSON 분석
            string modelPath;
            string[] texturePath;
            string posePath;
            Dictionary<string, L2DMotion[]> motionDictionary = new Dictionary<string, L2DMotion[]>();
            string parentPath = Directory.GetParent(path).FullName;
            JObject jsonObject = JObject.Parse(File.ReadAllText(path));

            // - model
            modelPath = FixPath(path, jsonObject.GetValue("model").Value<string>());

            // - textures
            texturePath = jsonObject.GetValue("textures").Values<string>().ToArray();
            for (int i = 0; i < texturePath.Length; i++)
            {
                texturePath[i] = FixPath(path, texturePath[i]);
            }

            // - pose
            posePath = FixPath(path, jsonObject.GetValue("pose").Value<string>());

            // - motions
            foreach (JProperty motion in jsonObject["motions"].Children())
            {
                List<L2DMotion> motionList = new List<L2DMotion>();
                foreach (JArray children in motion.Children().ToList())
                {
                    foreach (JObject result in children)
                    {
                        string motionFile = FixPath(path, result.GetValue("file").Value<string>());
                        JToken soundFileToken; result.TryGetValue("sound", out soundFileToken);

                        if (soundFileToken == null)
                        {
                            motionList.Add(new L2DMotion(motionFile));
                        }
                        else
                        {
                            string soundFile = FixPath(path, soundFileToken.Value<string>());
                            motionList.Add(new L2DMotion(motionFile, soundFile));
                        }
                    }
                }

                motionDictionary.Add(motion.Name, motionList.ToArray());
            }

            // L2DModel 생성
            L2DModel model = new L2DModel(modelPath);
            model.SetTexture(texturePath);
            model.Motion = motionDictionary;
            model.Pose = new L2DPose(posePath);

            return model;
        }
        #endregion
    }
}
