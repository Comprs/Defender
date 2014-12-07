#ifndef VECTOR_CPP
#define VECTOR_CPP

#include "vector.h"

#include <cmath>

// Constructor
template <unsigned int dim> template<typename... Args>
Defender::Vector<dim>::Vector(Args... args)
{
    static_assert(dim >= sizeof...(args), "Too many parameters");
    static_assert(dim <= sizeof...(args), "Not enough parameters");
    addValue(0, args...);
}

// Get the x value ([0]) for Vector with dim of at least 1
template <unsigned int dim>
double& Defender::Vector<dim>::x()
{
    static_assert(dim >= 1, "No x attribute");
    return values[0];
}

template <unsigned int dim>
const double& Defender::Vector<dim>::x() const
{
    static_assert(dim >= 1, "No x attribute");
    return values[0];
}

// Get the y value ([1]) for Vector with dim of at least 2
template <unsigned int dim>
double& Defender::Vector<dim>::y()
{
    static_assert(dim >= 2, "No y attribute");
    return values[1];
}


template <unsigned int dim>
const double& Defender::Vector<dim>::y() const
{
    static_assert(dim >= 2, "No x attribute");
    return values[1];
}

// Get the z value ([2]) for Vector with dim of at least 3
template <unsigned int dim>
double& Defender::Vector<dim>::z()
{
    static_assert(dim >= 3, "No z attribute");
    return values[2];
}

template <unsigned int dim>
const double& Defender::Vector<dim>::z() const
{
    static_assert(dim >= 3, "No x attribute");
    return values[2];
}

// += Overload
template <unsigned int dim>
Defender::Vector<dim>& Defender::Vector<dim>::operator +=
(const Defender::Vector<dim> &a)
{
    for(unsigned int i = 0; i < dim; ++i)
    {
        values[i] += a.values[i];
    }
    return *this;
}

// -= Overload
template <unsigned int dim>
Defender::Vector<dim>& Defender::Vector<dim>::operator -=
(const Defender::Vector<dim> &a)
{
    for(unsigned int i = 0; i < dim; ++i)
    {
        values[i] -= a.values[i];
    }
    return *this;
}

// *= Overload
template <unsigned int dim>
Defender::Vector<dim>& Defender::Vector<dim>::operator *= (const double &a)
{
    for(unsigned int i = 0; i < dim; ++i)
    {
        values[i] *= a;
    }
    return *this;
}

// /= Overload
template <unsigned int dim>
Defender::Vector<dim>& Defender::Vector<dim>::operator /= (const double &a)
{
    for(unsigned int i = 0; i < dim; ++i)
    {
        values[i] /= a;
    }
    return *this;
}

// [] Overload
template <unsigned int dim>
double& Defender::Vector<dim>::operator [] (const unsigned int& index)
{
    if (index >= dim) { throw std::range_error("Invalid index"); }
    return values[index];
}

template <unsigned int dim>
const double& Defender::Vector<dim>::operator [] (const unsigned int& index) const
{
    if (index >= dim) { throw std::range_error("Invalid index"); }
    return values[index];
}

// Returns the magnitude of the Vector
// Calculated by the square root of the sum of the squares of each dimention
template <unsigned int dim>
double Defender::Vector<dim>::magnitude() const
{
    double value = 0;
    for (unsigned int i = 0; i < dim; ++i)
    {
        value += pow(values[i], 2);
    }
    value = std::sqrt(value);
    return value;
}

// Returns the direction of the 2D vector
// This is the angle between the horizontal line and the vector line
// Caculated by arctan(y / x)
namespace Defender
{
template <>
double Defender::Vector<2>::direction() const
{
    return std::atan(y() / x());
}
}

// Returns a vector with the same direction if the magnitude was 1
// Calculated by diving each dimention by the magnitude of the vector
template <unsigned int dim>
Defender::Vector<dim> Defender::Vector<dim>::normalised() const
{
    auto i = magnitude();
    auto a = *this / i;
    return a;
}

// These two functions recursively add values into the array based on the
// passed parameter pack
template <unsigned int dim>
void Defender::Vector<dim>::addValue(const unsigned int& index, const double& i)
{
    values[index] = i;
}

template <unsigned int dim> template <typename... Args>
void Defender::Vector<dim>::addValue(unsigned int index, const double &i,
                                 Args... args)
{
    addValue(index, i);
    addValue(++index, args...);
}

// + Overload
template<unsigned int dim>
Defender::Vector<dim> operator + (Defender::Vector<dim> a,
                                    const Defender::Vector<dim>& b)
{
    a += b;
    return a;
}

// - Overload
template<unsigned int dim>
Defender::Vector<dim> operator - (Defender::Vector<dim> a,
                                    const Defender::Vector<dim>& b)
{
    a -= b;
    return a;
}

template<unsigned int dim>
Defender::Vector<dim> operator - (const Defender::Vector<dim>& a)
{
    Defender::Vector<dim> b;
    b -= a;
    return b;
}

// * Overload
template<unsigned int dim>
Defender::Vector<dim> operator * (Defender::Vector<dim> a, const double& b)
{
    a *= b;
    return a;
}

template<unsigned int dim>
Defender::Vector<dim> operator * (const double& b, Defender::Vector<dim> a)
{
    a *= b;
    return a;
}

// / Overload
template<unsigned int dim>
Defender::Vector<dim> operator / (Defender::Vector<dim> a, const double& b)
{
    a /= b;
    return a;
}

#endif //VECTOR_CPP
