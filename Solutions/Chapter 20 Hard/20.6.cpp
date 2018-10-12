/*
 * TASK: Given a very large array containing n integers, determine its m largest
 *       values. Typical values of n and m are 1 billion and 1 million
 *       respectively.
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

/**
 * @brief Returns the m largest elements of an array using quick-select.
 * @note Complexity: O(m) in time (on average), O(n) in space, where n is the
 *       number of elements in the array.
 */
std::vector<int> get_m_largest_1(std::vector<int> values, const size_t m)
{
    assert(m <= values.size());

    static std::random_device device;
    static std::mt19937 generator(device());

    auto first = values.begin();
    auto last = values.end();

    /* number of largest elements we still need to find */
    size_t missing = m;

    while (true)
    {
        size_t k = std::distance(first, last);

        std::uniform_int_distribution<size_t> distribution(0, k - 1);

        /* randomly select a pivot */
        auto pivot = first + distribution(generator);

        std::swap(*first, *pivot);

        auto compare = [first](const int x) { return x < *first; };

        /*
         * partition [first+1,last): the left half will contain values
         * which are < pivot, the right half will contain values which
         * are >= pivot
         */
        auto middle = std::partition(first + 1, last, compare) - 1;

        /*
         * make [first,middle) contain values which are < pivot and
         * [middle,last) contain values which are >= pivot
         */
        if (middle != first)
        {
            std::swap(*first, *middle);
        }

        /*
         * since all values in [middle,last) are larger than the
         * values in [first,middle), the d values in [middle,last)
         * are the d largest values in [first,last)
         */
        size_t d = std::distance(middle, last);

        if (d == missing)
        {
            break;
        }
        else if (d < missing)
        {
            last = middle;
            missing -= d;
        }
        else /* d > missing */
        {
            first = middle + 1;
        }
    }

    return {values.end() - m, values.end()};
}

/**
 * @brief Returns the m largest elements of an array using a min-heap.
 * @note Complexity: O(n*log(m)) in time, O(m) in space, where n is the number
 *       of elements in the array.
 */
std::vector<int> get_m_largest_2(const std::vector<int>& values, const size_t m)
{
    assert(m <= values.size());

    auto heap_compare = [](const int a, const int b) { return a > b; };

    std::vector<int> m_largest(values.begin(), values.begin() + m);

    /* turn the first m values into a min-heap in O(m) time */
    std::make_heap(m_largest.begin(), m_largest.end(), heap_compare);

    for (size_t i = m; i < values.size(); ++i)
    {
        /* push values[i] into the heap; heap size becomes m+1 */
        m_largest.push_back(values[i]);
        std::push_heap(m_largest.begin(), m_largest.end(), heap_compare);

        /* pop the smallest value from the heap; heap size becomes m */
        std::pop_heap(m_largest.begin(), m_largest.end(), heap_compare);
        m_largest.pop_back();
    }

    return m_largest;
}

/**
 * @brief Returns the m largest elements of an array by sorting it first.
 * @note Complexity: O(n*log(n)) in time (on average), O(n) in space, where n
 *       is the number of elements in the array.
 */
std::vector<int> get_m_largest_3(std::vector<int> values, const size_t m)
{
    assert(m <= values.size());

    std::sort(values.begin(), values.end());

    return {values.end() - m, values.end()};
}

int main()
{
    std::random_device device;
    std::mt19937 generator(device());

    std::uniform_int_distribution<int> distribution(-1000, 1000);

    for (size_t n = 0; n <= 50; ++n)
    {
        for (int i = 0; i < 100; ++i)
        {
            std::vector<int> values;

            while (values.size() < n)
            {
                values.push_back(distribution(generator));
            }

            for (size_t m = 1; m <= n; ++m)
            {
                std::vector<int> largest1 = get_m_largest_1(values, m);
                std::vector<int> largest2 = get_m_largest_2(values, m);
                std::vector<int> largest3 = get_m_largest_3(values, m);

                std::sort(largest1.begin(), largest1.end());
                std::sort(largest2.begin(), largest2.end());

                assert(largest1 == largest2);
                assert(largest2 == largest3);
            }
        }

        std::cout << "passed random tests for arrays of size " << n
                  << std::endl;
    }

    return EXIT_SUCCESS;
}
