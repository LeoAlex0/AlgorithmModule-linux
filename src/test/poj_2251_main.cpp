// http://poj.org/problem?id=2251
// 这是原题，不过。。因为POJ不支持C++11,所以就算把代码复制粘贴好也不能送上去评测

#include "algorithm_module.hpp"
#include <cstdio>

using namespace Algorithm;
using namespace Algorithm::Graph;

const int maxn = 30;
int       a, b, t;
char      s[ maxn ][ maxn ][ maxn ];

struct Node {
    int r, c, h;
    Node( int r = 0, int c = 0, int h = 0 )
        : r( r )
        , c( c )
        , h( h ) {}
};

inline bool inside( const Node &v ) {
    return v.r >= 0 && v.r < a && v.c >= 0 && v.c < b && v.h >= 0 && v.h < t &&
           s[ v.h ][ v.r ][ v.c ] != '#';
}
inline int encoder( int h, int r, int c ) { return h * ( a * b ) + r * b + c; }

inline int walk( int v, int i ) {
    const static int dr[] = {-1, 0, 1, 0, 0, 0};
    const static int dc[] = {0, -1, 0, 1, 0, 0};
    const static int dh[] = {0, 0, 0, 0, 1, -1};
    const Node       next( v % ( a * b ) / b + dr[ i ], v % b + dc[ i ],
                     v / ( a * b ) + dh[ i ] );
    if ( inside( next ) )
        return encoder( next.h, next.r, next.c );
    else
        return NIL;
}

NextEdgeAdapter nextOf = []( int v, int e ) -> int {
    for ( int e1 = e + 1; e1 < 6; e1++ ) {
        if ( walk( v, e1 ) != NIL ) return e1;
    }
    return NIL;
};

GraphAdapter graph = {std::bind2nd( nextOf, -1 ), nextOf, walk};

int main() {
    int start, dest;

    while ( scanf( "%d%d%d", &t, &a, &b ) == 3 && t ) { //长宽高

        for ( int i = 0; i < t; i++ )
            for ( int j = 0; j < a; j++ ) {
                scanf( "%s", s[ i ][ j ] );
                for ( int k = 0; k < b; k++ )
                    if ( s[ i ][ j ][ k ] == 'S' ) {
                        start = encoder( i, j, k );
                    } else if ( s[ i ][ j ][ k ] == 'E' ) {
                        dest = encoder( i, j, k );
                    }
            }

        const int ans = bfsStep( start, dest, graph );
        if ( ans != NIL )
            printf( "Escaped in %d minute(s).\n", ans );
        else
            printf( "Trapped!\n" );
    }
    return 0;
}
