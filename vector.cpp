#include "vector.h"

matalgo::Vector::Vector()
{
    data_ = std::vector<float>(0);
}

matalgo::Vector::Vector(std::size_t s)
{
    data_ = std::vector<float>(s);
}

const matalgo::Vector matalgo::Vector::operator-() const
{
    Vector res(size());
    for (std::size_t i = 0; i < res.size(); ++i)
    {
        res[i] = -data_[i];
    }
    return res;
}

matalgo::Vector &matalgo::Vector::operator+=(const matalgo::Vector &v)
{
    if (size() != v.size())
    {
        //例外
    }
    for (std::size_t i = 0; i < size(); ++i)
    {
        data_[i] += v[i];
    }
    return *this;
}

matalgo::Vector &matalgo::Vector::operator-=(const matalgo::Vector &vec)
{
    return *this += (-vec);
}

matalgo::Vector &matalgo::Vector::operator/=(float s)
{
    if (s == 0)
    {
        //devide 0
    }
    return *this *= (1.0f / s);
}

matalgo::Vector &matalgo::Vector::operator*=(float s)
{
    for (std::size_t i = 0; i < size(); ++i)
    {
        data_[i] *= s;
    }
    return *this;
}

std::string matalgo::Vector::toString() const
{
    std::string str = "[";

    //要素数0のときは、(size - 1)のオーバーフローを防ぐために先に処理
    if (size() == 0)
    {
        str += "]";
        return str;
    }

    //sが0の時は(s - 1)はオーバーフロー
    for (std::size_t i = 0; i < size() - 1; ++i)
    {
        str += std::to_string(data_[i]);
        str += ", ";
    }
    str += std::to_string(data_[size() - 1]);
    str += "]";
    return str;
}

float matalgo::Vector::norm() const
{
    float res = 0;
    for (float e : data_)
    {
        res += e * e;
    }
    return sqrt(res);
}

std::ostream &matalgo::operator<<(std::ostream &stream, const matalgo::Vector &v)
{
    const std::string str = v.toString();
    stream << str;
    return stream;
}

const matalgo::Vector matalgo::operator+(const matalgo::Vector &v1, const matalgo::Vector &v2)
{
    return matalgo::Vector(v1) += v2;
}

const matalgo::Vector matalgo::operator-(const matalgo::Vector &v1, const matalgo::Vector &v2)
{
    return matalgo::Vector(v1) -= v2;
}

const matalgo::Vector matalgo::operator*(const matalgo::Vector &v, float s)
{
    return matalgo::Vector(v) *= s;
}

const matalgo::Vector matalgo::operator*(float s, const matalgo::Vector &v)
{
    return matalgo::Vector(v) *= s;
}

const matalgo::Vector matalgo::operator/(const matalgo::Vector &v, float s)
{
    return matalgo::Vector(v) /= s;
}

float matalgo::dot(const matalgo::Vector &v1, const matalgo::Vector &v2)
{
    if (v1.size() != v2.size())
    {
        //例外
    }
    float res = 0;
    for (std::size_t i = 0; i < v1.size(); ++i)
    {
        res += v1[i] * v2[i];
    }
    return res;
}