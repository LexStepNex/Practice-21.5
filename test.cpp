#include <iostream>
#include <random>
#include <windows.h>
#include <shellapi.h>

using namespace std;

int main() {
  random_device rd;
  mt19937 generate(rd());
  uniform_int_distribution<> dist(1, 10);
  uniform_int_distribution<> dist2(50, 150);

  for (int i = 0; i < 5; ++i) {
    cout << dist(generate) << " ";
  }
  cout << endl;

  for (int i = 0; i < 5; ++i) {
    cout << dist2(generate) << " ";
  }
  ShellExecute(0, 0, "http://www.google.com", 0, 0 , SW_SHOW );
}