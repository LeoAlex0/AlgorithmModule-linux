//注意：本文件所有定义类型/函数以AM_做前缀

#ifdef WIN32
#define C_PUBLIC extern "C" __declspec(dllexport) //C语言的导出标记
#elif defined (__cplusplus)
#define C_PUBLIC extern	"C"
#else
#define C_PUBLIC

//vertexList为路径上所有节点组成的数组(动态)，vetexSize为其大小
//edgeList为路径上所有边组成的数组(动态)，edgeSize为其大小
typedef struct{
  int *vertexList,vertexSize;
  int *edgeList,edgeSize;
}AM_PathType;

//不存在的路径
const static PathType AM_NILPATH={NULL,0,NULL,0};
//不存在的编号
const int NIL=-1;

//@Param idx_v:节点编号
//Return: 相邻的第一条边的编号，无边返回AW_NIL;
typedef int (*AM_FirstEdgeAdapter)(int idx_v);

//@Param: idx_v:节点编号
//@Param: idx_e:当前扫描到的边
//@Return:返回下一条边的id,无边时返回NIL
typedef int (*AM_NextEdgeAdapter)(int idx_v, int idx_e);

//@Param: idx_v:节点编号
//@Param: idx_e:当前扫描到的边
//@Return:返回指向节点的id,无边时返回AW_NIL
typedef int (*AM_EdgeToAdapter)(int idx_v, int idx_e);

//@Param idx_v:表示此边与v相连
//@Param idx_e:表示此边编号
//@Return:节点idx_v的编号为idx_e的边的长度
typedef double (*AM_EdgeLengthAdapter)(int idx_v, int idx_e);

//@Param idx_v:表示节点idx_v
//@Param idx_e:表示与idx_v相连的编号为idx_e的边
//@Return:节点idx_v的编号为idx_e的边的容量
typedef double (*AM_EdgeContainAdapter)(int idx_v, int idx_e) EdgeContainAdapter;

//@Param idx_start_v:最初的节点编号
//@Param idx_dest_v:目标节点编号
//@Param firstOf,nextOf,edgeTo:图的属性
//@Return: 返回所走的路径
C_PUBLIC AM_PathType
AM_bfs(int idx_start_v,int idx_dest_v,
    AM_FirstEdgeAdapter firstOf,AM_NextEdgeAdapter nextOf
    AM_EdgeToAdapter destOf);
