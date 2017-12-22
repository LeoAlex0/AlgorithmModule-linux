// DllTest.cpp: 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"

#define Public extern "C" __declspec(dllexport)

namespace Test
{
    namespace Test2
    {
        Public int add(int data[2][2])
        {
            return data[0][0] + data[0][1] + data[1][0] + data[1][1];
        }
    }
}