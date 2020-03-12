#include "solver.h"
//ガウスの消去法による一次方程式solver

template <typename Scalar, int Rows, int Cols>
Atrix::Vector<Scalar, Rows> solveLinearEqByGaussianElimination(Atrix::Matrix<Scalar, Rows, Cols> mat)
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
}

//LU分解による一次方程式solver
matalgo::Vector solveLinearEqByLU(matalgo::Matrix mat)
{
    matalgo::Vector b(mat.size_row());
    matalgo::Vector c(mat.size_row());
    matalgo::Vector x(mat.size_row());
    for (std::size_t i = 0; i < mat.size_row(); ++i)
    {
        b[i] = mat[i][mat.size_col() - 1];
    }

    matalgo::Matrix luMat(mat.size_row(), mat.size_col());
    LUdecomposition(mat, luMat);
    //Lc = bからcを求める(前進消去)
    for (std::size_t i = 0; i < mat.size_row(); ++i)
    {
        c[i] = b[i];
        for (std::size_t j = 0; j < i; ++j)
        {
            c[i] -= luMat[i][j] * c[j];
        }
    }

    //Ux = cからxを求める(後退代入)
    for (int i = mat.size_row() - 1; i >= 0; --i)
    {
        x[i] = c[i];
        for (std::size_t j = i + 1; j < mat.size_row(); ++j)
        {
            x[i] -= luMat[i][j] * x[j];
        }
        x[i] /= luMat[i][i];
    }
    return x;
}

//LU分解アルゴリズム
void LUdecomposition(const matalgo::Matrix &mat, matalgo::Matrix &out)
{
    if (mat.size_col() == 0 || mat.size_row() == 0)
    {
    }
    std::size_t imax = std::min(mat.size_row(), mat.size_col());

    for (std::size_t i = 0; i < imax; ++i)
    {
        //Lの計算
        for (std::size_t j = 0; j < i; ++j)
        {
            float lu = mat[i][j];
            for (std::size_t k = 0; k < j; ++k)
            {
                lu -= out[i][k] * out[k][j];
            }
            out[i][j] = lu / out[j][j];
        }

        //Uの計算
        for (std::size_t j = i; j < mat.size_col(); ++j)
        {
            float lu = mat[i][j];
            for (std::size_t k = 0; k < i; ++k)
            {
                float l = mat[i][k];
                float u = mat[k][j];
                lu -= out[i][k] * out[k][j];
            }
            out[i][j] = lu;
        }
    }
}

//QR分解アルゴリズム
void QRdecomposition(const matalgo::Matrix &mat, matalgo::Matrix &qt, matalgo::Matrix &r)
{
    //matalgo::Matrix qt(mat.size_row(), mat.size_row());
    r = mat;
    for (int i = 0; i < qt.size_row(); ++i)
    {
        for (int j = 0; j < qt.size_col(); ++j)
        {
            qt[i][j] = 0;
        }
    }
    for (int i = 0; i < qt.size_row(); ++i)
    {
        qt[i][i] = 1;
    }

    for (int i = 0; i < mat.size_row(); ++i)
    {
        matalgo::Vector x(mat.size_row() - i);
        matalgo::Vector u(mat.size_row() - i);
        for (int j = 0; j < x.size(); ++j)
        {
            x[j] = mat[i][j];
        }
        //yの先頭要素
        float y0 = x.norm();
        //xとyの先頭要素は異符号にする(桁落ちを防ぐ)
        if (x[0] < 0)
        {
            x[0] += y0;
        }
        else
        {
            x[0] -= y0;
        }
        x /= x.norm();

        matalgo::Matrix c(mat.size_row() - i, mat.size_col() - i);
        matalgo::Matrix c_new;
        for (int j = 0; j < c.size_row(); ++j)
        {
            for (int k = 0; k < c.size_col(); ++k)
            {
                c[j][k] = mat[j + i][k + i];
            }
        }
        c_new = c;
        matalgo::Matrix temp(c.size_row(), c.size_col());
        matalgo::Matrix qt_new;
        for (int j = 0; j < c.size_col(); ++j)
        {
            float xc = 0;
            for (int k = 0; k < x.size(); ++k)
            {
                xc += x[k] * c[k][j];
            }
            for (int k = 0; k < temp.size_row(); ++k)
            {
                temp[k][j] = xc;
            }
        }
        for (int j = 0; j < x.size(); ++j)
        {
            temp[j] *= x[j];
        }
        temp *= 2;

        c_new -= temp;

        for (int j = 0; i < c_new.size_row(); ++i)
        {
            for (int k = 0; j < c_new.size_col(); ++j)
            {
                r[j + i][j + i] = c_new[j][k];
            }
        }

        qt_new = matalgo::Matrix(qt.size_row() - i, qt.size_col());
        temp = matalgo::Matrix(qt.size_row() - i, qt.size_col());
        for (int j = 0; j < temp.size_row(); ++j)
        {
            temp[j] = qt[j + i];
        }
        qt_new = temp;
        for (int j = 0; j < temp.size_col(); ++j)
        {
            float tx = 0;
            for (int k = 0; k < temp.size_row(); ++k)
            {
                tx += temp[k][j] * x[k];
            }
            for (int k = 0; k < temp.size_row(); ++k)
            {
                temp[k][j] = tx;
            }
        }
        for (int j = 0; j < temp.size_row(); ++j)
        {
            temp[j] *= 2 * x[j];
        }
        qt_new -= temp;

        for (int j = 0; j < qt_new.size_row(); ++j)
        {
            for (int k = 0; k < qt_new.size_col(); ++k)
            {
                qt[j + i][k + i] = qt_new[j][k];
            }
        }
    }
}