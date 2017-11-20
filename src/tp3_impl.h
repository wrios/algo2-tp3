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

inline Matriz sumar (const Matriz& A, const Matriz& B){
  Matriz res = crear(A.size(),0);
  int fila = 0;
  int col = 0;
  while (fila < A.size()){
    col = 0;
    while (col < A.size()){
      res[fila][col] = A[fila][col] + B[fila][col];
      col++;
    }
    fila++;
  }
  return res;
}

inline Matriz restar (const Matriz& A, const Matriz& B){
  Matriz res = crear(A.size(),0);
  int fila = 0;
  int col = 0;
  while (fila < A.size()){
    col = 0;
    while (col < A.size()){
      res[fila][col] = A[fila][col] - B[fila][col];
      col++;
    }
    fila++;
  }
  return res;
}


inline Matriz multiplicar_strassen(const Matriz& A, const Matriz& B, int K) {
  int n = A.size();
  if (n <= K)
    return multiplicar(A,B);

  Matriz a11 (&A[0][0],&A[n/2 -1][n/2 -1]);
  Matriz a12 (&A[n/2 -1][0],&A[0][n/2 -1]);
  Matriz a21 (&A[0][n/2 -1],&A[0][n/2 -1]);
  Matriz a22 (&A[n/2 -1][n/2 -1],&A[n][n]);

  Matriz b11 (&B[0][0],&B[n/2 -1][n/2 -1]);
  Matriz b12 (&B[n/2 -1][0],&B[0][n/2 -1]);
  Matriz b21 (&B[0][n/2 -1],&B[0][n/2 -1]);
  Matriz b22 (&B[n/2 -1][n/2 -1],&B[n][n]);

  Matriz m1a = sumar (a11,a22);
  Matriz m1b = sumar (b11,b22);
  Matriz m1 = multiplicar_strassen(m1a,m1b,K);

  Matriz m2a = sumar (a21,a22);
  Matriz m2 = multiplicar_strassen(m2a,b11,K);

  Matriz m3b = restar (a12,b22);
  Matriz m3 = multiplicar_strassen(a11,m3b,K);

  Matriz m4b = restar (b21,b22);
  Matriz m4 = multiplicar_strassen(a22,m4b,K);

  Matriz m5a = sumar (a11,a12);
  Matriz m5 = multiplicar_strassen(m5a,b22,K);

  Matriz m6a = restar (a21,a11);
  Matriz m6b = sumar (b11,b12);
  Matriz m6 = multiplicar_strassen(m6a,m6b,K);

  Matriz m7a = restar (a12,a22);
  Matriz m7b = sumar (b21,b22);
  Matriz m7 = multiplicar_strassen(m7a,m7b,K);

  Matriz c11 = restar(sumar(m1,m4),sumar(m5,m7));
  Matriz c12 = sumar(m3,m5);
  Matriz c21 = sumar(m2,m4);
  Matriz c22 = sumar(restar(m1,m2),sumar(m3,m6));

  return multiplicar(A,B);
}

#endif // TP3_IMPL_H
