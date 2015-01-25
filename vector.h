#ifndef VECTOR_H
#define VECTOR_H

#include <array>

namespace Defender
{
template<unsigned int dim>
class Vector final
{
public:
    Vector() = default;

    template <typename... Args>
    Vector(Args... args);

    inline double& x();
    inline const double& x() const;
    inline double& y();
    inline const double& y() const;
    inline double& z();
    inline const double& z() const;

    inline Vector<dim>& operator += (const Vector<dim> &a);
    inline Vector<dim>& operator -= (const Vector<dim> &a);
    inline Vector<dim>& operator *= (const double &a);
    inline Vector<dim>& operator /= (const double &a);
    inline double& operator [] (const unsigned int& index);
    inline const double& operator [] (const unsigned int& index) const;

    inline double magnitude() const;
    inline double direction() const;
    inline Vector<dim> normalised() const;

private:
    std::array<double, dim> values;

    inline void addValue(const unsigned int& index, const double& i);

    template <typename... Args>
    inline void addValue(unsigned int index, const double &i, Args... args);
};

using Vector2D = Vector<2>;
using Vector3D = Vector<3>;
}

#include "vector.cpp"
#endif // VECTOR_H
