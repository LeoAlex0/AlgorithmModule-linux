//注意：本文件所有定义类型/函数以AM_做前缀

#pragma once
#include <stdlib.h>

#ifdef WIN32
#define PUBLIC __declspec(dllexport)
#else
#define C_PUBLIC
#endif

#ifdef __cplusplus
extern "C" {
#endif

	//vertexList为路径上所有节点组成的数组(动态)，vetexSize为其大小
	//edgeList为路径上所有边组成的数组(动态)，edgeSize为其大小
	typedef struct {
		int *vertexList, *edgeList;
		size_t vertexSize, edgeSize;
	}AM_PathType;

	//不存在的路径
	const static AM_PathType AM_NIL_PATH = { NULL,NULL,0,0 };
	//不存在的编号
	const int NIL = -1;

	//@Param idx_v:节点编号
	//@Return: 相邻的第一条边的编号，无边返回AW_NIL
	typedef int(*AM_FirstEdgeAdapter)(int idx_v);

	//@Param: idx_v:节点编号
	//@Param: idx_e:当前扫描到的边
	//@Return:返回下一条边的id,无边时返回NIL
	typedef int(*AM_NextEdgeAdapter)(int idx_v, int idx_e);

	//@Param: idx_v:节点编号
	//@Param: idx_e:当前扫描到的边
	//@Return:返回指向节点的id,无边时返回AW_NIL
	typedef int(*AM_EdgeToAdapter)(int idx_v, int idx_e);

	//@Param idx_v:表示此边与v相连
	//@Param idx_e:表示此边编号
	//@Return:节点idx_v的编号为idx_e的边的长度
	typedef double(*AM_EdgeLengthAdapter)(int idx_v, int idx_e);

	//@Param idx_v:表示节点idx_v
	//@Param idx_e:表示与idx_v相连的编号为idx_e的边
	//@Return:节点idx_v的编号为idx_e的边的容量
	typedef double(*AM_EdgeContainAdapter)(int idx_v, int idx_e);

	//@Param idx_start_v:最初的节点编号
	//@Param idx_dest_v:目标节点编号
	//@Param firstOf,nextOf,edgeTo:图的属性
	//@Return: 返回所走的路径
	PUBLIC AM_PathType
		AM_bfs(
			int idx_start_v, int idx_dest_v,
			AM_FirstEdgeAdapter firstOf, AM_NextEdgeAdapter nextOf,
			AM_EdgeToAdapter destOf);

	//@Param idx_start_v:最初的节点编号
	//@Param idx_dest_v:目标节点编号
	//@Param firstOf,nextOf,edgeTo:图的属性
	//@Return: 返回所走的路径的长度
	int
		AM_bfsStep(
			int idx_start_v, int idx_dest_v,
			AM_FirstEdgeAdapter firstOf, AM_NextEdgeAdapter nextOf,
			AM_EdgeToAdapter destOf) {

		AM_PathType tmp = AM_bfs(idx_start_v, idx_dest_v, firstOf, nextOf, destOf);
		free(tmp.edgeList);
		free(tmp.vertexList);
		return tmp.vertexSize - 1;
	}

#ifdef __cplusplus
}
#endif
