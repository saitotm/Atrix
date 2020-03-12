#pragma once

#include <iostream>
#include <cstdint>
#include <ostream>
#include <vector>
#include <string>
#include <math.h>

namespace Atrix
{
template <typename Scalar, int Rows, int Cols>
class Matrix
{
private:
    std::vector<std::vector<Scalar>> data_;

public:
    explicit Matrix();
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
        return Rows;
    }

    inline int cols() const
    {
        return Cols;
    }
};

template <typename Scalar, int Rows, int Cols>
std::ostream &operator<<(std::ostream &, const Matrix<Scalar, Rows, Cols> &);

template <typename Scalar, int Rows, int Cols>
const Matrix<Scalar, Rows, Cols> operator+(const Matrix<Scalar, Rows, Cols> &, const Matrix<Scalar, Rows, Cols> &);

template <typename Scalar, int Rows, int Cols>
const Matrix<Scalar, Rows, Cols> operator-(const Matrix<Scalar, Rows, Cols> &, const Matrix<Scalar, Rows, Cols> &);

template <typename Scalar, int Rows, int Cols>
const Matrix<Scalar, Rows, Cols> operator*(const Matrix<Scalar, Rows, Cols> &, Scalar);

template <typename Scalar, int Rows, int Cols>
const Matrix<Scalar, Rows, Cols> operator*(Scalar, const Matrix<Scalar, Rows, Cols> &);

template <typename Scalar, int Rows, int Cols>
const Matrix<Scalar, Rows, Cols> operator/(const Matrix<Scalar, Rows, Cols> &, Scalar);

template <typename Scalar, int Rows, int Cols, int RowCols>
const Matrix<Scalar, Rows, Cols> operator*(const Matrix<Scalar, Rows, RowCols> &, const Matrix<Scalar, RowCols, Cols> &);

template <typename Scalar, int Rows, int Cols>
Matrix<Scalar, Rows, Cols>::Matrix()
{
    data_ = std::vector<std::vector<Scalar>>(Rows);
    for (int i = 0; i < Rows; ++i)
    {
        data_[i] = std::vector<Scalar>(Cols);
    }
}

template <typename Scalar, int Rows, int Cols>
const Matrix<Scalar, Rows, Cols> Matrix<Scalar, Rows, Cols>::operator-() const
{
    Matrix<Scalar, Rows, Cols> res();
    for (int i = 0; i < Rows; ++i)
    {
        for (int j = 0; j < Cols; ++j)
        {
            res[i][j] = -data_[i][j];
        }
    }
    return res;
}

template <typename Scalar, int Rows, int Cols>
Matrix<Scalar, Rows, Cols> &Matrix<Scalar, Rows, Cols>::operator+=(const Matrix<Scalar, Rows, Cols> &mat)
{
    for (int i = 0; i < Rows; ++i)
    {
        for (int j = 0; j < Cols; ++j)
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
    for (int i = 0; i < Rows; ++i)
    {
        for (int j = 0; j < Cols; ++j)
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
    for (int i = 0; i < Rows; ++i)
    {
        for (int j = 0; j < Cols; ++j)
        {
            res[j][i] = (*this)[i][j];
        }
    }
    return res;
}

template <typename Scalar, int Rows, int Cols>
Matrix<Scalar, 1, Cols> Matrix<Scalar, Rows, Cols>::row(int i) const
{
    Matrix<Scalar, 1, Cols> res;
    for (int j = 0; j < Cols; ++j)
    {
        res[0][j] = (*this)[i][j];
    }
    return res;
}

template <typename Scalar, int Rows, int Cols>
Matrix<Scalar, Rows, 1> Matrix<Scalar, Rows, Cols>::col(int j) const
{
    Matrix<Scalar, Rows, 1> res;
    for (int i = 0; i < Rows; ++i)
    {
        res[i][0] = (*this)[i][j];
    }
    return res;
}

template <typename Scalar, int Rows, int Cols>
std::string Matrix<Scalar, Rows, Cols>::toString() const
{
    std::string str = "[";
    if (Rows == 0 || Cols == 0)
    {
        str += "]";
        return str;
    }

    str += "[";
    str += std::to_string((*this)[0][0]);
    for (int i = 1; i < Cols; ++i)
    {
        str += ", ";
        str += std::to_string((*this)[0][i]);
    }
    for (int i = 1; i < Rows; ++i)
    {
        str += "],\n[";
        str += std::to_string((*this)[i][0]);
        for (int j = 1; j < Cols; ++j)
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

template <typename Scalar, int Rows, int Cols, int RowCols>
const Matrix<Scalar, Rows, Cols> operator*(const Matrix<Scalar, Rows, RowCols> &mat_a, const Matrix<Scalar, RowCols, Cols> &mat_b)
{
    Matrix<Scalar, Rows, Cols> res;
    for (int i = 0; i < Rows; ++i)
    {
        for (int j = 0; j < Cols; ++j)
        {
            Scalar temp = 0;
            for (int k = 0; k < RowCols; ++k)
            {
                temp = mat_a[i][k] * mat_b[k][j];
            }
            res[i][j] = temp;
        }
    }
    return res;
}

template <int Rows, int Cols>
using Matrixf = Matrix<float, Rows, Cols>;

} // namespace Atrix