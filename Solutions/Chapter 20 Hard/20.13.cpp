/*
 * TASK: Your are given a set of words (a dictionary). Determine the largest
 *       rectangle of characters such that every row and every column forms a
 *       word in the given dictionary (read from left to right and top to
 *       bottom respectively).
 *
 * NOTE: The solution below works for any dictionary whose words are encoded in
 *       either ASCII or ISO-8859-15; this should cover languages from the
 *       Americas, Western Europe, Oceania and much of Africa (see
 *       https://en.wikipedia.org/wiki/ISO/IEC_8859-1 for more on this topic).
 */

#include <bitset>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/* a bitmask which indicates valid/invalid characters */
using char_bitset = std::bitset<256>;

/* a set of (distinct) words */
using word_set = std::unordered_set<std::string>;

/** @brief A dictionary class for storing words and extra useful information. */
class dictionary
{
public:
    /**
     * @brief Inserts a word into the dictionary.
     * @note Complexity: O(n²) in both time and space, where n is the length
     *       of the word.
     */
    void insert(const std::string& word)
    {
        size_t n = word.size();

        words_.insert(word);
        largest_word_length_ = std::max(largest_word_length_, n);

        if (next_chars_.size() <= n)
        {
            next_chars_.resize(n + 1);
        }

        /*
         * for each prefix word[0..i), with i in [0,n), add word[i] as a
         * "valid next character" for word[0..i) whenever we are trying
         * to form a word of length n
         */
        for (size_t i = 0; i < n; ++i)
        {
            uint8_t char_bit = static_cast<uint8_t>(word[i]);
            next_chars_[n][word.substr(0, i)][char_bit] = true;
        }
    }

    /**
     * @brief Given a word prefix, returns a bitmask indicating what are the
     *        possible next characters if the prefix is assumed to be part
     *        of a word of length n present in the dictionary.
     * @note Complexity: O(n) in time, O(1) in space.
     */
    char_bitset valid_next_chars(const std::string& prefix,
                                 const size_t n) const
    {
        auto it = next_chars_[n].find(prefix);

        if (it == next_chars_[n].end())
        {
            return {};
        }

        return it->second;
    }

    /**
     * @brief Returns true if a given word is in the dictionary, false
     *        otherwise.
     * @note Complexity: O(n) in time, O(1) in space, where n is the length
     *       of the input word.
     */
    bool find(const std::string& word) const
    {
        return (words_.find(word) != words_.end());
    }

    /**
     * @brief Returns the length of the longest word in the dictionary.
     * @note Complexity: O(1) in both time and space.
     */
    size_t largest_word_length() const
    {
        return largest_word_length_;
    }

private:
    /* words in the dictionary */
    word_set words_;

    /* length of the longest word in the dictionary */
    size_t largest_word_length_ = 0;

    /* valid next characters given the target word length and a prefix */
    std::vector<std::unordered_map<std::string, char_bitset> > next_chars_;
};

/**
 * @brief A "rectangle of characters" such that each undefined cell stores a
 *        '\0' character; each cell is identified by a pair of indices (i,j),
 *        with (0,0) being the index of the top-left rectangle cell.
 */
class rectangle
{
public:
    rectangle(const size_t width = 0, const size_t height = 0)
        : width_(width), height_(height), chars_(width * height, '\0')
    {
        /* nothing needs to be done here */
    }

    /**
     * @brief Returns a reference to the character at the i-th row and j-th
     *        column (both are zero indexed).
     * @note Complexity: O(1) in both time and space.
     */
    char& operator()(const size_t i, const size_t j)
    {
        assert(i < height() && j < width());

        return chars_[i * width() + j];
    }

    /**
     * @brief Returns a copy of the character at the i-th row and j-th
     *        column (both are zero indexed).
     * @note Complexity: O(1) in both time and space.
     */
    char operator()(const size_t i, const size_t j) const
    {
        assert(i < height() && j < width());

        return chars_[i * width() + j];
    }

    /**
     * @brief Marks the cell at the i-th row and j-th column as "undefined"
     *        (i.e., sets it to '\0').
     * @note Complexity: O(1) in both time and space.
     */
    void reset(const size_t i, const size_t j)
    {
        (*this)(i, j) = '\0';
    }

    /**
     * @brief Returns the leftmost contiguous sequence of defined characters
     *        at the i-th row.
     * @note Complexity: O(width) in both time and space.
     */
    std::string subrow(const size_t i) const
    {
        assert(i < height());

        std::string result;

        for (size_t j = 0; j < width() && (*this)(i, j) != '\0'; ++j)
        {
            result.push_back((*this)(i, j));
        }

        return result;
    }

    /**
     * @brief Returns the topmost contiguous sequence of defined characters
     *        at the j-th column.
     * @note Complexity: O(height) in both time and space.
     */
    std::string subcolumn(const size_t j) const
    {
        assert(j < width());

        std::string result;

        for (size_t i = 0; i < height() && (*this)(i, j) != '\0'; ++i)
        {
            result.push_back((*this)(i, j));
        }

        return result;
    }

    /**
     * @brief Returns the width of the rectangle.
     * @note Complexity: O(1) in both time and space.
     */
    size_t width() const
    {
        return width_;
    }

    /**
     * @brief Returns the height of the rectangle.
     * @note Complexity: O(1) in both time and space.
     */
    size_t height() const
    {
        return height_;
    }

    /**
     * @brief Returns true if the rectangle has area zero, false otherwise.
     * @note Complexity: O(1) in both time and space.
     */
    bool empty() const
    {
        return (width() == 0 || height() == 0);
    }

    /**
     * @brief Prints the rectangle on a given output stream.
     * @note Complexity: O(width*height) in time, O(1) in space.
     */
    std::ostream& print(std::ostream& os = std::cout) const
    {
        for (size_t i = 0; i < height(); ++i)
        {
            for (size_t j = 0; j < width(); ++j)
            {
                os << (*this)(i, j);
            }

            os << "\n";
        }

        return os;
    }

private:
    const size_t width_;
    const size_t height_;
    std::vector<char> chars_;
};

/**
 * @brief Recursive step on the backtracking implementation; at each call, all
 *        cells rect(0:i, 0:j) except for rect(i,j) are assumed to be already
 *        defined; the rectangle is constructed first from left to right
 *        starting at the top-left cell, then top to bottom, so the topmost row
 *        is built first, then the second topmost row and so on until we reach
 *        the bottom-right cell.
 * @return true if a valid rectangle could be built, false otherwise.
 */
bool build_rectangle(rectangle& rect,
                     const dictionary& dict,
                     const size_t i = 0,
                     const size_t j = 0)
{
    std::string subrow = rect.subrow(i);
    std::string subcol = rect.subcolumn(j);

    /* subrow must be equal to rect(i, 0:j-1) */
    assert(subrow.size() == j);

    /* subcol must be equal to rect(0:i-1, j) */
    assert(subcol.size() == i);

    /*
     * considering that the i-th row and the j-th column must form words in
     * the dictionary, determine which characters can be placed at rect(i,j)
     * such that it will still be possible for the i-th row and the j-th
     * column to form words of lengths rect.width() and rect.height()
     * respectively when they are both fully built (i.e., all cells defined)
     */
    char_bitset valid_next_char = dict.valid_next_chars(subrow, rect.width()) &
                                  dict.valid_next_chars(subcol, rect.height());

    /* the character '\0' may not be part of a word */
    for (int c = 1; c < 256; ++c)
    {
        if (valid_next_char[c] == true)
        {
            rect(i, j) = static_cast<char>(c);

            if (j + 1 < rect.width())
            {
                if (build_rectangle(rect, dict, i, j + 1) == true)
                {
                    return true;
                }
            }
            else if (i + 1 < rect.height()) /* j+1 == rect.width() */
            {
                if (build_rectangle(rect, dict, i + 1, 0) == true)
                {
                    return true;
                }
            }
            else /* we are at the right-bottom rectangle cell */
            {
                return true;
            }

            rect.reset(i, j);
        }
    }

    return false;
}

/**
 * @brief Builds the largest rectangle of characters such that each of its rows
 *        and columns forms a word in a given dictionary.
 * @note Complexity: O(N²*d^N²) in time, O(N²) in space, where N is the length
 *       of the longest word in the dictionary and d is the number of distinct
 *       characters from which the dictionary words are constructed (notice that
 *       d cannot exceed 255 in this implementation; also, this runtime
 *       asymptotic bound is very conservative and a solution will in general be
 *       obtained in much less time).
 */
rectangle build_largest_word_rectangle(const dictionary& dict)
{
    size_t N = dict.largest_word_length();

    /*
     * consider first the rectangles with the maximum possible area N*N,
     * then (N*N - 1), then (N*N - 2) and so on; the first valid rectangle
     * which is found is the one we are looking for
     */
    for (size_t area = N * N; area > 0; --area)
    {
        for (size_t width = N; width > 0; --width)
        {
            size_t height = area / width;

            /*
             * if width < height, we already considered this
             * rectangle (with swapped values of width and height),
             * and there is no need to consider even smaller width
             * values
             */
            if (width < height)
            {
                break;
            }

            /* if no rectangle with the given area/width can exist */
            if (width * height != area)
            {
                continue;
            }

            rectangle rect(width, height);

            if (build_rectangle(rect, dict) == true)
            {
                return rect;
            }
        }
    }

    /*
     * if we reach this point, there is no rectangle which can be formed
     * with the words from the input dictionary
     */
    return {};
}

/**
 * @brief Returns true if the rectangle rows and columns form words in the given
 *        dictionary, false otherwise.
 * @note Complexity: O(width*height) in time, O(max(width,height)) in space.
 */
bool is_valid_rectangle(const rectangle& rect, const dictionary& dict)
{
    /* check if each row is a valid word in the dictionary */
    for (size_t i = 0; i < rect.height(); ++i)
    {
        std::string row = rect.subrow(i);

        if (row.size() != rect.width())
        {
            return false;
        }

        if (dict.find(row) == false)
        {
            return false;
        }
    }

    /* check if each column is a valid word in the dictionary */
    for (size_t j = 0; j < rect.width(); ++j)
    {
        std::string column = rect.subcolumn(j);

        if (column.size() != rect.height())
        {
            return false;
        }

        if (dict.find(column) == false)
        {
            return false;
        }
    }

    return true;
}

int main(int argc, char** argv)
{
    /*
     * usage: ./solve <dictionary-file>
     * example: ./solve dictionaries/dictionary-100.txt
     */

    assert(argc > 1);

    /* make sure the dictionary file is valid */
    std::ifstream dict_file(argv[1]);
    assert(dict_file.is_open() == true);

    dictionary dict;

    /* read all words from the dictionary file */
    std::string dict_word;
    while (dict_file >> dict_word)
    {
        dict.insert(dict_word);
    }

    rectangle rect = build_largest_word_rectangle(dict);

    if (rect.empty() == false)
    {
        assert(is_valid_rectangle(rect, dict) == true);

        rect.print();
    }
    else
    {
        std::cout << "no rectangle could be built\n";
    }

    return EXIT_SUCCESS;
}
