#ifndef vector_utils_h
#define vector_utils_h

#include  <random>
#include  <iterator>

namespace vector_utils
{
    template<typename I, typename R>
    inline I find_random(I begin, I end, R& g) {
        std::uniform_int_distribution<> dist(0, std::distance(begin, end) - 1);
        std::advance(begin, dist(g));
        return begin;
    }

    template<typename I>
    inline I find_random(I begin, I end) {
        static std::random_device rd;
        static std::mt19937 gen{rd()};
        return find_random(begin, end, gen);
    }
}
#endif
