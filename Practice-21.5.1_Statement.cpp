#include <fstream>
#include <iostream>
#include <regex>
#include <string>

struct paymentData {
  std::string name = "unnamed";
  std::string surname = "unnamed";
  std::string date = "unnamed";
  std::string moneyStr = "unnamed";
};

bool dateControl(std::string date) {
  std::cmatch result;
  std::regex is31Day(
      "([0]?[1-9]|[1-2]?[0-9]|[3]?[0-1])\\.([0]?[13578]|[1][02])\\.(\\d+)");
  std::regex is30Day(
      "([0]?[1-9]|[1-2]?[0-9]|[3]?[0])\\.([0]?[469]|[1][1])\\.(\\d+)");
  std::regex february("([0]?[1-9]|[1-2]?[0-9])\\.(0?2)\\.(\\d+)");

  if (std::regex_match(date.c_str(), result, february)) {
    int dd = stoi(result[0]);
    int yyyy = stoi(result[3]);

    if ((yyyy % 400 == 0) || (yyyy % 4 == 0 && yyyy % 100 != 0)) {
      if (dd <= 29) {
        return true;
      } else
        return false;
    } else {
      if (dd <= 28) {
        return true;
      } else
        return false;
    }
  } else if (std::regex_match(date.c_str(), is30Day)) {
    return true;
  } else if (std::regex_match(date.c_str(), is31Day)) {
    return true;
  } else {
    return false;
  }
}

double moneyControl(std::string moneyStr) {
  int sizeMoneyStr = moneyStr.length();
  int countDot = 0;
  for (int i = 0; i < sizeMoneyStr; i++) {
    if (i == 0 && moneyStr[i] == '-') {
      std::cerr << "The monetary amount must be positive\n";
      return -1;
    }

    if (!std::isdigit(moneyStr[i]) && moneyStr[i] != '.') {
      std::cerr << "Error entering monetary amount\n";
      return -1;
    }
    if (moneyStr[i] == '.') {
      countDot++;
    }
    if (countDot > 1) {
      std::cerr << "There cannot be more than one dot in a monetary amount.\n";
      return -1;
    }
  }
  return stod(moneyStr);
}

std::string lower_case(std::string str) {
  int sizeStr = str.size();
  for (int i = 0; i < sizeStr; i++) {
    str[i] = std::tolower(str[i]);
  }
  return str;
}

bool repeat() {
  std::string answer;
  std::cout << "Do you want to continue working with the file?\n";
  do {
    std::cout << "Input \"yes\" or \"no\": ";
    std::cin >> answer;
    answer = lower_case(answer);
  } while (answer != "yes" && answer != "no");

  if (answer == "yes")
    return true;
  else
    return false;
}

void add(paymentData& person) {
  std::ofstream statement("statement.txt", std::ios::app);

  std::cout << "Input name : ";
  std::cin >> person.name;
  statement << person.name << ' ';

  std::cout << "Input surname: ";
  std::cin >> person.surname;
  statement << person.surname << ' ';

  do {
    std::cout << "Input date (format dd.mm.yyyy): ";
    std::cin >> person.date;
    if (!dateControl(person.date)) std::cerr << "Please, try again.\n";
  } while (!dateControl(person.date));
  statement << person.date << ' ';

  do {
    std::cout << "Enter payment: ";
    std::cin >> person.moneyStr;
    if (moneyControl(person.moneyStr) < 0) std::cerr << "Please, try again.\n";
  } while (moneyControl(person.moneyStr) < 0);

  double money = stod(person.moneyStr);
  statement.setf(std::ios::showpoint);
  statement.setf(std::ios::fixed);
  statement.precision(2);

  statement << money << " RUB\n";
  statement.close();
}

std::string outputAlignment(std::string str) {
  std::string alignment = "";
  if (str.length() < 10) {
    for (int count = 0; count < 10 - str.length(); count++) alignment += " ";
  }
  return alignment;
}

void list(paymentData* person) {
  std::ifstream statement("Statement.txt");
  if (!statement.is_open()) {
    std::cerr << "File \"Statement.txt\" not found\n";
    std::cerr << "Please select \"add\" first\n";
    return;
  }

  std::string currency;

  while (statement >> person->name >> person->surname >> person->date >>
         person->moneyStr >> currency) {
    std::cout << person->name << outputAlignment(person->name) << "\t"
              << person->surname << outputAlignment(person->surname) << "\t"
              << person->date << "\t" << person->moneyStr << " " << currency
              << "\n";
  }
  statement.close();
}

int main() {
  paymentData person;
  std::string answer;

  do {
    do {
      std::cout << "Input \"add\" or \"list\": ";
      std::cin >> answer;
      answer = lower_case(answer);
      if (answer != "add" && answer != "list")
        std::cout << "Error input. Please try again\n";
    } while (answer != "add" && answer != "list");

    if (answer == "add") add(person);
    if (answer == "list")
      list(&person);  // Для себя сделал 2 варианта
                      // с ссылкой и указателем
  } while (repeat());
}