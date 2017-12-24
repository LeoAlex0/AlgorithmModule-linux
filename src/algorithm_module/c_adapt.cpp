#include "algorithm_module.h"
#include "c_algorithm_module.h"

AM_PathType PathType_cast(const Algorithm::Graph::PathType& a) {
	if (a == Algorithm::Graph::NIL_PATH)
		return AM_NIL_PATH;

	AM_PathType ret;
	ret.vertexSize = a.first.size();
	ret.vertexList = (int*)malloc(sizeof(int)*ret.vertexSize);
	int idx = 0;
	for (int v : a.first)
		ret.vertexList[idx++] = v;

	ret.edgeSize = a.second.size();
	ret.edgeList = (int*)malloc(sizeof(int)*ret.edgeSize);
	idx = 0;
	for (int e : a.second)
		ret.edgeList[idx++] = e;
	return ret;
}

C_PUBLIC AM_PathType
AM_bfs(
	int idx_start_v,int idx_dest_v,
	AM_FirstEdgeAdapter firstOf,AM_NextEdgeAdapter nextOf,
	AM_EdgeToAdapter destOf){

	return PathType_cast(Algorithm::Graph::bfs(
		idx_start_v, idx_dest_v,
		firstOf, nextOf, destOf));
}
