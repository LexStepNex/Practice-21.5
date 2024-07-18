#include <cmath>
#include <iostream>
#include <string>

struct math_vector {
  double x = 0;
  double y = 0;
};

void info() {
  using namespace std;

  cout << "Operations info:\n";
  cout << "add - addition of two vectors\n";
  cout << "subtraction - subtraction of two vectors\n";
  cout << "scale - multiplying a vector by a scalar\n";
  cout << "length - finding the length of a vector\n";
  cout << "normalize - vector normalization\n\n";
}

std::string lower_case(std::string str) {
  int sizeStr = str.size();
  for (int i = 0; i < sizeStr; i++) {
    str[i] = std::tolower(str[i]);
  }
  return str;
}

bool answer(std::string ans) {
  if (ans == "add" || ans == "subtract" || ans == "scale" || ans == "length" ||
      ans == "normalize") {
    return true;
  }
  return false;
}

math_vector input_coord(math_vector& vec, std::string number_vector = "") {
  do {
    std::cout << "Input coordinate x vector" << number_vector << ": ";
    std::cin >> vec.x;
    std::cout << "Input coordinate y vector" << number_vector << ": ";
    std::cin >> vec.y;

    if (vec.x == 0 && vec.y == 0) {
      std::cout << "Incorrect coordinates\n";
      std::cout << "Vector cannot be equal to 0. Please, try again.\n";
    }
  } while (vec.x == 0 && vec.y == 0);

  return vec;
}

double length() {  // для вектора с началом координат (0,0)
  math_vector vec;
  vec = input_coord(vec);
  return hypot(vec.x, vec.y);
}

double add() {  // для векторов с началом координат (0,0)
  math_vector vec_1;
  vec_1 = input_coord(vec_1, "1");

  math_vector vec_2;
  vec_2 = input_coord(vec_2, "2");

  math_vector vec_3;
  vec_3.x = vec_1.x + vec_2.x;
  vec_3.y = vec_1.y + vec_2.y;

  return hypot(vec_3.x, vec_3.y);
}

double subtract() {  // для векторов с началом координат (0,0)
  math_vector vec_1;
  vec_1 = input_coord(vec_1, "1");

  math_vector vec_2;
  vec_2 = input_coord(vec_2, "2");

  math_vector vec_3;
  vec_3.x = vec_1.x - vec_2.x;
  vec_3.y = vec_1.y - vec_2.y;
  std::cout << "The resulting vector with coordinates x = " << vec_3.x
            << ", y = " << vec_3.y << "\n";
  return hypot(vec_3.x, vec_3.y);
}

math_vector scale() {  // для вектора с началом координат (0,0)
  math_vector vec;
  vec = input_coord(vec);
  double scalar;

  do {
    std::cout << "Input scalar number: ";
    std::cin >> scalar;
    if (scalar == 0) {
      std::cout << "A scalar cannot be equal to 0\n";
    }
  } while (scalar == 0);

  math_vector result;
  result.x = vec.x * scalar;
  result.y = vec.y * scalar;

  return result;
}

math_vector normalize() {  // для вектора с началом координат (0,0)
  math_vector vec;

  vec = input_coord(vec);

  math_vector result;
  result.x = vec.x / hypot(vec.x, vec.y);
  result.y = vec.y / hypot(vec.x, vec.y);
  return result;
}

int main() {
  std::cout << "Operations with vectors\n";
  std::cout << "To simplify: vectors always leave the origin.\n\n";
  info();

  std::string operation;

  do {
    std::cout << "Available vector operations:\n";
    std::cout << "add, subtract, scale, length, normalize\n";
    std::cout << "Input operation: ";
    std::cin >> operation;
    operation = lower_case(operation);
    if (!answer(operation)) {
      std::cout << "Unavailable operation. Please try again\n";
    }
  } while (!answer(operation));

  if (operation == "length") {
    double result = length();
    std::cout << "Length you vector = " << result << "\n";
  }

  if (operation == "add") {
    double result = add();
    std::cout << "Length of the resulting vector upon addition = " << result
              << "\n";
  }

  if (operation == "subtract") {
    double result = subtract();
    std::cout << "Length of the resulting vector upon subtraction = " << result
              << "\n";
  }

  if (operation == "scale") {
    math_vector result = scale();
    std::cout << "As a result of vector normalization, the coordinates were "
                 "obtained:\n "
              << "x = " << result.x << ", y = " << result.y
              << ".\n With length = " << hypot(result.x, result.y);
  }

  if (operation == "normalize") {
    math_vector result = normalize();

    std::cout << "As a result of vector normalization, the coordinates were "
                 "obtained:\n "
              << "x = " << result.x << ", y = " << result.y
              << ".\n With length = " << hypot(result.x, result.y);
  }
}