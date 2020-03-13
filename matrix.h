#pragma once

#include "constant.h"
#include <iostream>
#include <cstdint>
#include <ostream>
#include <vector>
#include <string>
#include <math.h>
#include <cassert>

namespace Atrix
{

template <typename Scalar, int Rows, int Cols>
class Matrix
{
private:
    std::vector<std::vector<Scalar>> data_;
    int _rows;
    int _cols;

public:
    explicit Matrix();
    explicit Matrix(int, int);
    //explicit Matrix(std::size_t, std::size_t);
    Matrix(const Matrix &) = default;
    Matrix(Matrix &&) noexcept = default;
    Matrix &operator=(const Matrix &) = default;
    Matrix &operator=(Matrix &&) = default;

    const Matrix operator-() const;
    Matrix &operator+=(const Matrix &);
    Matrix &operator-=(const Matrix &);
    Matrix &operator*=(Scalar);
    Matrix &operator/=(Scalar);

    Matrix<Scalar, Cols, Rows> transpose() const;
    Matrix<Scalar, 1, Cols> row(int) const;
    Matrix<Scalar, Rows, 1> col(int) const;
    static Matrix identity(int i);
    Matrix<Scalar, Dynamic, Dynamic> subMatrix(int, int, int, int);
    Scalar norm2() const;
    Scalar norm() const;
    std::string toString() const;

    inline std::vector<Scalar> &operator[](int i)
    {
        return data_[i];
    }

    inline const std::vector<Scalar> &operator[](int i) const
    {
        return data_[i];
    }

    inline int rows() const
    {
        return Rows == Dynamic ? _rows : Rows;
    }

    inline int cols() const
    {
        return Cols == Dynamic ? _cols : Cols;
    }
};

template <typename Scalar, int Rows, int Cols>
Matrix<Scalar, Rows, Cols>::Matrix() : _rows(Rows), _cols(Cols)
{
    if (Rows == Dynamic)
    {
        _rows = 0;
    }

    if (Cols == Dynamic)
    {
        _cols = 0;
    }

    data_ = std::vector<std::vector<Scalar>>(rows());
    for (int i = 0; i < rows(); ++i)
    {
        data_[i] = std::vector<Scalar>(cols());
    }
}

template <typename Scalar, int Rows, int Cols>
Matrix<Scalar, Rows, Cols>::Matrix(int rows, int cols) : _rows(rows), _cols(cols)
{
    assert(Rows == Dynamic || Rows == rows);
    assert(Cols == Dynamic || Cols == cols);

    data_ = std::vector<std::vector<Scalar>>((*this).rows());
    for (int i = 0; i < (*this).rows(); ++i)
    {
        data_[i] = std::vector<Scalar>((*this).cols());
    }
}

template <typename Scalar, int Rows, int Cols>
const Matrix<Scalar, Rows, Cols> Matrix<Scalar, Rows, Cols>::operator-() const
{
    Matrix<Scalar, Rows, Cols> res();
    for (int i = 0; i < rows(); ++i)
    {
        for (int j = 0; j < cols(); ++j)
        {
            res[i][j] = -data_[i][j];
        }
    }
    return res;
}

template <typename Scalar, int Rows, int Cols>
Matrix<Scalar, Rows, Cols> &Matrix<Scalar, Rows, Cols>::operator+=(const Matrix<Scalar, Rows, Cols> &mat)
{
    for (int i = 0; i < rows(); ++i)
    {
        for (int j = 0; j < cols(); ++j)
        {
            (*this)[i][j] += mat[i][j];
        }
    }
    return *this;
}

template <typename Scalar, int Rows, int Cols>
Matrix<Scalar, Rows, Cols> &Matrix<Scalar, Rows, Cols>::operator-=(const Matrix<Scalar, Rows, Cols> &mat)
{
    return *this += (-mat);
}

template <typename Scalar, int Rows, int Cols>
Matrix<Scalar, Rows, Cols> &Matrix<Scalar, Rows, Cols>::operator*=(Scalar s)
{
    for (int i = 0; i < rows(); ++i)
    {
        for (int j = 0; j < cols(); ++j)
        {
            (*this)[i][j] *= s;
        }
    }
    return *this;
}

template <typename Scalar, int Rows, int Cols>
Matrix<Scalar, Rows, Cols> &Matrix<Scalar, Rows, Cols>::operator/=(Scalar s)
{
    //0除算の例外は未実装
    return *this *= (1 / s);
}

template <typename Scalar, int Rows, int Cols>
Matrix<Scalar, Cols, Rows> Matrix<Scalar, Rows, Cols>::transpose() const
{
    Matrix<Scalar, Cols, Rows> res;
    for (int i = 0; i < rows(); ++i)
    {
        for (int j = 0; j < cols(); ++j)
        {
            res[j][i] = (*this)[i][j];
        }
    }
    return res;
}

template <typename Scalar, int Rows, int Cols>
Matrix<Scalar, 1, Cols> Matrix<Scalar, Rows, Cols>::row(int i) const
{
    Matrix<Scalar, 1, cols()> res;
    for (int j = 0; j < cols(); ++j)
    {
        res[0][j] = (*this)[i][j];
    }
    return res;
}

template <typename Scalar, int Rows, int Cols>
Matrix<Scalar, Rows, 1> Matrix<Scalar, Rows, Cols>::col(int j) const
{
    Matrix<Scalar, Rows, 1> res;
    for (int i = 0; i < rows(); ++i)
    {
        res[i][0] = (*this)[i][j];
    }
    return res;
}

template <typename Scalar, int Rows, int Cols>
Matrix<Scalar, Rows, Cols> Matrix<Scalar, Rows, Cols>::identity(int i)
{
    Matrix<Scalar, Rows, Cols> res(i, i);
    for (int j = 0; j < i; ++j)
    {
        for (int k = 0; k < j; ++k)
        {
            if (j == k)
            {
                res[j][k] = 1;
            }
            else
            {
                res[j][k] = 0;
            }
        }
    }
    return res;
}

template <typename Scalar, int Rows, int Cols>
Scalar Matrix<Scalar, Rows, Cols>::norm() const
{
    return sqrt(norm2());
}

template <typename Scalar, int Rows, int Cols>
Scalar Matrix<Scalar, Rows, Cols>::norm2() const
{
    Scalar res = 0;
    for (int i = 0; i < rows(); ++i)
    {
        for (int j = 0; j < cols(); ++j)
        {
            res += (*this)[i][j] * (*this)[i][j];
        }
    }
    return res;
}

template <typename Scalar, int Rows, int Cols>
std::string Matrix<Scalar, Rows, Cols>::toString() const
{
    std::string str = "[";
    if (rows() == 0 || cols() == 0)
    {
        str += "]";
        return str;
    }

    str += "[";
    str += std::to_string((*this)[0][0]);
    for (int i = 1; i < cols(); ++i)
    {
        str += ", ";
        str += std::to_string((*this)[0][i]);
    }
    for (int i = 1; i < rows(); ++i)
    {
        str += "],\n[";
        str += std::to_string((*this)[i][0]);
        for (int j = 1; j < cols(); ++j)
        {
            str += ", ";
            str += std::to_string((*this)[i][j]);
        }
    }
    str += "]]";
    return str;
}

template <typename Scalar, int Rows, int Cols>
std::ostream &operator<<(std::ostream &stream, const Matrix<Scalar, Rows, Cols> &mat)
{
    stream << mat.toString();
    return stream;
}

template <typename Scalar, int Rows, int Cols>
const Matrix<Scalar, Rows, Cols> operator+(const Matrix<Scalar, Rows, Cols> &mat_a, const Matrix<Scalar, Rows, Cols> &mat_b)
{
    return Matrix<Scalar, Rows, Cols>(mat_a) += mat_b;
}

template <typename Scalar, int Rows, int Cols>
const Matrix<Scalar, Rows, Cols> operator-(const Matrix<Scalar, Rows, Cols> &mat_a, const Matrix<Scalar, Rows, Cols> &mat_b)
{
    return Matrix<Scalar, Rows, Cols>(mat_a) -= mat_b;
}

template <typename Scalar, int Rows, int Cols>
const Matrix<Scalar, Rows, Cols> operator*(const Matrix<Scalar, Rows, Cols> &mat, Scalar s)
{
    return Matrix<Scalar, Rows, Cols>(mat) *= s;
}

template <typename Scalar, int Rows, int Cols>
const Matrix<Scalar, Rows, Cols> operator*(Scalar s, const Matrix<Scalar, Rows, Cols> &mat)
{
    return Matrix<Scalar, Rows, Cols>(mat) *= s;
}

template <typename Scalar, int Rows, int Cols>
const Matrix<Scalar, Rows, Cols> operator/(const Matrix<Scalar, Rows, Cols> &mat, Scalar s)
{
    return Matrix<Scalar, Rows, Cols>(mat) /= s;
}

template <typename Scalar, int RowsA, int ColsA, int RowsB, int ColsB>
const Matrix<Scalar, RowsA, ColsB> operator*(const Matrix<Scalar, RowsA, ColsA> &mat_a, const Matrix<Scalar, RowsB, ColsB> &mat_b)
{
    assert(mat_a.cols() == mat_b.rows());
    int rows = mat_a.rows();
    int cols = mat_b.cols();
    Matrix<Scalar, RowsA, ColsB> res(rows, cols);
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            Scalar temp = 0;
            for (int k = 0; k < mat_a.cols(); ++k)
            {
                temp += mat_a[i][k] * mat_b[k][j];
            }
            res[i][j] = temp;
        }
    }
    return res;
}

template <typename Scalar, int Rows, int Cols>
Matrix<Scalar, Dynamic, Dynamic> Matrix<Scalar, Rows, Cols>::subMatrix(int topLeftx, int topLefty, int bottomRightx, int bottomRighty)
{
    Matrix<Scalar, Dynamic, Dynamic> res(bottomRightx - topLeftx + 1, bottomRighty - topLefty + 1);
    for (int i = topLefty; i <= bottomRighty; ++i)
    {
        for (int j = topLeftx; j <= bottomRightx; ++j)
        {
            res[i - topLefty][j - topLeftx] = (*this)[i][j];
        }
    }
    return res;
}

} // namespace Atrix