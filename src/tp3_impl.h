#ifndef TP3_IMPL_H
#define TP3_IMPL_H

#include "tp3.h"

#include <limits>
#include <algorithm>

///////////////////////////////////////////////////////////////////////////////
/// EJERCICIO 1
////

template <typename iterator, typename bucket>
vector<bucket> generar_buckets(iterator input_begin, iterator input_end) {
    return vector<bucket>();
}

template <typename bucket>
vector<typename bucket::value_type> aplanar_buckets(const std::vector<bucket> & B) {
    return vector<typename bucket::value_type>();
}

///////////////////////////////////////////////////////////////////////////////
/// EJERCICIO 2
////

fajo ordenar_por_probabilidad(const fajo& falsos_conocidos, const fajo & a_ordenar) {
    return a_ordenar;
}

///////////////////////////////////////////////////////////////////////////////
/// EJERCICIO 3
////

inline Matriz multiplicar_strassen(const Matriz& A, const Matriz& B, int K) {
    return multiplicar(A,B);
}

#endif // TP3_IMPL_H
