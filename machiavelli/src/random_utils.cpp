#include "random_utils.hpp"

namespace machiavelli
{
    std::default_random_engine randomizer::loop_generator(unsigned(time(NULL)));
    std::uniform_int_distribution<int> randomizer::loop_distribution(1, 20);
    
    randomizer::randomizer(int min, int max) : m_min{min}, m_max{max}
    {
        std::default_random_engine generator(unsigned(time(NULL)));
        this->generator = generator;
        
        std::uniform_int_distribution<int> distribution(min, max);
        this->distribution = distribution;
    }
    
    int randomizer::random()
    {
        int i = random_loop_number();
        while (i > 0) {
            distribution(generator);
            i--;
        }
        return distribution(generator);
    }
    
    int randomizer::random_loop_number()
    {
        return loop_distribution(loop_generator);
    }
}
