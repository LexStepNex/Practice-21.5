#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include <vector>

struct world {
  char area[20][20];
};

struct coordinate {
  int x = -1;
  int y = -1;
};

struct character {
  std::string name = "unnamed";
  std::string side = "unnamed";

  coordinate place;

  int heals = 0;
  int armor = 0;
  int damage = 0;

  bool alive = false;
};

void print_map(world& map, std::vector<character> enemy, character player) {
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 20; j++) {
      map.area[i][j] = '.';
    }
  }

  for (int k = 0; k < enemy.size(); k++) {
    if (enemy[k].alive == true)
      map.area[enemy[k].place.y][enemy[k].place.x] = 'E';
  }

  map.area[player.place.y][player.place.x] = 'P';

  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 20; j++) {
      std::cout << map.area[i][j];
    }
    std::cout << "\n";
  }
  std::cout << "\n";

  std::cout << player.name << "\n";
  std::cout << "You HP: " << player.heals << "\n";
  std::cout << "You Armor: " << player.armor << "\n";
  std::cout << "\n";
}

bool correct_place_enemy(std::vector<character>& enemy, int index) {
  int enemy_size = enemy.size();
  for (int i = 0; i < enemy_size; i++) {
    if (i == index) continue;

    if (enemy[i].place.x == enemy[index].place.x &&
        enemy[i].place.y == enemy[index].place.y)
      return false;
  }

  return true;
}

bool correct_place_enemy(std::vector<character>& enemy, character& player,
                         int index) {
  if (player.place.x == enemy[index].place.x &&
      player.place.y == enemy[index].place.y)
    return false;

  int enemy_size = enemy.size();
  for (int i = 0; i < enemy_size; i++) {
    if (i == index) continue;

    if (enemy[i].place.x == enemy[index].place.x &&
        enemy[i].place.y == enemy[index].place.y)
      return false;
  }

  return true;
}

bool correct_place_player(character& player, std::vector<character>& enemy) {
  int enemy_size = enemy.size();
  for (int i = 0; i < enemy_size; i++) {
    if (enemy[i].place.x == player.place.x &&
        enemy[i].place.y == player.place.y)
      return false;
  }

  return true;
}

void new_game_enemy(std::vector<character>& enemy) {
  std::random_device rand;
  std::mt19937 generate(rand());
  std::uniform_int_distribution<> range_for_place(0, 19);

  std::uniform_int_distribution<> range_for_armor(0, 50);
  std::uniform_int_distribution<> range_for_heals(50, 150);
  std::uniform_int_distribution<> range_for_damage(15, 30);

  for (int i = 0; i < enemy.size(); i++) {
    enemy[i].side = "mob";

    enemy[i].name = "Enemy #";
    enemy[i].name += (i + 1) + '0';

    do {
      enemy[i].place.x = range_for_place(generate);
      enemy[i].place.y = range_for_place(generate);
    } while (!correct_place_enemy(enemy, i));

    enemy[i].heals = range_for_heals(generate);
    enemy[i].armor = range_for_armor(generate);
    enemy[i].damage = range_for_damage(generate);

    enemy[i].alive = true;
  }
  std::cout << "Enemy team creation completed successfully\n";
}

void new_game_player(std::vector<character>& enemy, character& player) {
  player.side = "player";

  std::cout << "Create your character:\n";

  std::cout << "Input name: ";
  std::cin >> player.name;

  std::cout << "Enter the character's number of lives: ";
  std::cin >> player.heals;

  std::cout << "Enter the amount of character armor: ";
  std::cin >> player.armor;

  std::cout << "Enter character damage: ";
  std::cin >> player.damage;

  std::random_device rand;
  std::mt19937 generate(rand());
  std::uniform_int_distribution<> range_for_place(0, 19);
  do {
    player.place.x = range_for_place(generate);
    player.place.y = range_for_place(generate);
  } while (!correct_place_player(player, enemy));

  player.alive = true;
}

std::string upper_case(std::string str) {
  int sizeStr = str.size();
  for (int i = 0; i < sizeStr; i++) {
    str[i] = std::toupper(str[i]);
  }
  return str;
}

std::string answer_player() {
  std::string answer;
  do {
    std::cout << "Enter direction of travel(L, R, U or D):\n";
    std::cout << "L - Left, R - right, U - Up, D - Down\n";

    std::cin >> answer;
    answer = upper_case(answer);
  } while (answer != "L" && answer != "R" && answer != "U" && answer != "D");

  return answer;
}

bool behind_map(character person) {
  if (person.place.x < 0 || person.place.x > 19) {
    return true;
  }
  if (person.place.y < 0 || person.place.y > 19) {
    return true;
  }
  return false;
}

int index_enemy(character& player, std::vector<character>& enemy, int i) {
  int enemy_size = enemy.size();
  for (int i = 0; i < enemy_size; i++) {
    if (enemy[i].place.x == player.place.x &&
        enemy[i].place.y == player.place.y)
      return i;
  }
  return i;
}

void player_attack(character& player, character& enemy) {
  enemy.armor -= player.damage;

  if (enemy.armor < 0) {
    enemy.heals += enemy.armor;
    enemy.armor = 0;
  }

  if (enemy.heals <= 0) {
    enemy.alive = false;
    enemy.side = "Dead enemy";
    enemy.place.x = -1;
    enemy.place.y = -1;
    std::cout << "Enemy killed\n";
  }
}

void enemy_attack(character& player, character& enemy) {
  player.armor -= enemy.damage;

  if (player.armor < 0) {
    player.heals += player.armor;
    player.armor = 0;
  }

  if (enemy.heals <= 0) {
    player.alive = false;
    player.side = "Dead player";
    player.place.x = -2;
    player.place.y = -2;
    std::cout << "YOU DIED\n";
  }
}

void move_player(character& player, std::vector<character>& enemy) {
  int x = player.place.x;
  int y = player.place.y;

  std::string answer = answer_player();

  if (answer == "L") player.place.x--;
  if (answer == "R") player.place.x++;
  if (answer == "U") player.place.y--;
  if (answer == "D") player.place.y++;

  if (behind_map(player)) {
    player.place.x = x;
    player.place.y = y;
    return;
  }

  if (!correct_place_player(player, enemy)) {
    int i = index_enemy(player, enemy, i);
    if (i >= 0 && i <= 4) {
      player_attack(player, enemy[i]);
      player.place.x = x;
      player.place.y = y;
    } else {
      return;
    }
  }
}

void move_enemy(std::vector<character>& enemy, character& player) {
  std::random_device rand;
  std::mt19937 gen(rand());
  std::uniform_int_distribution<> for_ans(1, 5);

  int enemy_size = enemy.size();
  for (int i = 0; i < enemy_size; i++) {
    if (enemy[i].alive == false) continue;

    int x = enemy[i].place.x;
    int y = enemy[i].place.y;

    if (for_ans(gen) == 1) {
      enemy[i].place.x--;
    }
    if (for_ans(gen) == 2) {
      enemy[i].place.x++;
    }
    if (for_ans(gen) == 3) {
      enemy[i].place.y--;
    }
    if (for_ans(gen) == 4) {
      enemy[i].place.y++;
    }
    if (for_ans(gen) == 5) {
      // dont move
      return;
    }

    if (behind_map(enemy[i])) {
      enemy[i].place.x = x;
      enemy[i].place.y = y;
      return;
    }

    if (!correct_place_enemy(enemy, player, i)) {
      if (enemy[i].place.x == player.place.x &&
          enemy[i].place.y == player.place.y) {
        enemy_attack(player, enemy[i]);
        enemy[i].place.x = x;
        enemy[i].place.y = y;
      } else {
        enemy[i].place.x = x;
        enemy[i].place.y = y;
        return;
      }
    }
  }
}

int main() {
  std::cout << "Play RPG game\n";
  world map;
  std::vector<character> enemy(5);
  character player;
  new_game_enemy(enemy);
  new_game_player(enemy, player);

  do {
    print_map(map, enemy, player);
    move_player(player, enemy);
    move_enemy(enemy, player);
  } while (player.alive);
}