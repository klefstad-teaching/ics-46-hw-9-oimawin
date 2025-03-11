#include "ladder.h"

void error(string word1, string word2, string msg) {
    cerr << "Error with word ladder [" << word1 << "->" << word2 << "]: " << msg << endl;
}

void valid_ladder_input(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word)
        error(begin_word, end_word, "Beginning and ending word are the same");
    valid_dict_word(begin_word, end_word, end_word, word_list);
}

void valid_dict_word(const string& begin_word, const string& end_word, const string& curr_word, const set<string>& word_list) {
    if (word_list.find(curr_word) == word_list.end())
        error(begin_word, end_word, "\'" + curr_word + "\' is not a valid dictionary word");
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream in(file_name);
    for (string word; in >> word;)
        word_list.insert(word);
    in.close();
}

void print_word_ladder(const vector<string>& ladder) {
    vector<string>::const_iterator it = ladder.cbegin();
    cout << *(it++);
    for (it; it != ladder.end(); ++it)
        cout << " -> " << *it;
}