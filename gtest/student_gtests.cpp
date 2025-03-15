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
  string expected = "a -> b -> c -> d";
  EXPECT_EQ(output, expected);
}

TEST(WordLadder, valid_ladder_input_success) {
  set<string> word_list;
  load_words(word_list, file_name);
  valid_ladder_input("ring", "worm", word_list);
}

TEST(WordLadder, valid_ladder_input_begin_end_same_fail) {
  set<string> word_list;
  load_words(word_list, file_name);
  testing::internal::CaptureStderr();
  valid_ladder_input("ring", "ring", word_list);
  string output = testing::internal::GetCapturedStderr();
  string expected = "[ERROR] word ladder \'ring -> ring\': Beginning and ending word are the same\n";
  EXPECT_EQ(output, expected);
}

TEST(WordLadder, valid_ladder_input_end_word_fail) {
  set<string> word_list;
  load_words(word_list, file_name);
  testing::internal::CaptureStderr();
  valid_ladder_input("ring", "s;ldkfja;lskdfj", word_list);
  string output = testing::internal::GetCapturedStderr();
  string expected = "[ERROR] word ladder \'ring -> s;ldkfja;lskdfj\': \'s;ldkfja;lskdfj\' is not a valid dictionary word\n";
  EXPECT_EQ(output, expected);
}

TEST(WordLadder, is_adjacent) {
  EXPECT_TRUE(is_adjacent("word", "word"));
  EXPECT_TRUE(is_adjacent("word", "words"));
  EXPECT_TRUE(is_adjacent("word", "ward"));
  EXPECT_TRUE(is_adjacent("word", "wrd"));
  EXPECT_FALSE(is_adjacent("word", "wording"));
  EXPECT_FALSE(is_adjacent("word", "brother"));
  EXPECT_FALSE(is_adjacent("word", "sin"));
}

TEST(WordLadder, generate_word_ladder) {
  set<string> word_list;
  load_words(word_list, file_name);
  testing::internal::CaptureStdout();
  print_word_ladder(generate_word_ladder("car", "cheat", word_list));
  string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, "car -> cat -> chat -> cheat");
}