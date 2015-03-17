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
        explicit param_type(double c) : parameter_c(c) {}
        double c() const { return parameter_c; }

        friend bool operator == (const param_type& lhs,
                                 const param_type& rhs)
        {
            return lhs.parameter_c == rhs.parameter_c;
        }

    private:
        double parameter_c;
    };
    explicit pseudo_random_distribution(double c = 0.5) : parameters(c),
        internal_n(1) {}
    explicit pseudo_random_distribution(const param_type& params) :
        parameters(params) {}

    param_type param() const { return parameters; }
    void param(const param_type& params) { parameters = params; }

    double c() const { return parameters.c(); }

    result_type min() { return std::numeric_limits<result_type>::min(); }
    result_type max() { return std::numeric_limits<result_type>::max(); }

    void reset() { internal_n = 1; }

    template<typename Generator>
    result_type operator () (Generator& g, const param_type& gen_params)
    {
        double thisChance = gen_params.c() * internal_n;
        bool success = (g() - g.min()) < thisChance * (g.max() - g.min());
        if (success) { internal_n = 1; }
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
    int internal_n;
};

template <class CharT, class Traits>
std::basic_ostream<CharT, Traits>&
operator << (std::basic_ostream<CharT, Traits>& os,
             const pseudo_random_distribution& d)
{
    os << d.parameters.parameter_c << d.internal_n;
    return os;
}

template <class CharT, class Traits>
std::basic_istream<CharT, Traits>&
operator >> (std::basic_istream<CharT, Traits>& is,
             const pseudo_random_distribution& d)
{
    is >> d.parameters.parameter_c >> d.internal_n;
    return is;
}
}

#endif // PSEUDORANDOMDISTRIBUTION

