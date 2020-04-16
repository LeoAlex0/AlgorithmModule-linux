#pragma once

#include "algorithm_module.h"

#ifdef WIN32
#define PUBLIC                                                                 \
    __declspec( dllexport ) // dll输出函数，至于为什么要叫public.......
#else
#define PUBLIC
#endif

#include "graph.hpp"

namespace Algorithm {

/**不存在的编号,长度..*/
constexpr int NIL = -1;

} // namespace Algorithm
