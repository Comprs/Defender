#ifndef PSEUDORANDOMDISTRIBUTION
#define PSEUDORANDOMDISTRIBUTION

#include <iostream>
#include <limits>

namespace Defender
{
class pseudo_random_distribution
{
public:
    typedef bool result_type;
    struct param_type
    {
    public:
        typedef pseudo_random_distribution distribution_type;
        explicit param_type(double c, double d) : parameter_c(c),
            parameter_d(d) {}
        double c() const { return parameter_c; }
        double d() const { return parameter_d; }

        friend bool operator == (const param_type& lhs,
                                 const param_type& rhs)
        {
            return lhs.parameter_c == rhs.parameter_c &&
                    lhs.parameter_d == rhs.parameter_d;
        }

    private:
        double parameter_c;
        double parameter_d;
    };
    explicit pseudo_random_distribution(double c = 0.5, double d = 0.01) :
        parameters(c, d), internal_n(0) {}
    explicit pseudo_random_distribution(const param_type& params) :
        parameters(params) {}

    param_type param() const { return parameters; }
    void param(const param_type& params) { parameters = params; }

    double c() const { return parameters.c(); }
    double d() const { return parameters.d(); }

    result_type min() { return std::numeric_limits<result_type>::min(); }
    result_type max() { return std::numeric_limits<result_type>::max(); }

    void reset() { internal_n = 0; }

    template<typename Generator>
    result_type operator () (Generator& g, const param_type& gen_params)
    {
        double thisChance = gen_params.c() * internal_n;
        bool success = (g() - g.min()) < thisChance * (g.max() - g.min());
        if (success) { internal_n = 0; }
        else { internal_n += gen_params.d(); }
        return success;
    }

    template<typename Generator>
    result_type operator () (Generator& g)
    {
        return operator()(g, parameters);
    }

    friend bool operator == (const pseudo_random_distribution& lhs,
                      const pseudo_random_distribution& rhs)
    {
        return (lhs.parameters == rhs.parameters) &&
                (lhs.internal_n == rhs.internal_n);
    }

    friend bool operator != (const pseudo_random_distribution& lhs,
                      const pseudo_random_distribution& rhs)
    {
        return !(lhs == rhs);
    }

private:
    param_type parameters;
    double internal_n;
};

template <class CharT, class Traits>
std::basic_ostream<CharT, Traits>&
operator << (std::basic_ostream<CharT, Traits>& os,
             const pseudo_random_distribution& d)
{
    os << d.parameters.parameter_c << d.parameters.parameter_d << d.internal_n;
    return os;
}

template <class CharT, class Traits>
std::basic_istream<CharT, Traits>&
operator >> (std::basic_istream<CharT, Traits>& is,
             const pseudo_random_distribution& d)
{
    is >> d.parameters.parameter_c >> d.parameters.parameter_d >> d.internal_n;
    return is;
}
}

#endif // PSEUDORANDOMDISTRIBUTION

