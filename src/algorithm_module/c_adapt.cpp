#include "algorithm_module.h"
#define C_PUBLIC extern "C" __declspec(dllexport) //C export
namespace Algorithm
{
    namespace Graph
    {
        const int maxn = 30;
        int a, b, t;
        char s[maxn][maxn][maxn];

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

        C_PUBLIC int EscapeMaze(int floors, int height, int width, char mazeData[maxn][maxn][maxn])
        {
            t = floors;
            a = height;
            b = width;
            int start, dest;
            for (int i = 0; i < t; i++)
            {
                for (int j = 0; j < a; j++)
                {
                    for (int k = 0; k < b; k++)
                    {
                        s[i][j][k] = mazeData[i][j][k];
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