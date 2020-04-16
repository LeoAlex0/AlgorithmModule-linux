#include "segtree.hpp"

namespace Algorithm {

template <class T,
          class = typename std::enable_if<monoid<T>::is_instance>::type>
T operator+( T a, T b ) {
    return monoid<T>::append( a, b );
}

template <typename T, typename... Args, class> T mconcat( Args... args ) {
    return ( args + ... );
}

} // namespace Algorithm
