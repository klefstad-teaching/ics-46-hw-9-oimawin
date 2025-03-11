#include "ladder.h"

void error(string word1, string word2, string msg) {
    cerr << "Error with word ladder [" << word1 << "->" << word2 << "]: " << msg << endl;
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream in(file_name);
    for (string word; in >> word;)
        word_list.insert(word);
    in.close();
}
