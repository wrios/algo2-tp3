#include <gtest/gtest.h>
#include "../src/tp3.h"

#include <chrono>
#include <iostream>

TEST(test_multiplicacion, test_matriz_cuadrada) {
    Matriz M1 = {
        {1,2,3,4},
        {5,4,3,2},
        {6,6,6,7},
        {1,2,2,1}
    };

    Matriz M2 = {
        {2,0,0,0},
        {0,2,0,0},
        {0,0,2,0},
        {0,0,0,2}
    };

    auto res = multiplicar (M1,M2);

    // producto con dimension potencia de 2
    auto M3 = multiplicar_strassen(M1,M2,1);
    // EXPECT_EQ(M3, Matriz({
    //                          {2,   4,  6,  8},
    //                          {10,  8,  6,  4},
    //                          {12, 12, 12, 14},
    //                          {2,   4,  4,  2}
    //                      }
    //               ));
    EXPECT_EQ(M3,res);
}

TEST(test_suma, suma_ceros){
  Matriz A = crear(4,0);
  Matriz B = crear(4,0);
  Matriz C = sumar(A,B);
  EXPECT_EQ(A,C);
}

TEST(test_suma, suma_con_cero){
  Matriz A = crear(8,1.2);
  Matriz B = crear(8,0);
  Matriz C = sumar(A,B);
  EXPECT_EQ(A,C);
}

TEST(test_suma, suma_normal){
  Matriz A = crear(3,1.2);
  Matriz B = crear(3,0.1);
  Matriz C = {
    {1.3,1.3,1.3},
    {1.3,1.3,1.3},
    {1.3,1.3,1.3}
  };
  EXPECT_EQ(sumar(A,B),C);
}
TEST(test_strassen, ceros){
  Matriz A = crear(4,0);
  Matriz B = crear(4,0);
  Matriz C = multiplicar_strassen(A,B,2);
  EXPECT_EQ(A,C);
}
// TEST(test_multiplicacion, test_matriz_gigante) {
//     // una matriz un poco más grande
//     Matriz M4 = crear(1024,1.0);
//     auto t0 = std::chrono::system_clock::now();
//     Matriz M5 = multiplicar_strassen(M4, M4, 32);
//     auto t1 = std::chrono::system_clock::now();
//     EXPECT_FLOAT_EQ(M5[0][0], M5.size());

//     auto t2 = std::chrono::system_clock::now();
//     Matriz M6 = multiplicar_strassen(M4, M4, M4.size());
//     auto t3 = std::chrono::system_clock::now();
//     EXPECT_FLOAT_EQ(M5[0][0], M5.size());
//     auto d = double((t1-t0).count()) / (t3-t2).count();
//     std::cout << "D: " << d << std::endl;
//     EXPECT_LT(d, 0.4);
// }
