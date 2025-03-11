#include <gtest/gtest.h>

#include "dijkstras.h"
#include "ladder.h"

string file_name = "/home/emmath/ics46/ics-46-hw-9-oimawin/src/words.txt";
size_t word_count = 45392;

TEST(WordLadder, load_words) {
  set<string> word_list;
  load_words(word_list, file_name);
  EXPECT_EQ(word_list.size(), word_count);
}

TEST(WordLadder, print_word_ladder) {
  vector<string> ladder = {"a", "b", "c", "d"};
  testing::internal::CaptureStdout();
  print_word_ladder(ladder);
  string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, "a -> b -> c -> d");
}