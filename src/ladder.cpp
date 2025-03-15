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

bool is_adjacent(const string& word1, const string& word2) {
    //Wagner-Fischer algorithm for computing edit distance
    int word1_len = word1.length(), word2_len = word2.length();
    
    vector<vector<int>> d(word1_len + 1, vector<int>(word2_len + 1, 0));
    
    for (int i = 0; i <= word1_len; ++i) { d[i][0] = i; }
    for (int j = 0; j <= word2_len; ++j) { d[0][j] = j; }

    for (int i = 1; i <= word1_len; ++i) {
        for (int j = 1; j <= word2_len; ++j) {
            int substitutionCost = (word1[i - 1] == word2[j - 1]) ? 0 : 1;
            d[i][j] = min(d[i - 1][j] + 1, min(d[i][j - 1] + 1, d[i - 1][j - 1] + substitutionCost));
        }
    }

    return d[word1_len][word2_len] < 2;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> ladder_q;
    ladder_q.push({begin_word});
    set<string> visited = {begin_word};
    while (!ladder_q.empty()) {
        vector<string> ladder = ladder_q.front();
        ladder_q.pop();
        string last_word = ladder[ladder.size() - 1];
        for (string word : word_list)
            if (is_adjacent(last_word, word))
                if (!visited.contains(word)) {
                    visited.insert(word);
                    vector<string> new_ladder(ladder);
                    new_ladder.push_back(word);
                    if (word == end_word)
                        return new_ladder;
                    ladder_q.push(new_ladder);
                }
    }
    vector<string> empty;
    return empty;
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