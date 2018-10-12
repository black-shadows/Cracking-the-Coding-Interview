/*
 * TASK: You are given an array storing numbers in [0,32000). Using only 4kB of
 *       memory, print all numbers which appear at least twice in the array.
 *
 * NOTE: I have slightly modified the original question since requiring that
 *       the array has all numbers in [0,N] for some N in [0,32000) does not add
 *       any complexity to the problem.
 */

#include <algorithm>
#include <bitset>
#include <cassert>
#include <iostream>
#include <vector>

/**
 * @brief Returns a bitset indicating which numbers in an array of size n are
 *        duplicates, where the array numbers are in the range [0,32000).
 * @note Complexity: O(n) in time, O(1) in space.
 * @note This function uses, in total, 4002 bytes of memory to detect
 *       duplicates, but since we are returning a bitset with 32000 bits, it
 *       uses 8002 bytes in total (this would not be the case if we merely
 *       printed the duplicate values).
 */
std::bitset<32000> get_duplicates(const std::vector<uint16_t>& values)
{
    std::bitset<32000> seen(false);
    std::bitset<32000> duplicate(false);

    for (const uint16_t x : values)
    {
        if (seen[x] == true)
        {
            duplicate[x] = true;
        }
        else
        {
            seen[x] = true;
        }
    }

    return duplicate;
}

/**
 * @brief Returns a random vector containing n integer values in [0,32000).
 * @note Complexity: O(n) in both time and space.
 */
std::vector<uint16_t> random_vector(const size_t n)
{
    static std::random_device device;
    static std::mt19937 generator(device());

    std::uniform_int_distribution<uint16_t> distribution(0, 31999);

    std::vector<uint16_t> values;

    while (values.size() < n)
    {
        values.push_back(distribution(generator));
    }

    return values;
}

int main()
{
    for (size_t n = 0; n <= 100000; n += 1000)
    {
        std::vector<uint16_t> values = random_vector(n);

        std::bitset<32000> duplicates = get_duplicates(values);

        std::sort(values.begin(), values.end());

        for (size_t i = 1; i + 1 < values.size(); ++i)
        {
            bool is_duplicate =
                (values[i] == values[i - 1]) || (values[i] == values[i + 1]);

            assert(duplicates[values[i]] == is_duplicate);
        }

        std::cout << "passed random test for array of size " << n << std::endl;
    }

    return EXIT_SUCCESS;
}
