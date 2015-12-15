using System.Windows;
using System.Runtime.InteropServices;

namespace L2DLib.Core
{
    /// <summary>
    /// L2DNative 라이브러리와 상호 운용에 사용되는 구조체를 제공합니다.
    /// </summary>
    class NativeStructure
    {
        [StructLayout(LayoutKind.Sequential)]
        public struct POINT
        {
            public POINT(Point p)
            {
                x = (int)p.X;
                y = (int)p.Y;
            }

            public int x;
            public int y;
        }
    }
}
