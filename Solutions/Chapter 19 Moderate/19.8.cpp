/*
 * TASK: Given an input stream (e.g. to read from a file), count the number of
 *       occurrences of each unique word read from the stream.
 */

#include <iostream>
#include <map>

/**
 * @brief Returns a map containing the number of occurrences of each unique
 *        word read from an input stream.
 * @note Complexity: O(n*m*log(n)) in time, O(n*m) in space, where n is the
 *       number of words in the input stream and m is the length of the longest
 *       word.
 */
std::map<std::string, size_t> count_words(std::istream& stream)
{
    std::string word;

    std::map<std::string, size_t> count;

    while (stream >> word)
    {
        ++count[word];
    }

    return count;
}

int main()
{
    std::map<std::string, size_t> count = count_words(std::cin);

    for (const auto& p : count)
    {
        std::cout << p.first << ": " << p.second << "\n";
    }

    return EXIT_SUCCESS;
}
