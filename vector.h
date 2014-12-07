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

    double& x();
    const double& x() const;
    double& y();
    const double& y() const;
    double& z();
    const double& z() const;

    Vector<dim>& operator += (const Vector<dim> &a);
    Vector<dim>& operator -= (const Vector<dim> &a);
    Vector<dim>& operator *= (const double &a);
    Vector<dim>& operator /= (const double &a);
    double& operator [] (const unsigned int& index);
    const double& operator [] (const unsigned int& index) const;

    double magnitude() const;
    double direction() const;
    Vector<dim> normalised() const;

private:
    std::array<double, dim> values;

    void addValue(const unsigned int& index, const double& i);

    template <typename... Args>
    void addValue(unsigned int index, const double &i, Args... args);
};

using Vector2D = Vector<2>;
using Vector3D = Vector<3>;
}

#include "vector.cpp"
#endif // VECTOR_H
