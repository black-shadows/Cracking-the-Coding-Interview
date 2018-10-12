/*
 * TASK: Given a set of n distinct points on a plane, determine the line which
 *       is tangent to the largest number of points.
 *
 * NOTE: The solution to this problem is not, in general, unique.
 */

#include <algorithm>
#include <iostream>
#include <vector>
#include "line.h"

/**
 * @brief Returns a vector with all lines which connect each pair of points
 *        on an array with n distinct points.
 * @note Complexity: O(n²) in both time and space since there are n*(n-1)/2
 *       possible distinct pairs of points.
 */
std::vector<line> build_all_lines(const std::vector<point>& points)
{
    std::vector<line> lines;

    for (size_t i = 0; i < points.size(); ++i)
    {
        for (size_t j = i + 1; j < points.size(); ++j)
        {
            lines.push_back(line(points[i], points[j]));
        }
    }

    return lines;
}

/**
 * @brief Determines the line which crosses the largest number of points using
 *        brute-force (build all possible lines and then determine which one
 *        of them crosses the largest number of points by mere counting).
 * @note Complexity: O(n³) in time, O(n²) in space, where n is the number of
 *       points.
 */
line line_crosses_most_points_1(const std::vector<point>& points)
{
    assert(points.size() >= 2);

    /* compute all lines passing over each distinct pair of points */
    std::vector<line> lines = build_all_lines(points);

    /* determine which line crosses the largest number of points */
    size_t best_line = 0;
    size_t max_crossed = 0;

    for (size_t i = 0; i < lines.size(); ++i)
    {
        /* number of points crossed by line i */
        size_t num_crossed_i = 0;

        for (const point& p : points)
        {
            if (lines[i].crosses(p) == true)
            {
                ++num_crossed_i;
            }
        }

        if (num_crossed_i > max_crossed)
        {
            max_crossed = num_crossed_i;
            best_line = i;
        }
    }

    return lines[best_line];
}

/**
 * @brief Comparison function which orders lines by x-intercept values, then by
 *        y-intercept values and finally by the sines of the angles they make
 *        with the positive x axis.
 * @note Complexity: O(1) in both time and space.
 */
bool line_compare(const line& r, const line& s)
{
    double rx = r.x_intercept();
    double sx = s.x_intercept();

    /* if r and s have the same x intercept values */
    if (std::abs(rx - sx) < epsilon)
    {
        double ry = r.y_intercept();
        double sy = s.y_intercept();

        /* if r and s have the same y intercept values */
        if (std::abs(ry - sy) < epsilon)
        {
            return r.sine() < s.sine();
        }

        return ry < sy;
    }

    return rx < sx;
}

/**
 * @brief Determines the line which crosses the largest number of points using
 *        sorting (build all possible lines, sort them and then determine which
 *        one of them occurs the most in the sorted array of lines).
 * @note Complexity: O(n²*log(n)) in time, O(n²) in space.
 */
line line_crosses_most_points_2(const std::vector<point>& points)
{
    assert(points.size() >= 2);

    /* compute all lines passing over each distinct pair of points */
    std::vector<line> lines = build_all_lines(points);

    /*
     * sort the lines array using line_compare(); this will group identical
     * lines together and runs in O(n²*log(n²)) = O(n²*log(n)) time
     */
    std::sort(lines.begin(), lines.end(), line_compare);

    /*
     * determine which line appears most in the sorted array; by doing this,
     * we end up getting the line which crosses the largest number of points
     * because if a line crosses m points, there will be m*(m-1)/2 identical
     * lines in the lines array, so the line which crosses the largest number
     * of points will be the one which appears most in the array
     */
    size_t best_line = 0;
    size_t max_count = 1;

    size_t i = 0;

    while (i < lines.size())
    {
        size_t j = i + 1;
        size_t count_equal_i = 1;

        /* loop as long as we keep on finding identical lines */
        while (j < lines.size() && lines[i] == lines[j])
        {
            ++count_equal_i;
            ++j;
        }

        if (count_equal_i > max_count)
        {
            max_count = count_equal_i;
            best_line = i;
        }

        i = j;
    }

    return lines[best_line];
}

/**
 * @brief Returns an array with n distinct random points with coordinates (i,j),
 *        where i and j are integer values in [0,9].
 * @note This method works only for n <= 100, otherwise it will never finish.
 */
std::vector<point> random_points(const size_t n)
{
    assert(n <= 100);

    static std::random_device device;
    static std::mt19937 generator(device());

    std::uniform_int_distribution<int> distribution(0, 9);

    std::vector<point> points;

    while (points.size() < n)
    {
        double x = static_cast<double>(distribution(generator));
        double y = static_cast<double>(distribution(generator));

        point p{x, y};

        /* all points in the array must be distinct */
        if (std::find(points.begin(), points.end(), p) == points.end())
        {
            points.push_back({x, y});
        }
    }

    return points;
}

int main()
{
    for (size_t n = 2; n <= 20; ++n)
    {
        for (int i = 0; i < 1000; ++i)
        {
            std::vector<point> points = random_points(n);

            line r1 = line_crosses_most_points_1(points);
            line r2 = line_crosses_most_points_2(points);

            size_t crossed_1 = 0;
            size_t crossed_2 = 0;

            for (const point& p : points)
            {
                crossed_1 += r1.crosses(p);
                crossed_2 += r2.crosses(p);
            }

            assert(crossed_1 == crossed_2);
        }

        std::cout << "passed random tests for point sets of size " << n
                  << std::endl;
    }

    return EXIT_SUCCESS;
}
