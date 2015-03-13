#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <array>

namespace Defender
{
template<unsigned int dim>
class Vector final
{
public:
    Vector() = default;

    // Constructor
    template <typename... Args> Vector(Args... args)
    {
        static_assert(dim >= sizeof...(args), "Too many parameters");
        static_assert(dim <= sizeof...(args), "Not enough parameters");
        addValue(0, args...);
    }

    // Get the x value ([0]) for Vector with dim of at least 1
    inline double& x()
    {
        static_assert(dim >= 1, "No x attribute");
        return values[0];
    }

    // Const version
    inline const double& x() const
    {
        static_assert(dim >= 1, "No x attribute");
        return values[0];
    }

    // Get the y value ([1]) for Vector with dim of at least 2
    inline double& y()
    {
        static_assert(dim >= 2, "No y attribute");
        return values[1];
    }

    // Const Version
    inline const double& y() const
    {
        static_assert(dim >= 2, "No y attribute");
        return values[1];
    }

    // Get the z value ([2]) for Vector with dim of at least 3
    inline double& z()
    {
        static_assert(dim >= 3, "No z attribute");
        return values[2];
    }

    // Const version
    inline const double& z() const
    {
        static_assert(dim >= 3, "No z attribute");
        return values[2];
    }

    // += Overload
    inline Vector<dim>& operator += (const Vector<dim> &a)
    {
        for(unsigned int i = 0; i < dim; ++i)
        {
            values[i] += a.values[i];
        }
        return *this;
    }

    // -= Overload
    inline Vector<dim>& operator -= (const Vector<dim> &a)
    {
        for(unsigned int i = 0; i < dim; ++i)
        {
            values[i] -= a.values[i];
        }
        return *this;
    }

    // *= Overload
    inline Vector<dim>& operator *= (const double &a)
    {
        for(unsigned int i = 0; i < dim; ++i)
        {
            values[i] *= a;
        }
        return *this;
    }

    // /= Overload
    inline Vector<dim>& operator /= (const double &a)
    {
        for(unsigned int i = 0; i < dim; ++i)
        {
            values[i] /= a;
        }
        return *this;
    }

    // [] Overload
    inline double& operator [] (const unsigned int& index)
    {
        if (index >= dim) { throw std::range_error("Invalid index"); }
        return values[index];
    }

    // Const version
    inline const double& operator [] (const unsigned int& index) const
    {
        if (index >= dim) { throw std::range_error("Invalid index"); }
        return values[index];
    }

    // Returns the magnitude of the Vector
    // Calculated by the square root of the sum of the squares of each dimention
    inline double magnitude() const
    {
        double value = 0;
        for (unsigned int i = 0; i < dim; ++i)
        {
            value += pow(values[i], 2);
        }
        value = std::sqrt(value);
        return value;
    }

    inline double direction() const;

    // Returns a vector with the same direction if the magnitude was 1
    // Calculated by diving each dimention by the magnitude of the vector{
    inline Vector<dim> normalised() const
    {
        auto i = magnitude();
        auto a = *this / i;
        return a;
    }

private:
    std::array<double, dim> values;

    // These two functions recursively add values into the array based on the
    // passed parameter pack
    inline void addValue(const unsigned int& index, const double& i)
    {
        values[index] = i;
    }

    template <typename... Args>
    inline void addValue(unsigned int index, const double &i, Args... args)
    {
        addValue(index, i);
        addValue(++index, args...);
    }
};

// Returns the direction of the 2D vector
// This is the angle between the horizontal line and the vector line
// Caculated by arctan(y / x)
template <>
inline double Vector<2>::direction() const
{
    return std::atan2(y(), x());
}

using Vector2D = Vector<2>;
using Vector3D = Vector<3>;
}

// + Overload
template<unsigned int dim>
inline Defender::Vector<dim> operator + (Defender::Vector<dim> a,
                                    const Defender::Vector<dim>& b)
{
    a += b;
    return a;
}

// - Overload
template<unsigned int dim>
inline Defender::Vector<dim> operator - (Defender::Vector<dim> a,
                                    const Defender::Vector<dim>& b)
{
    a -= b;
    return a;
}

template<unsigned int dim>
inline Defender::Vector<dim> operator - (const Defender::Vector<dim>& a)
{
    Defender::Vector<dim> b = {};
    b -= a;
    return b;
}

// * Overload
template<unsigned int dim>
inline Defender::Vector<dim> operator * (Defender::Vector<dim> a, const double& b)
{
    a *= b;
    return a;
}

template<unsigned int dim>
inline Defender::Vector<dim> operator * (const double& b, Defender::Vector<dim> a)
{
    a *= b;
    return a;
}

// / Overload
template<unsigned int dim>
inline Defender::Vector<dim> operator / (Defender::Vector<dim> a, const double& b)
{
    a /= b;
    return a;
}

// == Overload
template<unsigned int dim>
inline bool operator == (const Defender::Vector<dim>& a,
                         const Defender::Vector<dim>& b)
{
    return (a.x() == b.x()) && (a.y() == b.y());
}

// != Overload
template<unsigned int dim>
inline bool operator != (const Defender::Vector<dim>& a,
                         const Defender::Vector<dim>& b)
{
    return !(a == b);
}

// < Overload
template<unsigned int dim>
inline bool operator < (const Defender::Vector<dim>& a,
                        const Defender::Vector<dim>& b)
{
    if (a.x() == b.x())
    {
        return a.y() < b.y();
    }
    return a.x() < b.x();
}

#endif // VECTOR_H
