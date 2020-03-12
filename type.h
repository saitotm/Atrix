#pragma once
#include "matrix.h"

namespace Atrix
{
template <int Rows, int Cols>
using Matrixf = Matrix<float, Rows, Cols>;

template <typename Scalar, int Rows>
using Vector = Matrix<Scalar, Rows, 1>;

template <int Rows>
using Vectorf = Vector<float, Rows>;

template <typename Scalar, int Cols>
using RowVector = Matrix<Scalar, 1, Cols>;

template <int Cols>
using RowVectorf = RowVector<float, Cols>;

template <typename Scalar, int N>
using SquareMatrix = Matrix<float, N, N>;

template <int N>
using SquareMatrixf = SquareMatrix<float, N>;

} // namespace Atrix