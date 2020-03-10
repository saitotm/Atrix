#pragma once

#include <iostream>
#include <cstdint>
#include <ostream>
#include <vector>
#include <string>
#include <math.h>

namespace matalgo
{
class Matrix
{
protected:
    std::vector<std::vector<float>> data_;

public:
    explicit Matrix();
    explicit Matrix(std::size_t, std::size_t);
    Matrix(const Matrix &) = default;
    Matrix(Matrix &&) noexcept = default;
    Matrix &operator=(const Matrix &) = default;
    Matrix &operator=(Matrix &&) = default;

    const Matrix operator-() const;
    Matrix &operator+=(const Matrix &);
    Matrix &operator-=(const Matrix &);
    Matrix &operator*=(float);
    Matrix &operator/=(float);
    Matrix transpose();
    std::string toString() const;

    inline std::vector<float> &operator[](std::size_t i)
    {
        return data_[i];
    }

    inline const std::vector<float> &operator[](std::size_t i) const
    {
        return data_[i];
    }

    inline std::size_t size_row() const
    {
        return data_.size();
    }

    inline std::size_t size_col() const
    {
        return size_row() == 0 ? 0 : data_[0].size();
    }
};
std::ostream &operator<<(std::ostream &, const Matrix &);
const Matrix operator+(const Matrix &, const Matrix &);
const Matrix operator-(const Matrix &, const Matrix &);
const Matrix operator*(const Matrix &, float);
const Matrix operator*(float, const Matrix &);
const Matrix operator/(const Matrix &, float);
Matrix matmul(const Matrix &, const Matrix &);
} // namespace matalgo