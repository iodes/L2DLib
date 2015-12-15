using System;
using System.Windows;
using System.Runtime.InteropServices;

namespace L2DLib.Core
{
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

        [StructLayout(LayoutKind.Sequential)]
        public struct ARGUMENT
        {
            public IntPtr model;
            public IntPtr textures;
            public IntPtr motions;
        }
    }
}
