/*
 * TASK: You are given a big file which has 4 billions integers. Assuming that
 *       you have only 1GB of memory available, find an integer value which is
 *       not in the file. Try also solving this problem assuming that you have
 *       very little memory available, e.g. 10MB.
 *
 * NOTE: The solution below assumes that the integer values can be represented
 *       in 32 bits, but will not work if we need 64 bits to represent them.
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

/**
 * @brief Finds a missing integer among the n given integers using a histogram.
 * @note Complexity: O(n) in time, O(1) in space.
 * @note This function uses, in total, less than 300kB of memory.
 */
int get_absent_int(const std::vector<uint32_t>& values)
{
    /* each bucket represents a range [x, x+65536) for some integer x */
    static const uint32_t bucket_size = 65536;

    /* histogram with 65536 buckets: uses slightly more than ~260kB */
    std::vector<uint32_t> histogram(65536, 0);

    for (const uint32_t x : values)
    {
        ++histogram[x / bucket_size];
    }

    /* find which bucket did not get filled up */
    uint32_t xmin = 0;

    for (const uint32_t count : histogram)
    {
        if (count < bucket_size)
        {
            break;
        }

        xmin += bucket_size;
    }

    /* integer range represented by the incomplete bucket: [xmin, xmax) */
    uint32_t xmax = xmin + bucket_size;

    /*
     * go over all input integers and mark all integers seen in [xmin, xmax)
     * as "seen"; this bucket uses ~8kB of memory
     */
    std::vector<bool> seen(bucket_size, false);

    for (const uint32_t x : values)
    {
        if (xmin <= x && x < xmax)
        {
            seen[x - xmin] = true;
        }
    }

    /* determine an integer x in [xmin, xmax) which is missing */
    uint32_t x = xmin;

    while (x < xmax)
    {
        if (seen[x - xmin] == false)
        {
            break;
        }

        ++x;
    }

    return x;
}

int main()
{
    std::random_device device;
    std::mt19937 generator(device());

    std::uniform_int_distribution<uint32_t> distribution;

    for (int i = 0; i < 10; ++i)
    {
        std::vector<uint32_t> values;

        /*
         * here we generate sets of integer values to emulate the input
         * file, but since 4 billion integers would not fit on most
         * modern computers in 2016, we generate sets which are small
         * enough just for testing purposes (with a million values)
         */
        while (values.size() < 1000000)
        {
            values.push_back(distribution(generator));
        }

        uint32_t x = get_absent_int(values);

        assert(std::find(values.begin(), values.end(), x) == values.end());
    }

    std::cout << "passed all random tests" << std::endl;

    return EXIT_SUCCESS;
}
