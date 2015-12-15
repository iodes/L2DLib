using System;
using System.Runtime.InteropServices;

namespace L2DLib.Core
{
    public sealed class LPWSTRArray
    {
        private IntPtr taskAlloc;
        private readonly int _length;
        private IntPtr[] _strings;

        public LPWSTRArray(string[] theArray)
        {
            int sizeIntPtr = IntPtr.Size;
            int neededSize = 0;
            if (theArray != null)
            {
                _length = theArray.Length;
                _strings = new IntPtr[_length];
                neededSize = _length * sizeIntPtr;
                taskAlloc = Marshal.AllocCoTaskMem(neededSize);
                for (int cx = _length - 1; cx >= 0; cx--)
                {
                    _strings[cx] = Marshal.StringToCoTaskMemUni(theArray[cx]);
                    Marshal.WriteIntPtr(taskAlloc, cx * sizeIntPtr, _strings[cx]);
                }
            }
        }

        public int Length
        {
            get { return _length; }
        }

        public IntPtr arrayPtr
        {
            get { return taskAlloc; }

        }

        ~LPWSTRArray()
        {
            if (taskAlloc != IntPtr.Zero)
            {
                Marshal.FreeCoTaskMem(taskAlloc);
                int cx = _length;
                while (cx-- != 0)
                    Marshal.FreeCoTaskMem(_strings[cx]);
            }
        }
    }
}
