#include "begin.h"

#include <type_traits>

namespace Algorithm {

template <typename T> struct monoid {
    // static T              empty();
    // static T              append( T, T );
    static constexpr bool is_instance = false;
};

#include "monoid.h" // MonoidCtx : 记录C上Monoid里的函数

template <typename T,
          typename = typename std::enable_if<monoid<T>::is_instance>::type>
constexpr monoidCtx createCtx() {
    return monoidCtx{
        []() { // empty
            return static_cast<void *>( new T( monoid<T>::empty() ) );
        },
        []( const void *a, const void *b ) { // append
            return static_cast<void *>(
                new T( monoid<T>::append( *static_cast<const T *>( a ),
                                          *static_cast<const T *>( b ) ) ) );
        },
        []( void *a ) { delete static_cast<T *>( a ); }}; // free
}
} // namespace Algorithm
