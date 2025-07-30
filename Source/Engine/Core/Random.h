#pragma once
#include <cstdlib>
#include <random>

namespace shovel::random 
{
	// Returns a reference to a random number generator
    inline std::mt19937& generator() 
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        return gen;
    }

	// Seeds the random number generator with a specific value
    inline void seed(unsigned int value) 
    {
        generator().seed(value);
    }

	// Returns a random integer in the range [min, max]
    inline int getInt(int min, int max) 
    {
        std::uniform_int_distribution<> dist(min, max);
        return dist(generator());
    }


	// Returns a random integer in the range (0, max)
    inline int getInt(int max) 
    {
        return getInt(0, max - 1);
    }

	// Returns a random integer in the range [min, max)
    inline int getInt() 
    {
        static std::uniform_int_distribution<> dist;
        return dist(generator());
    }

	// Returns a random float in the range [min, max)
    template <typename T = float>
    inline T getReal(T min, T max) 
    {
        std::uniform_real_distribution<T> dist(min, max);
        return dist(generator());
    }

	// Returns a random float in the range [0, max)
    template <typename T = float>
    inline T getReal(T max) {
        return getReal(static_cast<T>(0), static_cast<T>(max));
    }

	// Returns a random float in the range [0, 1)
    template <typename T = float>
    inline T getReal() {
        static std::uniform_real_distribution<T> dist(static_cast<T>(0), static_cast<T>(1));
        return dist(generator());
    }

	// Returns a random boolean value with a 50% chance of being true or false
    inline bool getBool() {
        static std::bernoulli_distribution dist(0.5);
        return dist(generator());
    }
}

