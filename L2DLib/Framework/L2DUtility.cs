using L2DLib.Core;

namespace L2DLib.Framework
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
    }
}
