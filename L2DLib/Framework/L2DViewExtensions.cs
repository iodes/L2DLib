using L2DLib.Motioning;
using System;
using System.Collections.Generic;
using System.Text;

namespace L2DLib.Framework
{
    /// <summary>
    /// The extensions for type <see cref="L2DView"/>
    /// </summary>
    public static class L2DViewExtensions
    {
        /// <summary>
        /// Do when motion finished changed.
        /// <para>
        /// It is dependency <see cref="L2DView.IsMotionFinishedChanged"/> event. When the motion status changed, 
        /// the action <paramref name="action"/> will be call once.
        /// </para>
        /// </summary>
        /// <param name="view">The l2d view, it can't be <see langword="null"/></param>
        /// <param name="action">The action, it can't be <see langword="null"/></param>
        /// <exception cref="ArgumentNullException">When arguments <paramref name="view"/> or <paramref name="action"/> is <see langword="null"/></exception>
        public static void DoWhenMotionFinishedChanged(this L2DView view,Action<L2DView, bool> action)
        {
            if (view is null)
            {
                throw new ArgumentNullException(nameof(view));
            }

            if (action is null)
            {
                throw new ArgumentNullException(nameof(action));
            }
            Action<L2DView, bool> doSomething = null;
            doSomething = (v, value) =>
             {
                 action?.Invoke(view, value);
                 //Only once
                 v.IsMotionFinishedChanged -= doSomething;
             };
            view.IsMotionFinishedChanged += doSomething;
        }
    }
}
