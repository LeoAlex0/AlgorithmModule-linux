#include "algorithm_module.h"
#define C_PUBLIC extern "C" __declspec(dllexport) //C语言的导出标记
namespace GraphAlgorithm
{
    typedef int (*_FirstEdgeAdapter)(int idx_v);
    typedef int (*_NextEdgeAdapter)(int idx_v, int idx_e);
    typedef int (*_EdgeToAdapter)(int idx_v, int idx_e);
    PathType bfsResult;
    C_PUBLIC void RunBfs(int idx_start_v, int idx_dest_v,
                       _FirstEdgeAdapter firstOf, 
                       _NextEdgeAdapter nextOf,
                       _EdgeToAdapter destOf)
    {
        bfsResult = bfs(idx_start_v, idx_dest_v, FirstEdgeAdapter(firstOf), NextEdgeAdapter(nextOf), EdgeToAdapter(destOf));
    };

}