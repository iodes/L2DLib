using System.Security.Permissions;
using System.Runtime.InteropServices;

namespace L2DLib.Core
{
    /// <summary>
    /// L2DNative 라이브러리와 상호 운용시 반환값 처리를 제공합니다.
    /// </summary>
    public static class HRESULT
    {
        [SecurityPermission(SecurityAction.Demand, Flags = SecurityPermissionFlag.UnmanagedCode)]
        public static void Check(int hr)
        {
            Marshal.ThrowExceptionForHR(hr);
        }
    }
}
