#include "matrix.h"
#include <utility>
#include <algorithm>

matalgo::Vector solveLinearEqByLU(matalgo::Matrix);
void LUdecomposition(const matalgo::Matrix &, matalgo::Matrix &);
void QRdecomposition(const matalgo::Matrix &, matalgo::Matrix &, matalgo::Matrix &);
matalgo::Matrix solveLinearEqByGaussianElimination(matalgo::Matrix);