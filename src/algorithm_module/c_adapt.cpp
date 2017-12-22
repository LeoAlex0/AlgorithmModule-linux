#include "algorithm_module.h"
#define C_PUBLIC extern "C" __declspec(dllexport) //C语言的导出标记
namespace GraphAlgorithm
{
    typedef int (*_FirstEdgeAdapter)(int idx_v);
    typedef int (*_NextEdgeAdapter)(int idx_v, int idx_e);
    typedef int (*_EdgeToAdapter)(int idx_v, int idx_e);
    PathType bfsResult;
    std::vector<int> pointVector, edgeVector;
    C_PUBLIC void RunBfs(int idx_start_v, int idx_dest_v,
                       _FirstEdgeAdapter firstOf, 
                       _NextEdgeAdapter nextOf,
                       _EdgeToAdapter destOf)
    {
        bfsResult = bfs(idx_start_v, idx_dest_v, FirstEdgeAdapter(firstOf), NextEdgeAdapter(nextOf), EdgeToAdapter(destOf));
        pointVector = std::vector<int>(bfsResult.first.begin(), bfsResult.first.end());
        edgeVector = std::vector<int>(bfsResult.second.begin(), bfsResult.second.end());

    };
    C_PUBLIC int* GetPointListPointer()
    {
        return &pointVector[0];
    }
    C_PUBLIC int GetPointListLength()
    {
        return pointVector.size();
    }
    C_PUBLIC int* GetEdgeListPointer()
    {
        return &edgeVector[0];
    }
    C_PUBLIC int GetEdgeListLength()
    {
        return edgeVector.size();
    }
}