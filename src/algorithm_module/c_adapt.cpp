#include "algorithm_module.h"
#define C_PUBLIC extern "C" __declspec(dllexport) //C export
namespace Algorithm
{
    namespace Graph
    {
        /*typedef int(*_FirstEdgeAdapter)(int idx_v);
        typedef int(*_NextEdgeAdapter)(int idx_v, int idx_e);
        typedef int(*_EdgeToAdapter)(int idx_v, int idx_e);
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
        }*/

        const int maxn = 30;
        int a, b, t;
        char*** s;

        struct Node
        {
            int r, c, h;
            Node(int r = 0, int c = 0, int h = 0) : r(r), c(c), h(h)
            {
            }
        };

        inline bool inside(const Node& v)
        {
            return
                v.r >= 0 && v.r < a &&
                v.c >= 0 && v.c < b &&
                v.h >= 0 && v.h < t &&
                s[v.h][v.r][v.c] != '#';
        }
        inline int encoder(int h, int r, int c)
        {
            return h * (a*b) + r * b + c;
        }

        inline int walk(int v, int i)
        {
            const static int dr[] = { -1, 0, 1, 0, 0, 0 };
            const static int dc[] = { 0, -1, 0, 1, 0, 0 };
            const static int dh[] = { 0, 0, 0, 0, 1, -1 };
            const Node next(v % (a*b) / b + dr[i], v % b + dc[i], v / (a*b) + dh[i]);
            if (inside(next)) return encoder(next.h, next.r, next.c);
            else return NIL;
        }

        NextEdgeAdapter nextOf =
            [] (int v, int e) -> int
        {
            for (int e1 = e + 1; e1 < 6; e1++)
            {
                if (walk(v, e1) != NIL)
                    return e1;
            }
            return NIL;
        };

        GraphAdapter graph = {
            std::bind2nd(nextOf,-1),
            nextOf,
            walk
        };

        C_PUBLIC int EscapeMaze(int floors, int height, int width, char*** mazeData)
        {
            t = floors;
            a = height;
            b = width;
            s = mazeData;
            int start, dest;
            for (int i = 0; i < t; i++)
            {
                for (int j = 0; j < a; j++)
                {
                    scanf_s("%s", s[i][j], 1024);
                    for (int k = 0; k < b; k++)
                    {
                        if (s[i][j][k] == 'S')
                        {
                            start = encoder(i, j, k);
                        }
                        else if (s[i][j][k] == 'E')
                        {
                            dest = encoder(i, j, k);
                        }
                    }
                }
            }

            return bfsStep(start, dest, graph);
        }
    }
}