#ifndef TP3_IMPL_H
#define TP3_IMPL_H

#include "tp3.h"

#include <limits>
#include <algorithm>

///////////////////////////////////////////////////////////////////////////////
/// EJERCICIO 1
////

template <typename iterator>
std::pair<int,int> minMax(iterator input_begin, iterator input_end){
  int min = int(*input_begin);
  int max = int(*input_begin);
  while (input_begin != input_end){
    if (int(*input_begin) > max)
      max = int(*input_begin);
    if (int(*input_begin) < min)
      min = int(*input_begin);
    input_begin++;
  }
  return std::make_pair(min,max);
}


template <typename iterator, typename bucket>
vector<bucket> generar_buckets(iterator input_begin, iterator input_end) {
  if (input_begin == input_end){
    return vector<bucket>();
  }
  std::pair<int,int> ambos = minMax(input_begin,input_end);
  int min = ambos.first;
  int max = ambos.second;
  vector<bucket> res(max-min+1);
  for (iterator it = input_begin; it != input_end; ++it){
    auto actual = &res[int(*it)-min];
    actual->insert(actual->end(),*it);
  }
    return res;
}

template <typename bucket>
vector<typename bucket::value_type> aplanar_buckets(const std::vector<bucket> & B) {
  vector<typename bucket::value_type> res;
  for (size_t i = 0; i < B.size(); ++i) {
    for (auto it = B[i].begin(); it != B[i].end(); ++it) {
      res.insert(res.end(),*it);
    }
  }
  return res;

}

///////////////////////////////////////////////////////////////////////////////
/// EJERCICIO 2
////

fajo ordenar_por_probabilidad(const fajo& falsos_conocidos, const fajo & a_ordenar) {
  std::pair<int,int> minmax = minMax(falsos_conocidos.begin(), falsos_conocidos.end());
  typedef vector<billete>::const_iterator iter_t;
  typedef std::set<billete> bucket_t;
  size_t n = falsos_conocidos.size();
  size_t m = a_ordenar.size();
  vector<bucket_t> falsosXAnio = generar_buckets<iter_t,bucket_t>(falsos_conocidos.begin(),falsos_conocidos.end());
  fajo res;
  for (size_t i = 0; i < m;++i){
    auto actual = &a_ordenar[i];
    if (falsosXAnio[int(*actual)-minmax.first].count(*actual)){
      billete nuevo(actual.numero_de_serie,probabilidad_max);
      res.push_back(nuevo);
    } else {
      billete nuevo(actual->numero_de_serie,(falsosXAnio[int(*actual)]).size());
      res.push_back(nuevo);
    }
  }
  struct lt{
    bool operator()(const billete& a, const billete& b) const {
      return !(a<b) && !(a==b);
    }
  };
  std::sort(res.begin(), res.end(), lt());
  return res;
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

inline Matriz unir(const Matriz& c11, const Matriz& c12, const Matriz& c21, const Matriz& c22){
  int n = c11.size();
  Matriz res = crear(n*2,0);
  for (int i = 0; i<n; i++){
    for (int j = 0; j < n; j++) {
      res[i][j] += c11[i][j];
      res[i+n][j] += c12[i][j];
      res[i][j+n] += c21[i][j];
      res[i+n][j+n] += c22[i][j];
    }
  }
  return res;
}

inline Matriz multiplicar_strassen(const Matriz& A, const Matriz& B, int K) {
  int n = A.size();
  if (n <= K)
    return multiplicar(A,B);
  Matriz a11 = crear(n/2, 0);
  Matriz a12 = crear(n/2, 0);
  Matriz a21 = crear(n/2, 0);
  Matriz a22 = crear(n/2, 0);
  Matriz b11 = crear(n/2, 0);
  Matriz b12 = crear(n/2, 0);
  Matriz b21 = crear(n/2, 0);
  Matriz b22 = crear(n/2, 0);
  for(int i=0; i<n/2; i++) {
    for(int j=0; j<n/2; j++) {
      a11[i][j] = A[i][j];
      a21[i][j] = A[i+n/2][j];
      a12[i][j] = A[i][j+n/2];
      a22[i][j] = A[i+n/2][j+n/2];

      b11[i][j] = B[i][j];
      b21[i][j] = B[i+n/2][j];
      b12[i][j] = B[i][j+n/2];
      b22[i][j] = B[i+n/2][j+n/2];
    }
  }

  Matriz m1 = multiplicar_strassen(sumar (a11,a22),sumar (b11,b22),K);
  Matriz m2 = multiplicar_strassen(sumar (a21,a22),b11,K);
  Matriz m3 = multiplicar_strassen(a11,restar (b12,b22),K);
  Matriz m4 = multiplicar_strassen(a22,restar (b21,b11),K);
  Matriz m5 = multiplicar_strassen(sumar (a11,a12),b22,K);
  Matriz m6 = multiplicar_strassen(restar (a21,a11),sumar (b11,b12),K);
  Matriz m7 = multiplicar_strassen(restar (a12,a22),sumar (b21,b22),K);

  Matriz c11 = sumar(restar(m4,m5),sumar(m1,m7));
  Matriz c21 = sumar(m3,m5);
  Matriz c12 = sumar(m2,m4);
  Matriz c22 = sumar(restar(m1,m2),sumar(m3,m6));

  Matriz res = unir (c11,c12,c21,c22);

  return res;
}

#endif // TP3_IMPL_H
