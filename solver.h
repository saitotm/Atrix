#include "type.h"
#include <utility>
#include <algorithm>

template <typename Scalar, int N>
Atrix::Vector<Scalar, N>
    solveLinearEqByLU(Atrix::SquareMatrix<Scalar, N>, Atrix::Vector<Scalar, N>);

template <typename Scalar, int N>
void LUdecomposition(const Atrix::SquareMatrix<Scalar, N> &, Atrix::SquareMatrix<Scalar, N> &);

template <typename Scalar, int Rows, int Cols>
void QRdecomposition(const Atrix::Matrix<Scalar, Rows, Cols> &, Atrix::Matrix &, Atrix::Matrix &);

template <typename Scalar, int Rows, int Cols>
Atrix::Vector<Scalar, Rows>
    solveLinearEqByGaussianElimination(Atrix::Matrix<Scalar, Rows, Cols>);

template <typename Scalar, int N>
Atrix::Vector<Scalar, N>
solveLinearEqByLU(Atrix::SquareMatrix<Scalar, N> mat, Atrix::Vector<Scalar, N> vec)
{
    Atrix::Vector<Scalar, N> b;
    Atrix::Vector<Scalar, N> c;
    Atrix::Vector<Scalar, N> x;

    Atrix::SquareMatrix<Scalar, N> luMat;
    LUdecomposition<Scalar, N>(mat, luMat);
    //Lc = bからcを求める(前進消去)
    for (int i = 0; i < N; ++i)
    {
        c[i][0] = vec[i][0];
        for (int j = 0; j < i; ++j)
        {
            c[i][0] -= luMat[i][j] * c[j][0];
        }
    }

    //Ux = cからxを求める(後退代入)
    for (int i = N - 1; i >= 0; --i)
    {
        x[i][0] = c[i][0];
        for (int j = i + 1; j < N; ++j)
        {
            x[i][0] -= luMat[i][j] * x[j][0];
        }
        x[i][0] /= luMat[i][i];
    }
    return x;
}

template <typename Scalar, int N>
void LUdecomposition(const Atrix::SquareMatrix<Scalar, N> &mat, Atrix::SquareMatrix<Scalar, N> &out)
{
    for (int i = 0; i < N; ++i)
    {
        //Lの計算
        for (int j = 0; j < i; ++j)
        {
            Scalar lu = mat[i][j];
            for (int k = 0; k < j; ++k)
            {
                lu -= out[i][k] * out[k][j];
            }
            out[i][j] = lu / out[j][j];
        }

        //Uの計算
        for (int j = i; j < N; ++j)
        {
            Scalar lu = mat[i][j];
            for (int k = 0; k < i; ++k)
            {
                lu -= out[i][k] * out[k][j];
            }
            out[i][j] = lu;
        }
    }
}

template <typename Scalar, int Rows, int Cols>
Atrix::Vector<Scalar, Rows>
solveLinearEqByGaussianElimination(Atrix::Matrix<Scalar, Rows, Cols> mat)
{
    // Cols == 0の例外処理は未実装
    int pivot = 0;
    for (int i = 0; i < Cols - 1; ++i)
    {
        if (i >= Rows)
        {
            break;
        }
        for (int j = pivot; j < Rows; ++j)
        {
            if (mat[j][i] != 0)
            {
                if (pivot != j)
                {
                    std::swap(mat[j], mat[pivot]);
                }
                mat[pivot] /= mat[pivot][i];
                for (int k = 0; k < Rows; ++k)
                {
                    if (pivot == k || mat[k][i] == 0)
                    {
                        continue;
                    }
                    mat[k] -= mat[pivot] * mat[k][i];
                }
                ++pivot;
                break;
            }
        }
    }
    return mat.row();
}