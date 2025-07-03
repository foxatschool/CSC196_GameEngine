#pragma once
#include <cstdlib>

namespace shovel 
{
	namespace random 
	{
		/// <summary>
		/// Generates a random integer between 0 and RAND_MAX, inclusive.
		/// </summary>
		/// <returns> A random integer between 0 and RAND_MAX, inclusive.</returns>
		inline int getRandomInt()
		{
			return rand();
		}

		/// <summary>
		/// Generates a random integer between 0 and max - 1, inclusive.
		/// </summary>
		/// <param name="max"></param>
		/// <returns> A random integer between 0 and max - 1, inclusive.</returns>
		inline int getRandomInt(int max)
		{
			return rand() % max;
		}

		/// <summary>
		/// Generates a random integer between min and max, inclusive.
		/// </summary>
		/// <param name="min"></param>
		/// <param name="max"></param>
		/// <returns> A random integer between min and max, inclusive.</returns>
		inline int getRandomInt(int min, int max)
		{
			return min + getRandomInt(max - min + 1);
		}


		/// <summary>
		/// Genreates a random float between 0 and 1.
		/// </summary>
		/// <returns>A random float between 0 and 1.</returns>
		inline float getRandomFloat()
		{
			return rand() / (float)RAND_MAX;
		}
	}
}