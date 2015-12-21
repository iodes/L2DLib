using System;
using L2DLib.Core;
using L2DLib.Utility;
using System.Runtime.InteropServices;

namespace L2DLib.Framework
{
    public class L2DPhysics : L2DBase
    {
        #region 속성
        /// <summary>
        /// 설정값을 설정하거나 가져옵니다.
        /// </summary>
        public PhysicsSetup Setup
        {
            get { return _Setup; }
            set
            {
                _Setup = value;
                UpdateSetup();
            }
        }
        private PhysicsSetup _Setup;

        /// <summary>
        /// 소스 배열을 설정하거나 가져옵니다.
        /// </summary>
        public PhysicsSource[] Sources
        {
            get { return _Sources; }
            set
            {
                _Sources = value;
                UpdateSources();
            }
        }
        private PhysicsSource[] _Sources;

        /// <summary>
        /// 대상 배열을 설정하거나 가져옵니다.
        /// </summary>
        public PhysicsTargets[] Targets
        {
            get { return _Targets; }
            set
            {
                _Targets = value;
                UpdateTargets();
            }
        }
        private PhysicsTargets[] _Targets;
        #endregion

        #region 객체
        long startTimeMSec = 0;
        #endregion

        #region 구조체
        public struct PhysicsSetup
        {
            public float length;
            public float regist;
            public float mass;
        }

        public struct PhysicsSource
        {
            public string id;
            public string ptype;
            public float scale;
            public float weight;
        }

        public struct PhysicsTargets
        {
            public string id;
            public string ptype;
            public float scale;
            public float weight;
        }
        #endregion

        #region 생성자
        public L2DPhysics()
        {
            HRESULT.Check(NativeMethods.CreatePhysics(out _Handle));
            startTimeMSec = L2DUtility.GetUserTimeMSec();
            _IsLoaded = true;
        }
        #endregion

        #region 내부 함수
        private void UpdateSetup()
        {
            HRESULT.Check(NativeMethods.PhysicsSetup(new IntPtr(Handle), Setup.length, Setup.regist, Setup.mass));
        }

        private void UpdateSources()
        {
            foreach (PhysicsSource source in Sources)
            {
                HRESULT.Check(NativeMethods.PhysicsAddSrcParam(new IntPtr(Handle), Marshal.StringToHGlobalAnsi(source.ptype), Marshal.StringToHGlobalAnsi(source.id), source.scale, source.weight));
            }
        }

        private void UpdateTargets()
        {
            foreach (PhysicsTargets target in Targets)
            {
                HRESULT.Check(NativeMethods.PhysicsAddTargetParam(new IntPtr(Handle), Marshal.StringToHGlobalAnsi(target.ptype), Marshal.StringToHGlobalAnsi(target.id), target.scale, target.weight));
            }
        }
        #endregion

        #region 사용자 함수
        public void UpdateParam(L2DModel model)
        {
            HRESULT.Check(NativeMethods.PhysicsUpdate(new IntPtr(Handle), new IntPtr(model.Handle), L2DUtility.GetUserTimeMSec() - startTimeMSec));
        }
        #endregion
    }
}
