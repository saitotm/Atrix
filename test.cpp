#include "solver.h"
using namespace Atrix;
#define N 3

int main()
{
    SquareMatrixf<N> a;
    Vectorf<N> b;
    a[0][0] = 1;
    a[0][1] = 1;
    a[0][2] = 1;
    a[1][0] = 1;
    a[1][1] = 2;
    a[1][2] = 2;
    a[2][0] = 2;
    a[2][1] = 3;
    a[2][2] = -4;
    b[0][0] = 6;
    b[1][0] = 11;
    b[2][0] = 3;
    std::cout << a << std::endl
              << std::endl;

    std::cout << b << std::endl << std::endl;
    std::cout << solveLinearEqByLU<float, N>(a, b) << std::endl;
    return 0;
}