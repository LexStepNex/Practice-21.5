#include <iostream>
#include <string>
#include <vector>

enum type_room {
  bedroom = 1,
  kitchen = 2,
  bathroom = 4,
  children = 8,
  living = 16
};

enum type_building { house = 1, garage = 2, barn = 4, bathhouse = 8 };

struct buildings {
  int quantityBuilding = 0;

  int buildings_enum = 0;

  int square_house = 0;
  int square_garage = 0;
  int square_barn = 0;
  int square_bathhouse = 0;
};

struct on_floor {
  int number_floor = 0;
  int floor_height = 0;

  int rooms_on_floor = 0;
  int rooms_enum = 0;

  int square_bedroom = 0;
  int square_kitchen = 0;
  int square_bathroom = 0;
  int square_children = 0;
  int square_living = 0;
};

struct in_house {
  int quantity_floors = 0;
  std::vector<on_floor> floor;
  bool stove_with_chimney = false;
};

struct in_bathhouse {
  bool stove_with_chimney = false;
};

struct village {
  int number = 0;
  int square_plot = 0;
  buildings construction;
  in_house house;
  in_bathhouse bathhouse;
};

std::string lower_case(std::string str) {
  int sizeStr = str.size();
  for (int i = 0; i < sizeStr; i++) {
    str[i] = std::tolower(str[i]);
  }
  return str;
}

bool number_match(std::vector<village> plot_land, int number_plot, int ind) {
  for (int i = 0; i < ind; i++) {
    if (plot_land[i].number == number_plot) {
      std::cout << "A plot with the same number already exists\n";
      std::cout << "Please, try again\n";
      return false;
    }
  }
  return true;
}

int square_plots(int number_plot) {
  int square;
  do {
    std::cout << "Input area plot number " << number_plot << ": ";
    std::cin >> square;
    if (square < 0) std::cout << "The area must be greater than 0.\n";
  } while (square < 0);

  return square;
}

int quantity_constructions() {
  int quantity;
  do {
    std::cout << "Input quantity buildings on plot (from 0 to 4): ";
    std::cin >> quantity;

    if (quantity == 0) {
      std::cout << "We move on to the next piece of land, "
                << "since there are no buildings\n";
      continue;
    }

    if (0 > quantity || quantity > 4) {
      std::cout << "Error. Try again\n";
    }
  } while (0 > quantity || quantity > 4);

  return quantity;
}

void add_square_constructions(village& plot_land, int square_plot) {
  int square_buildings;
  do {
    square_buildings = 0;
    if (plot_land.construction.buildings_enum & type_building::house) {
      std::cout << "Input square house: ";
      std::cin >> plot_land.construction.square_house;
      square_buildings += plot_land.construction.square_house;
    }
    if (plot_land.construction.buildings_enum & type_building::garage) {
      std::cout << "Input square garage: ";
      std::cin >> plot_land.construction.square_garage;
      square_buildings += plot_land.construction.square_garage;
    }
    if (plot_land.construction.buildings_enum & type_building::barn) {
      std::cout << "Input square barn: ";
      std::cin >> plot_land.construction.square_barn;
      square_buildings += plot_land.construction.square_barn;
    }
    if (plot_land.construction.buildings_enum & type_building::bathhouse) {
      std::cout << "Input square bathhouse: ";
      std::cin >> plot_land.construction.square_bathhouse;
      square_buildings += plot_land.construction.square_bathhouse;
    }

    if (square_plot < square_buildings) {
      std::cout << "The total area of buildings cannot be greater than the "
                   "area of the plot\n";
      std::cout << "Try again\n";
    }
  } while (square_plot < square_buildings);
}

void add_buildings(int numbers, int square_plot, village& plot_land) {
  std::cout << "List the buildings on the plot\n";
  for (int i = 0; i < numbers;) {
    std::string answer;
    int add_number = 0;

    do {
      add_number = 0;
      std::cout << "\nInput name construction\n";
      std::cout
          << "("
          << (!(plot_land.construction.buildings_enum & type_building::house)
                  ? "house, "
                  : "")
          << (!(plot_land.construction.buildings_enum & type_building::garage)
                  ? "garage, "
                  : "")
          << (!(plot_land.construction.buildings_enum & type_building::barn)
                  ? "barn, "
                  : "")
          << (!(plot_land.construction.buildings_enum &
                type_building::bathhouse)
                  ? "bathhouse"
                  : "")
          << "):\n";
      std::cin >> answer;
      answer = lower_case(answer);

      if (answer == "house") add_number = type_building::house;
      if (answer == "garage") add_number = type_building::garage;
      if (answer == "barn") add_number = type_building::barn;
      if (answer == "bathhouse") add_number = type_building::bathhouse;

      if (plot_land.construction.buildings_enum & add_number ||
          add_number == 0) {
        std::cout << "Invalid name building entered or "
                  << "such a building already exists\n";
        std::cout << "Please try again\n";
        add_number = plot_land.construction.buildings_enum;
      } else {
        plot_land.construction.buildings_enum |= add_number;
        add_number = ~plot_land.construction.buildings_enum;
      }
    } while (plot_land.construction.buildings_enum == add_number);
    i++;
  }
  add_square_constructions(plot_land, square_plot);
}

int floors_in_house() {
  int quantity = 0;
  do {
    std::cout << "Input quantity floors in house(from 1 to 3): ";
    std::cin >> quantity;
    if (1 > quantity || quantity > 3) {
      std::cerr << "Error. Please try again.\n";
    }
  } while (1 > quantity || quantity > 3);
  return quantity;
}

void add_square_rooms(on_floor floor, int number_floor, int square_house) {
  int square_rooms;
  do {
    square_rooms = 0;
    if (floor.rooms_enum & type_room::bedroom) {
      std::cout << "Input square bedroom on the " << number_floor << " floor: ";
      std::cin >> floor.square_bedroom;
      square_rooms += floor.square_bedroom;
    }
    if (floor.rooms_enum & type_room::kitchen) {
      std::cout << "Input square kitchen on the " << number_floor << " floor: ";
      std::cin >> floor.square_kitchen;
      square_rooms += floor.square_kitchen;
    }
    if (floor.rooms_enum & type_room::bathroom) {
      std::cout << "Input square bathroom on the " << number_floor
                << " floor: ";
      std::cin >> floor.square_bathroom;
      square_rooms += floor.square_bathroom;
    }
    if (floor.rooms_enum & type_room::children) {
      std::cout << "Input square children on the " << number_floor
                << " floor: ";
      std::cin >> floor.square_children;
      square_rooms += floor.square_children;
    }
    if (floor.rooms_enum & type_room::living) {
      std::cout << "Input square living on the " << number_floor << " floor: ";
      std::cin >> floor.square_living;
      square_rooms += floor.square_living;
    }

    if (square_house < square_rooms) {
      std::cout
          << "The total area of rooms on floor cannot be greater than the "
             "area of the house\n";
      std::cout << "Try again\n";
    }
  } while (square_house < square_rooms);
}

void floor_info(on_floor floor, int rooms_on_floor, int number_floor,
                int square_house) {
  std::cout << "List the rooms on the " << number_floor << " floor\n";
  for (int i = 0; i < rooms_on_floor;) {
    std::string answer;
    int add_number = 0;

    do {
      add_number = 0;
      std::cout << "\nInput name room\n";
      std::cout << "("
                << (!(floor.rooms_enum & type_room::bedroom) ? "bedroom, " : "")
                << (!(floor.rooms_enum & type_room::kitchen) ? "kitchen, " : "")
                << (!(floor.rooms_enum & type_room::bathroom) ? "bathroom, "
                                                              : "")
                << (!(floor.rooms_enum & type_room::children) ? "children, "
                                                              : "")
                << (!(floor.rooms_enum & type_room::living) ? "living" : "")
                << "):\n";
      std::cin >> answer;
      answer = lower_case(answer);

      if (answer == "bedroom") add_number = type_room::bedroom;
      if (answer == "kitchen") add_number = type_room::kitchen;
      if (answer == "bathroom") add_number = type_room::bathroom;
      if (answer == "children") add_number = type_room::children;
      if (answer == "living") add_number = type_room::living;

      if (floor.rooms_enum & add_number || add_number == 0) {
        std::cout << "Invalid name room entered or "
                  << "such a room already exists\n";
        std::cout << "Please try again\n";
        add_number = floor.rooms_enum;
      } else {
        floor.rooms_enum |= add_number;
        add_number = ~floor.rooms_enum;
      }
    } while (floor.rooms_enum == add_number);
    i++;
  }
  add_square_rooms(floor, number_floor, square_house);
}

int rooms_floor(int number_floor) {
  int rooms;
  do {
    std::cout << "Input quantity rooms on " << number_floor << " floor\n";
    std::cout << "(from 2 to 4 rooms): ";
    std::cin >> rooms;
    if (2 > rooms || rooms > 4) {
      std::cerr << "Error. Please try again.\n";
    }
  } while (2 > rooms || rooms > 4);

  return rooms;
}

bool stove(std::string construction) {
  std::string answer;
  do {
    std::cout << "Does the " << construction
              << " have a stove with a chimney?\n";
    std::cout << "Answer yes or no: ";
    std::cin >> answer;
    answer = lower_case(answer);
    if (answer != "yes" && answer != "no") {
      std::cout << "Error. Try again\n";
    }
  } while (answer != "yes" && answer != "no");

  if (answer == "yes")
    return true;
  else
    return false;
}

void house_info(village& plot_land, int floors, int square_house) {
  for (int i = 1; i <= floors; i++) {
    plot_land.house.floor.push_back({0});

    plot_land.house.floor[i - 1].number_floor = i;
    std::cout << "For " << i << " floor:\n";

    std::cout << "Input height floor: ";
    std::cin >> plot_land.house.floor[i - 1].floor_height;

    plot_land.house.floor[i - 1].rooms_on_floor = rooms_floor(i);
    floor_info(plot_land.house.floor[i - 1],
               plot_land.house.floor[i - 1].rooms_on_floor, i, square_house);
  }

  plot_land.house.stove_with_chimney = stove("house");
}

void printStatement(std::vector<village> plot_land) {
  using namespace std;  // в связи с тем что много cout
  int square_village = 0;
  int square_all_buildings = 0;

  cout << "In your village there are plots such, as: \n\n";
  for (int i = 0; i < plot_land.size(); i++) {
    cout << "Plot number: " << plot_land[i].number << "\n";
    cout << "Area this plot: " << plot_land[i].square_plot << "\n";
    square_village += plot_land[i].square_plot;

    cout << "Quantity buildings on plot - "
         << plot_land[i].construction.quantityBuilding << ", including:\n";
    if (plot_land[i].construction.buildings_enum & type_building::house) {
      cout << "house "
           << "with square: " << plot_land[i].construction.square_house << "\n";
      square_all_buildings += plot_land[i].construction.square_house;
    }
    if (plot_land[i].construction.buildings_enum & type_building::garage) {
      cout << "garage "
           << "with square: " << plot_land[i].construction.square_garage
           << "\n";
      square_all_buildings += plot_land[i].construction.square_garage;
    }
    if (plot_land[i].construction.buildings_enum & type_building::barn) {
      cout << "barn "
           << "with square: " << plot_land[i].construction.square_barn << "\n";
      square_all_buildings += plot_land[i].construction.square_barn;
      
    }
    if (plot_land[i].construction.buildings_enum & type_building::bathhouse) {
      cout << "bathhouse "
           << "with square: " << plot_land[i].construction.square_bathhouse
           << "\n";
      square_all_buildings += plot_land[i].construction.square_bathhouse;
    if (plot_land[i].bathhouse.stove_with_chimney == true) {
        std::cout << "Bathhouse have stove with chimney.\n";
      }
    }

    if (plot_land[i].construction.buildings_enum & type_building::house) {
      cout << "In house: " << plot_land[i].house.quantity_floors << " floors\n";

      int floors = plot_land[i].house.quantity_floors;
      for (int j = 0; j < floors; j++) {
        cout << "On " << j + 1  << " floor "
             << plot_land[i].house.floor[j].rooms_on_floor << " rooms: \n";
        cout << "Height floor " << plot_land[i].house.floor[j].floor_height << " m.\n";

        if (plot_land[i].house.floor[j].rooms_enum & type_room::bedroom) {
          cout << "bedroom "
               << "with square:" << plot_land[i].house.floor[j].square_bedroom
               << "\n";
        }
        if (plot_land[i].house.floor[j].rooms_enum & type_room::kitchen) {
          cout << "kitchen "
               << "with square:" << plot_land[i].house.floor[j].square_kitchen
               << "\n";
        }
        if (plot_land[i].house.floor[j].rooms_enum & type_room::bathroom) {
          cout << "bathroom "
               << "with square:" << plot_land[i].house.floor[j].square_bathroom
               << "\n";
        }
        if (plot_land[i].house.floor[j].rooms_enum & type_room::children) {
          cout << "children "
               << "with square:" << plot_land[i].house.floor[j].square_children
               << "\n";
        }
        if (plot_land[i].house.floor[j].rooms_enum & type_room::living) {
          cout << "living "
               << "with square:" << plot_land[i].house.floor[j].square_living
               << "\n";
        }
      }

      if (plot_land[i].house.stove_with_chimney == true) {
        cout << "House have stove with chimney.\n";
      }
    } else {
      cout << "There is no house on this plot\n";
    }
    cout << "\n";
  }

  cout << "\n";
  cout << "Square village = " << square_village << "\n";
  cout << "Total square of all buildings = " << square_all_buildings << "\n";
  double percentage_of_buildings =
      ((double)square_all_buildings / (double)square_village) * 100.0;
  cout << "Percentage of building area to village area = "
       << percentage_of_buildings << "\n";
}

int main() {
  std::cout << "Statement village\n\n";
  int n;
  std::cout << "Input quantity plot of land: ";
  std::cin >> n;
  std::vector<village> plot_land(n);

  for (int i = 0; i < n; i++) {
    do {
      std::cout << "Input number plot: ";
      std::cin >> plot_land[i].number;
    } while (!number_match(plot_land, plot_land[i].number, i));

    plot_land[i].square_plot = square_plots(plot_land[i].number);

    plot_land[i].construction.quantityBuilding = quantity_constructions();
    if (plot_land[i].construction.quantityBuilding == 0) continue;

    add_buildings(plot_land[i].construction.quantityBuilding,
                  plot_land[i].square_plot, plot_land[i]);

    if (plot_land[i].construction.buildings_enum & type_building::house) {
      plot_land[i].house.quantity_floors = floors_in_house();

      int square_house = plot_land[i].construction.square_house;
      house_info(plot_land[i], plot_land[i].house.quantity_floors,
                 square_house);
    } else {
      std::cout << "There is no house on this plot\n";
    }

    if (plot_land[i].construction.buildings_enum & type_building::bathhouse) {
      plot_land[i].bathhouse.stove_with_chimney = stove("bathhouse");
    } else {
      std::cout << "There is no bathhouse on this plot\n";
    }
  }
  std::cout << "\n";
  printStatement(plot_land);
}