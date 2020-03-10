#include "matrix.h"

matalgo::Matrix::Matrix()
{
    data_ = std::vector<std::vector<float>>();
}

matalgo::Matrix::Matrix(std::size_t row, std::size_t col)
{
    data_ = std::vector<std::vector<float>>(row);
    for (std::size_t i = 0; i < row; ++i)
    {
        data_[i] = std::vector<float>(col);
    }
}

const matalgo::Matrix matalgo::Matrix::operator-() const
{
    matalgo::Matrix res(size_row(), size_col());
    for (std::size_t i = 0; i < size_row(); ++i)
    {
        for (std::size_t j = 0; j < size_col(); ++j)
        {
            res[i][j] = -data_[i][j];
        }
    }
    return res;
}

matalgo::Matrix &matalgo::Matrix::operator+=(const Matrix &mat)
{
    if ((size_row() != mat.size_row()) || (size_col() != mat.size_col()))
    {
        //例外
    }

    for (std::size_t i = 0; i < size_row(); ++i)
    {
        for (std::size_t j = 0; j < size_col(); ++j)
        {
            data_[i][j] += mat[i][j];
        }
    }

    return *this;
}

matalgo::Matrix &matalgo::Matrix::operator-=(const Matrix &mat)
{
    return *this += (-mat);
}

matalgo::Matrix &matalgo::Matrix::operator*=(float s)
{
    for (auto vec : data_)
    {
        for (auto elm : vec)
        {
            elm *= s;
        }
    }
    return *this;
}

matalgo::Matrix &matalgo::Matrix::operator/=(float s)
{
    if (s == 0)
    {
        //例外
    }

    return *this *= (1.0f / s);
}

matalgo::Matrix matalgo::Matrix::transpose()
{
    matalgo::Matrix res(size_col(), size_row());
    for (std::size_t i = 0; i < size_row(); ++i)
    {
        for (std::size_t j = 0; j < size_col(); ++j)
        {
            res[j][i] = data_[i][j];
        }
    }
    return res;
}

std::string matalgo::Matrix::toString() const
{
    std::string str = "[";
    if (size_col() == 0 || size_row() == 0)
    {
        str += "]";
        return str;
    }

    str += "[";
    str += std::to_string(data_[0][0]);
    for (std::size_t i = 1; i < size_col(); ++i)
    {
        str += ", ";
        str += std::to_string(data_[0][i]);
    }

    for (std::size_t i = 1; i < size_row(); ++i)
    {
        str += "],\n[";
        str += std::to_string(data_[i][0]);
        for (std::size_t j = 1; j < size_col(); ++j)
        {
            str += ", ";
            str += std::to_string(data_[i][j]);
        }
    }
    str += "]]";

    return str;
}

std::ostream &matalgo::operator<<(std::ostream &stream, const matalgo::Matrix &mat)
{
    const std::string str = mat.toString();
    stream << str;
    return stream;
}

const matalgo::Matrix matalgo::operator+(const matalgo::Matrix &mat1, const matalgo::Matrix &mat2)
{
    return matalgo::Matrix(mat1) += mat2;
}

const matalgo::Matrix matalgo::operator-(const matalgo::Matrix &mat1, const matalgo::Matrix &mat2)
{
    return matalgo::Matrix(mat1) -= mat2;
}

const matalgo::Matrix matalgo::operator*(const matalgo::Matrix &mat, float s)
{
    return matalgo::Matrix(mat) *= s;
}

const matalgo::Matrix matalgo::operator*(float s, const matalgo::Matrix &mat)
{
    return matalgo::Matrix(mat) *= s;
}

const matalgo::Matrix matalgo::operator/(const matalgo::Matrix &mat, float s)
{
    return matalgo::Matrix(mat) /= s;
}

matalgo::Matrix matalgo::matmul(const matalgo::Matrix &a, const matalgo::Matrix &b)
{
    matalgo::Matrix res(a.size_col(), b.size_row());
    for (int i = 0; i < res.size_col(); ++i)
    {
        for (int j = 0; j < res.size_row(); ++j)
        {
            float temp = 0;
            for (int k = 0; k < a.size_col(); ++k)
            {
                temp += a[i][k] * b[k][j];
            }
            res[i][j] = temp;
        }
    }
    return res;
}