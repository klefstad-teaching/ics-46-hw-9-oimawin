#include "ladder.h"

void error(string word1, string word2, string msg) {
    cerr << "[ERROR] word ladder \'" << word1 << " -> " << word2 << "\': " << msg << endl;
}

bool valid_ladder_input(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word){
        error(begin_word, end_word, "Beginning and ending word are the same");
        return false;
    }
    return valid_dict_word(begin_word, end_word, end_word, word_list);
}

bool valid_dict_word(const string& begin_word, const string& end_word, const string& curr_word, const set<string>& word_list) {
    if (word_list.find(curr_word) == word_list.end()) {
        error(begin_word, end_word, "\'" + curr_word + "\' is not a valid dictionary word");
        return false;
    }
    return true;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    //Wagner-Fischer algorithm for computing edit distance
    int str1_len = str1.length(), str2_len = str2.length();
    if (abs(str2_len - str1_len) > d) { return false; }
    
    vector<vector<int>> dist(str1_len + 1, vector<int>(str2_len + 1, 0));
    
    for (int i = 0; i <= str1_len; ++i) { dist[i][0] = i; }
    for (int j = 0; j <= str2_len; ++j) { dist[0][j] = j; }

    for (int i = 1; i <= str1_len; ++i) {
        for (int j = 1; j <= str2_len; ++j) {
            int substitutionCost = (str1[i - 1] == str2[j - 1]) ? 0 : 1;
            dist[i][j] = min(dist[i - 1][j] + 1, min(dist[i][j - 1] + 1, dist[i - 1][j - 1] + substitutionCost));
        }
    }

    return dist[str1_len][str2_len] <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    /* if (valid_ladder_input(begin_word, end_word, word_list)) {
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
    } */
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
    cout << "Word ladder found: "
    for (vector<string>::const_iterator it = ladder.cbegin();; it != ladder.end(); ++it)
        cout << *it << " ";
    cout << endl;
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void verify_word_ladder() {
    set<string> word_list;
	load_words(word_list, "words.txt");
	my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
	my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
	my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
	my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
	my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
	my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}