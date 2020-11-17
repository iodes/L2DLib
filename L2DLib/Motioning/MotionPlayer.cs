using L2DLib.Framework;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace L2DLib.Motioning
{
    /// <summary>
    /// The motion player
    /// </summary>
    public class MotionPlayer
    {
        private readonly L2DView view;

        private bool isPlaying;
        
        private Func<L2DMotion,TimeSpan> delayFactory;
        /// <summary>
        /// Gets the value, the player is playing or not.
        /// </summary>
        public bool IsPlaying => isPlaying;
        /// <summary>
        /// Gets the value, it is attacked the player motions.
        /// </summary>
        public IEnumerable<L2DMotion> Motions { get; }

        private bool loop;
        /// <summary>
        /// Is the motion player loop when the motion collection <see cref="Motions"/> done.
        /// </summary>
        public bool Loop
        {
            get => loop;
            set
            {
                if (loop)
                {
                    Done -= MotionPlayer_Done;
                }
                loop = value;
                if (value)
                {
                    Done += MotionPlayer_Done;
                }
            }
        }

        private void MotionPlayer_Done(MotionPlayer obj)
        {
            obj.Begin();
        }
        /// <summary>
        /// Gets or sets the delay factory.
        /// <para>
        /// It will call when the motion pre done and delay return time.
        /// </para>
        /// </summary>
        /// <exception cref="InvalidOperationException">Throw when the player is playing</exception>
        public Func<L2DMotion,TimeSpan> DelayFactory
        {
            get => delayFactory;
            set
            {
                ThrowIfPlaying();
                delayFactory = value;
            }
        }
        /// <summary>
        /// It will be fired when the motion pre done.
        /// </summary>
        public event Action<MotionPlayer> Done;
        /// <summary>
        /// Initialize the class <see cref="MotionPlayer"/>
        /// </summary>
        /// <param name="view">The l2d view, it can't be <see langword="null"/></param>
        /// <param name="motions">The motion colleciton, it can't be <see langword="null"/></param>
        public MotionPlayer(L2DView view,IEnumerable<L2DMotion> motions)
        {
            this.view = view ?? throw new ArgumentNullException(nameof(view));
            Motions = motions ?? throw new ArgumentNullException(nameof(motions));
        }
        /// <summary>
        /// Start the motion collection play.
        /// </summary>
        public void Begin()
        {
            if (!isPlaying)
            {
                isPlaying = true;
                var enu = Motions.GetEnumerator();
                async void DoNext(L2DView view, bool value)
                {
                    if (value)
                    {
                        if (enu.MoveNext() && isPlaying)//When stop all stop
                        {
                            if (delayFactory != null)
                            {
                                var ts = delayFactory(enu.Current);
                                await Task.Delay(ts);
                            }
                            enu.Current.StartMotion();
                            view.DoWhenMotionFinishedChanged(DoNext);
                            Debug.WriteLine("Complated next", "MotionPlayer");
                        }
                        else
                        {
                            Stop();
                            Done?.Invoke(this);
                            Debug.WriteLine("Done", "MotionPlayer");
                        }
                    }
                    else
                    {
                        if (enu.Current != null)
                        {
                            view.DoWhenMotionFinishedChanged(DoNext);
                        }
                        else
                        {
                            Stop();
                            Done?.Invoke(this);
                        }
                    }
                }
                if (enu.MoveNext())
                {
                    view.DoWhenMotionFinishedChanged(DoNext);
                    enu.Current.StartMotion();
                    Debug.WriteLine("Begin", "MotionPlayer");
                }
            }
        }
        /// <summary>
        /// Stop play
        /// </summary>
        public void Stop()
        {
            if (isPlaying)
            {
                isPlaying = false;
            }
        }
        /// <summary>
        /// Throw if property <see cref="IsPlaying"/> true
        /// </summary>
        /// <exception cref="InvalidOperationException">Throw if <see cref="IsPlaying"/> true</exception>
        protected virtual void ThrowIfPlaying()
        {
            if (IsPlaying)
            {
                throw new InvalidOperationException("Playing state can't do this!");
            }
        }
    }
}
