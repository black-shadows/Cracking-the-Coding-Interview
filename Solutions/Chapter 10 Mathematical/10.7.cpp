/*
 * TASK: Determine the k-th number whose prime factors are only 3, 5 and 7.
 *       The smallest such numbers are 3, 5, 7, 9, 15, 21, 25, 27.
 */

#include <cassert>
#include <deque>
#include <iostream>
#include <limits>
#include <vector>

/**
 * @brief Finds the k-th number of type (3^a)*(5^b)*(7^c) using brute force.
 * @note Complexity: O(k²) in time, O(k) in space.
 */
uint64_t find_number_1(const size_t k)
{
    std::vector<uint64_t> numbers = {3, 5, 7};

    while (numbers.size() < k + 1)
    {
        uint64_t smallest = std::numeric_limits<uint64_t>::max();

        /*
         * multiply each number computed so far by 3, 5 and 7; each
         * resulting value which is larger than numbers.back() is a
         * candidate for the next number in the sequence, and the
         * actual next is the smallest one among all candidates
         */
        for (const uint64_t num : numbers)
        {
            for (const uint64_t x : {3, 5, 7})
            {
                if (numbers.back() < num * x)
                {
                    smallest = std::min(smallest, num * x);
                }
            }
        }

        numbers.push_back(smallest);
    }

    return numbers[k];
}

/**
 * @brief Finds the k-th number of type (3^a)*(5^b)*(7^c) using three queues,
 *        each one containing numbers which must still be multiplied by 3, 5
 *        and 7 respectively at each iteration.
 * @note Complexity: O(k) in both time and space.
 */
uint64_t find_number_2(size_t k)
{
    std::deque<uint64_t> q3 = {uint64_t(1)};
    std::deque<uint64_t> q5 = {uint64_t(1)};
    std::deque<uint64_t> q7 = {uint64_t(1)};

    uint64_t next = uint64_t(1);

    ++k;

    while (k > 0)
    {
        /*
         * compute the next candidates of each queue; if none of the
         * candidates produce a number large than next, just iterate
         * again (but pop the queue whose candidate was the best one),
         * otherwise add the winning candidate to all queues
         */
        uint64_t next3 = uint64_t(3) * q3.front();
        uint64_t next5 = uint64_t(5) * q5.front();
        uint64_t next7 = uint64_t(7) * q7.front();

        /* if next3 is the smallest candidate */
        if (next3 <= next5 && next3 <= next7)
        {
            q3.pop_front();
            if (next3 <= next)
            {
                continue;
            }
            next = next3;
        }
        /* if next5 is the smallest candidate */
        else if (next5 <= next3 && next5 <= next7)
        {
            q5.pop_front();
            if (next5 <= next)
            {
                continue;
            }
            next = next5;
        }
        /* if next7 is the smallest candidate */
        else
        {
            q7.pop_front();
            if (next7 <= next)
            {
                continue;
            }
            next = next7;
        }

        q3.push_back(next);
        q5.push_back(next);
        q7.push_back(next);

        --k;
    }

    return next;
}

/**
 * @brief Returns true if n is an integer whose prime factors are only 3, 5
 *        and 7, false otherwise.
 * @note Complexity: O(log(n)) in time, O(1) in space.
 */
bool is_valid(uint64_t n)
{
    if (n < 3)
    {
        return false;
    }

    while (n != 1)
    {
        uint64_t old_n = n;

        n = (n % 3 == 0) ? n / 3 : n;
        n = (n % 5 == 0) ? n / 5 : n;
        n = (n % 7 == 0) ? n / 7 : n;

        if (n == old_n)
        {
            return false;
        }
    }

    return true;
}

int main()
{
    for (size_t k = 0; k <= 100; ++k)
    {
        uint64_t n1 = find_number_1(k);
        uint64_t n2 = find_number_2(k);

        assert(n1 == n2);
        assert(is_valid(n1));
    }

    std::cout << "passed all tests" << std::endl;
}
