#include "monoid.hpp"
#include <iostream>

using namespace std;
using namespace Algorithm;

template <> struct Algorithm::monoid<int> {
    static int            empty() { return 1; }
    static int            append( int a, int b ) { return a * b; }
    static constexpr bool is_instance = true;
};
constexpr monoidCtx intMonoid = createCtx<int>();

int main() {
    printf( "%d\n", monoid<int>::append( 1, 2 ) );
    return 0;
}
