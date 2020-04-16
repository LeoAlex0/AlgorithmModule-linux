//本文件以八数码问题为测试问题，输出所有可解的情况和其所需的步数，顺便演示一波骚操作

#include "algorithm_module.h"
#include <stdio.h>

int nextOf( int v, int e ) {
    const int dx[] = {0, 1, 0, -1};
    const int dy[] = {1, 0, -1, 0};

    int zero_pos = 0;
    for ( int k = 1; k <= 1E9 && v / k % 10 != 0; k *= 10, zero_pos++ )
        ;
    const int zero_x = zero_pos % 3, zero_y = zero_pos / 3;

    for ( int i = e + 1; i < 4; i++ ) {
        const int x_n = zero_x + dx[ i ], y_n = zero_y + dy[ i ];
        if ( x_n >= 0 && x_n < 3 && y_n >= 0 && y_n < 3 ) return i;
    }
    return AM_NIL;
}

int sum = 0;
int firstOf( int v ) {
    sum += 1;
    printf( "%03d\n%03d\n%03d\n\n", v / 1000 / 1000 % 1000, v / 1000 % 1000,
            v % 1000 );
    return nextOf( v, -1 );
}

int destOf( int v, int e ) {
    const int k[]       = {1,      10,      100,      1000,      10000,
                     100000, 1000000, 10000000, 100000000, 1000000000};
    const int new_pos[] = {3, 1, -3, -1};
    int       zero_pos  = 0;
    for ( int k = 1; k <= 1E9 && v / k % 10 != 0; k *= 10, zero_pos++ )
        ;
    const int cur_num = v / k[ zero_pos + new_pos[ e ] ] % 10;
    return v + cur_num * ( k[ zero_pos ] - k[ zero_pos + new_pos[ e ] ] );
}

int main() {
    const int idx_start_v = 123804765;
    const int idx_end_v   = AM_NIL;

    AM_bfsStep( idx_start_v, idx_end_v, firstOf, nextOf, destOf );
    printf( "%d\n", sum );
    return 0;
}
