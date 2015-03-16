#ifndef PSEUDORANDOMDISTRIBUTION
#define PSEUDORANDOMDISTRIBUTION

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

private:
    param_type parameters;
    int internal_n;
};
}

#endif // PSEUDORANDOMDISTRIBUTION

