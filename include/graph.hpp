#include "begin.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <functional>
#include <list>
#include <unordered_map>
#include <utility>

namespace Algorithm::Graph {

//适配器类型声明

/**
 * @param idx_v:节点编号
 * @return:节点idx_v相连的第一条边的编号,无边时返回NIL
 */
typedef std::function<int( int idx_v )> FirstEdgeAdapter;

/**
 * @param: idx_v:节点编号
 * @param: idx_e:当前扫描到的边
 * @return:返回下一条边的id,无边时返回NIL
 */
typedef std::function<int( int idx_v, int idx_e )> NextEdgeAdapter;

/**
 * @param: idx_v:节点编号
 * @param: idx_e:当前扫描到的边
 * @return:返回指向节点的id,无边时返回NIL
 */
typedef std::function<int( int idx_v, int idx_e )> EdgeToAdapter;

/**
 * @param idx_v:表示此边与v相连
 * @param idx_e:表示此边编号
 * @return:节点idx_v的编号为idx_e的边的长度
 */
typedef std::function<double( int idx_v, int idx_e )> EdgeLengthAdapter;

/**
 * @param idx_v:表示节点idx_v
 * @param idx_e:表示与idx_v相连的编号为idx_e的边
 * @return:节点idx_v的编号为idx_e的边的容量
 */
typedef std::function<double( int idx_v, int idx_e )> EdgeContainAdapter;

/**
 * 如果无路径，则点的序列为空
 * @param first:表示点的序列
 * @param second:表示边的序列
 */
typedef std::pair<std::list<int>, std::list<int>> PathType;

/**空路径*/
const static PathType NIL_PATH =
    std::make_pair( std::list<int>(), std::list<int>() );

struct GraphAdapter {
    FirstEdgeAdapter   firstOf;
    NextEdgeAdapter    nextOf;
    EdgeToAdapter      destOf;
    EdgeLengthAdapter  lengthOf;
    EdgeContainAdapter containOf;
};

/**
 * @param idx_start_v:最初的节点编号
 * @param idx_dest_v:目标节点编号
 * @param firstOf,nextOf,edgeTo:图的属性
 * @return: 返回所走的路径
 */
PUBLIC PathType bfs( int idx_start_v, int idx_dest_v,
                     const FirstEdgeAdapter &firstOf,
                     const NextEdgeAdapter & nextOf,
                     const EdgeToAdapter &   destOf );

/**
 * 使用bfs算法求最少步骤的路径
 * @param idx_start_v:最初的节点编号
 * @param idx_dest_v:目标节点编号
 * @param graph:图的属性
 * @return: 返回所走的路径
 */
inline PathType bfs( int idx_start_v, int idx_dest_v,
                     const GraphAdapter &graph ) {
    return bfs( idx_start_v, idx_dest_v, graph.firstOf, graph.nextOf,
                graph.destOf );
}

/**
 * @param idx_start_v:最初的节点编号
 * @param idx_dest_v:目标节点编号
 * @param firstOf,nextOf,edgeTo:图的属性
 * @return: 返回所需的步数
 */
inline int bfsStep( int idx_start_v, int idx_dest_v,
                    const FirstEdgeAdapter &firstOf,
                    const NextEdgeAdapter & nextOf,
                    const EdgeToAdapter &   destOf ) {

    PathType tmp = bfs( idx_start_v, idx_dest_v, firstOf, nextOf, destOf );
    return tmp.first.size() - 1;
};

/**
 * @param idx_start_v:最初的节点编号
 * @param idx_dest_v:目标节点编号
 * @param graph:图的属性
 * @return: 返回所需的步数
 */
inline int bfsStep( int idx_start_v, int idx_dest_v,
                    const GraphAdapter &graph ) {
    return bfsStep( idx_start_v, idx_dest_v, graph.firstOf, graph.nextOf,
                    graph.destOf );
}
} // namespace Algorithm::Graph
