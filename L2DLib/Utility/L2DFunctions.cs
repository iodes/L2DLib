using System.IO;
using System.Collections.Generic;
using System.Linq;
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
            string posePath = null;
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
            JToken resultPose;
            jsonObject.TryGetValue("pose", out resultPose);
            if (resultPose != null)
            {
                posePath = FixPath(path, resultPose.Value<string>());
            }

            // - motions
            foreach (JProperty jsonMotion in jsonObject["motions"].Children())
            {
                List<L2DMotion> motionList = new List<L2DMotion>();
                foreach (JArray jsonChildren in jsonMotion.Children().ToList())
                {
                    foreach (JObject result in jsonChildren)
                    {
                        L2DMotion motion = null;
                        string motionFile = FixPath(path, result.GetValue("file").Value<string>());
                        JToken resultSound;
                        result.TryGetValue("sound", out resultSound);

                        if (resultSound == null)
                        {
                            motion = new L2DMotion(motionFile);
                        }
                        else
                        {
                            string soundFile = FixPath(path, resultSound.Value<string>());
                            motion = new L2DMotion(motionFile, soundFile);
                        }

                        JToken resultFadeIn;
                        result.TryGetValue("fade_in", out resultFadeIn);

                        JToken resultFadeOut;
                        result.TryGetValue("fade_out", out resultFadeOut);

                        if (resultFadeIn != null)
                        {
                            motion.SetFadeIn(resultFadeIn.Value<int>());
                        }

                        if (resultFadeOut != null)
                        {
                            motion.SetFadeOut(resultFadeOut.Value<int>());
                        }

                        if (motion != null)
                        {
                            motionList.Add(motion);
                        }
                    }
                }

                motionDictionary.Add(jsonMotion.Name, motionList.ToArray());
            }

            // L2DModel 생성
            L2DModel model = new L2DModel(modelPath);
            model.SetTexture(texturePath);
            model.Motion = motionDictionary;
            if (posePath != null)
            {
                model.Pose = new L2DPose(posePath);
            }

            return model;
        }
        #endregion
    }
}
