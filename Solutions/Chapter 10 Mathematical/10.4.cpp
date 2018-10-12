/*
 * TASK: Implement the subtraction, multiplication and division operations
 *       using only additions, i.e., express the *, - and / operators using
 *       only the + operator.
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <stdexcept>

/**
 * @brief Computes -a using only additions (-a = a + (-2)*a).
 * @note Complexity: O(|a|) in time, O(1) in space.
 */
int negative(int a)
{
    int b = a;

    if (a > 0)
    {
        while (a > 0)
        {
            b += (-2);
            --a;
        }
    }
    else
    {
        while (a < 0)
        {
            b += 2;
            ++a;
        }
    }

    return b;
}

/**
 * @brief Computes |a| using only additions.
 * @note Complexity: O(|a|) in time, O(1) in space.
 */
int magnitude(const int a)
{
    return (a > 0) ? a : negative(a);
}

/**
 * @brief Computes a*b using only additions.
 * @note Complexity: O(|a|) in time, O(1) in space.
 */
int multiply(const int a, const int b)
{
    int c = 0;

    /* c <-- |a|*b */
    for (int i = magnitude(a); i > 0; --i)
    {
        c += b;
    }

    return (a < 0) ? negative(c) : c;
}

/**
 * @brief Computes (a-b) using only additions.
 * @note Complexity: O(|b|) in time, O(1) in space.
 */
int subtract(const int a, const int b)
{
    return a + negative(b);
}

/**
 * @brief Computes a/b using only additions.
 * @note Complexity: O(max(|a|,|b|)) in time, O(1) in space.
 */
int divide(const int a, const int b)
{
    if (b == 0)
    {
        throw std::overflow_error("cannot divide by zero");
    }

    /* determine the sign of a/b */
    int sign = ((a > 0 && b > 0) || (a < 0 && b < 0)) ? 1 : -1;

    const int a_mag = magnitude(a);
    const int b_mag = magnitude(b);

    int c = 0;
    int d = 0;

    /* d <-- |a|/|b| */
    while (c + b_mag <= a_mag)
    {
        c += b_mag;
        ++d;
    }

    return (sign == 1) ? d : negative(d);
}

int main()
{
    std::random_device device;
    std::mt19937 generator(device());

    std::uniform_int_distribution<int> distribution(-1000, 1000);

    for (int i = 0; i < 1000; ++i)
    {
        int a = distribution(generator);
        int b = distribution(generator);

        assert(negative(a) == -a);
        assert(magnitude(a) == std::abs(a));

        assert(subtract(a, b) == a - b);
        assert(multiply(a, b) == a * b);

        if (b != 0)
        {
            assert(divide(a, b) == a / b);
        }
    }

    std::cout << "passed random tests" << std::endl;

    return EXIT_SUCCESS;
}
