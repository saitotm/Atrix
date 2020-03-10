#include "solver.h"
using namespace matalgo;

int main()
{
    Matrix a(2, 2);
    Matrix b(2, 2);
    a[0][0] = 1;
    a[0][1] = 2;
    a[1][0] = 3;
    a[1][1] = 4;
    b[0][0] = 5;
    b[0][1] = 6;
    b[1][0] = 7;
    b[1][1] = 8;
    std::cout << a << std::endl
              << std::endl;
    std::cout << b << std::endl
              << std::endl;

    std::cout << matmul(a, b) << std::endl;
    return 0;
}