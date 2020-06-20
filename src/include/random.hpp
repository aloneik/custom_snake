#pragma once

#include <random>


class UniformRandomNumber
{
public:
    static int getClosed(const int min, const int max)
    {
        return generate(min, max);
    }


private:
    template <typename ElemT, typename = std::enable_if_t<std::is_integral<ElemT>::value>>
    static ElemT generate(const ElemT min, const ElemT max)
    {
        static std::default_random_engine generator;
        static std::uniform_int_distribution<int> distribution(min, max);
        return distribution(generator);
    }
};
