/**
 * @file word_counter.cpp
 * Implementation of the WordFreq class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Spring 2012
 */

using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::pair;
using std::string;
using std::vector;

template <template <class K, class V> class Dict>
WordFreq<Dict>::WordFreq(const string &infile) : filename(infile)
{
    /* nothing */
}

template <template <class K, class V> class Dict>
vector<pair<string, int>> WordFreq<Dict>::getWords(int threshold) const
{
    TextFile infile(filename);
    vector<pair<string, int>> ret;
    /**
     * @todo Implement this function.
     * @see char_counter.cpp if you're having trouble.
     */
    while (infile.good())
    {
        string word = infile.getNextWord();
        bool found = false;

        for (auto& var : ret)
        {
            found = false;
            if (var.first == word)
            {
                var.second++;
                found = true;
                break;
            }
        }
        if (!found)
        {
            ret.push_back(std::pair(word, 1));
        }
    }

    for (size_t i = 0; i < ret.size(); i++) {
        if (ret.at(i).second < threshold) {
            ret.erase(ret.begin() + i);
            --i;
        }
    }
    return ret;
}
