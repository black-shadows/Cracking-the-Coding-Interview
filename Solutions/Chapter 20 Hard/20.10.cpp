/*
 * TASK: You are given a dictionary and a pair of words with equal lengths.
 *       Determine a "path of words" taking the first word into the second one
 *       such that at each step, only one character is changed and the resulting
 *       word is still part of the dictionary. As an example, for input words
 *       "cat" and "bit", a possible path is: cat -> bat -> bit (assuming that
 *       all these words are in the dictionary).
 */

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using dictionary = std::unordered_set<std::string>;
using word_array = std::vector<std::string>;

/**
 * @brief Returns true if two words word1 and word2 have the same length and
 *        differ by exactly one character, false otherwise.
 * @note Complexity: O(d) in time, O(1) in space, where d is the length of the
 *       words (if not equal, the method runs in O(1) time).
 */
bool is_distance_one(const std::string& word1, const std::string& word2)
{
    if (word1.size() != word2.size())
    {
        return false;
    }

    size_t count = 0;

    for (size_t i = 0; i < word1.size(); ++i)
    {
        count += (word1[i] != word2[i]);
    }

    return (count == 1);
}

/**
 * @brief Returns an array containing all words in a given dictionary with
 *        distance one from a given word.
 * @note Complexity: O(d) in both time and space, where d is the word length.
 */
word_array get_distance_one_words(std::string word, const dictionary& dict)
{
    word_array dist_one;

    /*
     * replace each character in word with every character in [a-zA-Z],
     * then check if the resulting string is a word in the dictionary
     * (this implementation is not portable, but works correctly for ASCII
     * strings)
     */
    for (char& current : word)
    {
        char original = current;

        for (char c = 'a'; c <= 'z'; ++c)
        {
            current = c;

            if (dict.find(word) != dict.end())
            {
                dist_one.push_back(word);
            }
        }

        for (char c = 'A'; c <= 'Z'; ++c)
        {
            current = c;

            if (dict.find(word) != dict.end())
            {
                dist_one.push_back(word);
            }
        }

        current = original;
    }

    return dist_one;
}

/**
 * @brief Determines a path between word1 and word2 which defines a series of
 *        steps to transform word1 into word2 such that each step involves only
 *        one character change and generates a word which is also in the
 *        dictionary (this is merely an implementation of breadth-first search).
 * @note Complexity: O(n*d) in both time and space, where n is the number of
 *       words in the dictionary and d is the length of its longest word.
 */
word_array get_path_between_words(const std::string& word1,
                                  const std::string& word2,
                                  const dictionary& dict)
{
    /*
     * return an empty path if one of these conditions are satisfied:
     *
     * 1) word1 and word2 are equal
     * 2) word1 and word2 have different lengths
     * 3) word1 is not in the dictionary
     * 4) word2 is not in the dictionary
     */
    if (word1 == word2 || word1.size() != word2.size() ||
        dict.find(word1) == dict.end() || dict.find(word2) == dict.end())
    {
        return {};
    }

    std::queue<std::string> Q;
    std::unordered_set<std::string> explored;
    std::unordered_map<std::string, std::string> previous;

    Q.push(word1);
    explored.insert(word1);

    while (Q.empty() == false)
    {
        std::string current = Q.front();
        Q.pop();

        word_array neighbors = get_distance_one_words(current, dict);

        for (const std::string& neighbor : neighbors)
        {
            /*
             * if we reached the target (word2), build the path in
             * reverse order from word2 to word1 and then return it
             * in correct order
             */
            if (neighbor == word2)
            {
                word_array path;

                path.push_back(neighbor);

                while (current != word1)
                {
                    path.push_back(current);
                    current = previous[current];
                }

                path.push_back(word1);

                /* correct the path direction: word1 -> word2 */
                std::reverse(path.begin(), path.end());

                return path;
            }

            /* if neighbor has not been explored yet */
            if (explored.find(neighbor) == explored.end())
            {
                Q.push(neighbor);
                explored.insert(neighbor);

                previous[neighbor] = current;
            }
        }
    }

    /* if we reach this point, we cannot transform word1 into word2 */
    return {};
}

int main(int argc, char** argv)
{
    /*
     * usage: ./solve <dictionary-file> <word1> <word2>
     * example: ./solve dictionary.txt cat bit
     */

    assert(argc > 3);

    /* make sure the dictionary file is valid */
    std::ifstream dict_file(argv[1]);
    assert(dict_file.is_open() == true);

    std::string word1(argv[2]);
    std::string word2(argv[3]);

    dictionary dict;

    /* read all words from the dictionary file */
    std::string dict_word;
    while (dict_file >> dict_word)
    {
        dict.insert(dict_word);
    }

    word_array path = get_path_between_words(word1, word2, dict);

    if (path.empty() == false)
    {
        std::cout << path.front();

        for (size_t i = 1; i < path.size(); ++i)
        {
            std::cout << " -> " << path[i];

            assert(is_distance_one(path[i - 1], path[i]) == true);
        }

        std::cout << std::endl;
    }
    else if (word1 == word2)
    {
        std::cout << "initial and target words are equal" << std::endl;
    }
    else
    {
        std::cout << "no path found between '" << word1 << "' and '" << word2
                  << "'" << std::endl;
    }

    return EXIT_SUCCESS;
}
