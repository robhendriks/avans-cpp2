#ifndef random_utils_h
#define random_utils_h

#include <random>
#include <ctime>

namespace machiavelli
{
    class randomizer
    {
        int m_min;
        int m_max;
    private:
        std::uniform_int_distribution<int> distribution;
        std::default_random_engine generator;
        
        static std::uniform_int_distribution<int> loop_distribution;
        static std::default_random_engine loop_generator;
        
        static int random_loop_number();
        
    public:
        randomizer(int min, int max);
        
        int random();
    };
}

#endif
