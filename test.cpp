#include <iostream>
#include <random>
#include <sstream>

int main() {
  std::stringstream buffer("Jon player 23 dsd 43");
  std::string word, word2, word3;
  int num, num2;
  buffer >> word >> word2 >> num >> word3 >> num2;

  std::cout << word << ' ' << word2 << ' ' << num << ' ' << word << ' ' << num2;
}