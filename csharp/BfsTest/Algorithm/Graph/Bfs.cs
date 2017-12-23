using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Algorithm.Graph
{
    /// <summary>
    /// 返回与节点node相连的第一条边的编号,无边时返回Nil
    /// </summary>
    /// <param name="node">节点编号</param>
    /// <returns></returns>
    public delegate int FirstEdgeAdapter(int node);
    /// <summary>
    /// 返回下一条边的编号,无边时返回Nil
    /// </summary>
    /// <param name="node">节点编号</param>
    /// <param name="edge">当前扫描到的边</param>
    /// <returns></returns>
    public delegate int NextEdgeAdapter(int node, int edge);
    /// <summary>
    /// 返回指向节点的编号,无边时返回Nil
    /// </summary>
    /// <param name="node">节点编号</param>
    /// <param name="edge">当前扫描到的边</param>
    /// <returns></returns>
    public delegate int EdgeToAdapter(int node, int edge);
    /// <summary>
    /// 返回节点node的编号为edge的边的长度
    /// </summary>
    /// <param name="node">表示此边与node相连</param>
    /// <param name="edge">表示此边编号</param>
    /// <returns></returns>
    public delegate double EdgeLengthAdapter(int node, int edge);
    /// <summary>
    /// 返回节点node的编号为edge的边的容量
    /// </summary>
    /// <param name="node">表示节点node</param>
    /// <param name="edge">表示与node相连的编号为edge的边</param>
    /// <returns></returns>
    public delegate double EdgeContainAdapter(int node, int edge);
    /// <summary>
    /// 封装图的属性
    /// </summary>
    public sealed class BfsGraphAdapter
    {
        /// <summary>
        /// 
        /// </summary>
        public FirstEdgeAdapter FirstOf { get; set; }
        /// <summary>
        /// 
        /// </summary>
        public NextEdgeAdapter NextOf { get; set; }
        /// <summary>
        /// 
        /// </summary>
        public EdgeToAdapter DestinationOf { get; set; }
        /// <summary>
        /// 
        /// </summary>
        public EdgeLengthAdapter LengthOf { get; set; }
        /// <summary>
        /// 
        /// </summary>
        public EdgeContainAdapter ContainOf { get; set; }
    }
    /// <summary>
    /// 表示Bfs算法模块
    /// </summary>
    public sealed class Bfs
    {
        /// <summary>
        /// 表示不存在的编号
        /// </summary>
        public const int Nil = -1;
        /// <summary>
        /// 表示空路径
        /// </summary>
        public static readonly (LinkedList<int> Points, LinkedList<int> Edges) NilPath
            = (new LinkedList<int>(), new LinkedList<int>());

        /// <summary>
        /// 获取或设置开始节点的编号
        /// </summary>
        public int StartNode { get; set; }
        /// <summary>
        /// 获取或设置目标节点的编号
        /// </summary>
        public int DestinationNode { get; set; }
        /// <summary>
        /// 获取或设置图的属性
        /// </summary>
        public BfsGraphAdapter Attributes { get; private set; } = new BfsGraphAdapter();
        /// <summary>
        /// 获取所要走的路径
        /// </summary>
        public (LinkedList<int> Points, LinkedList<int> Edges) Path { get; private set; } = NilPath;
        /// <summary>
        /// 获取走过的步数
        /// </summary>
        public int Steps => Path.Points.Count - 1;

        /// <summary>
        /// 初始化Bfs算法模块
        /// </summary>
        public Bfs() { }
        /// <summary>
        /// 运行算法
        /// </summary>
        public void Run()
        {
            var indexList = new LinkedList<int>(new int[]{ StartNode });
            var prevOf = new Dictionary<int, int> { { StartNode, Nil } };
            var prevEdgeOf = new Dictionary<int, int> { { StartNode, Nil } };

            var vNode = indexList.Find(StartNode);
            do
            {
                var v = vNode.Value;
                if (v == DestinationNode)
                {
                    var (points, edges) = NilPath;
                    for (var u = v; u != Nil; u = prevOf[u])
                    {
                        points.AddFirst(u);
                        edges.AddLast(prevEdgeOf[u]);
                    }
                    edges.RemoveFirst();

                    Path = (points, edges);
                    return;
                }
                if (v != StartNode)
                {
                    indexList.RemoveFirst();
                }

                for (var edge = Attributes.FirstOf(v); edge != Nil; edge = Attributes.NextOf(v, edge))
                {
                    var v1 = Attributes.DestinationOf(v, edge);
                    if (prevOf.ContainsKey(v1))
                    {
                        continue;
                    }
                    prevOf.Add(v1, v);
                    prevEdgeOf.Add(v1, edge);
                    indexList.AddLast(v1);
                }
                if (vNode.Next != null)
                {
                    vNode = vNode.Next;
                }
            }
            while (vNode.Next != null);

            Path = NilPath;
        }
    }
}
