#pragma once

#include <matrix.h>

namespace matalgo
{
class Vector
{
private:
    std::vector<float> data_;

public:
    explicit Vector();
    explicit Vector(std::size_t);
    Vector(const Vector &) = default;
    Vector(Vector &&) noexcept = default;
    Vector &operator=(const Vector &) = default;
    Vector &operator=(Vector &&) = default;

    const Vector operator-() const;
    Vector &operator+=(const Vector &);
    Vector &operator*=(float);
    Vector &operator-=(const Vector &);
    Vector &operator/=(float s);
    std::string toString() const;
    float norm() const;

    inline float &operator[](std::size_t i)
    {
        return data_[i];
    }

    inline const float &operator[](std::size_t i) const
    {
        return data_[i];
    }

    inline std::size_t size() const noexcept
    {
        return data_.size();
    }
};

class RowVector : public Matrix
{
public:
    explicit RowVector();
    explicit RowVector(std::size_t);
    RowVector(const RowVector &) = default;
    RowVector(RowVector &&) noexcept = default;
    RowVector &operator=(const RowVector &) = default;
    RowVector &operator=(RowVector &&) = default;

    const RowVector operator-() const;
    RowVector &operator+=(const RowVector &);
    RowVector &operator*=(float);
    RowVector &operator-=(const RowVector &);
    RowVector &operator/=(float s);
    ColVector transpose();
    inline float operator[](std::size_t i)
    {
        return data_[0][i];
    }
};

class ColVector : public Matrix
{
private:
    explicit ColVector();
    explicit ColVector(std::size_t);

    const ColVector operator-() const;
    ColVector &operator+=(const ColVector &);
    ColVector &operator*=(float);
    ColVector &operator-=(const ColVector &);
    ColVector &operator/=(float s);
    RowVector transpose();
    inline float operator[](std::size_t i)
    {
        return data_[i][0];
    }
};

std::ostream &operator<<(std::ostream &stream, const Vector &);
const Vector operator+(const Vector &, const Vector &);
const Vector operator-(const Vector &, const Vector &);
const Vector operator*(const Vector &, float s);
const Vector operator*(float s, const Vector &);
const Vector operator/(const Vector &, float s);
float dot(const Vector &, const Vector &);
} // namespace matalgo