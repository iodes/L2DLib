using L2DLib.Core;

namespace L2DLib.Utility
{
    /// <summary>
    /// Live2D 전반과 관련된 기능을 제공합니다.
    /// </summary>
    public class L2DUtility
    {
        /// <summary>
        /// 확보한 모든 자원을 해제합니다.
        /// </summary>
        public static void Dispose()
        {
            HRESULT.Check(NativeMethods.Dispose());
        }

        /// <summary>
        /// 렌더러에서 사용자 시간을 가져옵니다.
        /// </summary>
        /// <returns></returns>
        public static long GetUserTimeMSec()
        {
            long result = 0;
            HRESULT.Check(NativeMethods.GetUserTimeMSec(out result));

            return result;
        }
    }
}
