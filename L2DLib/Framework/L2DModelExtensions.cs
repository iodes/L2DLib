using L2DLib.Motioning;
using System;
using System.Collections.Generic;

namespace L2DLib.Framework
{
    /// <summary>
    /// The extensions for type <see cref="L2DModel"/>
    /// </summary>
    public static class L2DModelExtensions
    {
        /// <summary>
        /// For each <see cref="L2DModel.Motion"/> do <paramref name="action"/>
        /// </summary>
        /// <remarks>
        /// It will want to do anything for all or any motions.
        /// </remarks>
        /// <param name="model">The l2d model</param>
        /// <param name="action">The action</param>
        public static void DoMotion(this L2DModel model, Action<L2DMotion> action)
        {
            if (model.Motion != null)
            {
                foreach (var item in model.Motion)
                {
                    foreach (var m in item.Value)
                    {
                        action?.Invoke(m);
                    }
                }
            }
        }
        /// <summary>
        /// Set the fade in with value <paramref name="millsec"/> to each <see cref="L2DModel.Motion"/>
        /// </summary>
        /// <param name="model">The l2d model</param>
        /// <param name="millsec">Fade millsecond</param>
        public static void SetFadeIn(this L2DModel model,int millsec)
        {
            model.DoMotion(x => x.SetFadeIn(millsec));
        }
        /// <summary>
        /// Set the fade out with value <paramref name="millsec"/> to each <see cref="L2DModel.Motion"/>
        /// </summary>
        /// <param name="model">The l2d model</param>
        /// <param name="millsec">Fade millsecond</param>
        public static void SetFadeOut(this L2DModel model, int millsec)
        {
            model.DoMotion(x => x.SetFadeOut(millsec));
        }
        /// <summary>
        /// The extension to easy create <see cref="MotionPlayer"/> with <paramref name="view"/>
        /// </summary>
        /// <param name="model">The l2d model</param>
        /// <param name="millsec">Fade millsecond</param>
        /// <exception cref="ArgumentNullException">When <paramref name="model"/>, <paramref name="view"/> or <paramref name="key"/> <see langword="null"/></exception>
        /// <exception cref="KeyNotFoundException">When given key <paramref name="key"/> not in <see cref="L2DModel.Motion"/></exception>
        public static MotionPlayer CreatePlayer(this L2DModel model,L2DView view,string key)
        {
            if (model is null)
            {
                throw new ArgumentNullException(nameof(model));
            }

            if (view is null)
            {
                throw new ArgumentNullException(nameof(view));
            }

            if (key is null)
            {
                throw new ArgumentNullException(nameof(key));
            }

            var val = model.Motion[key];
            return new MotionPlayer(view,val);
        }
    }
}
