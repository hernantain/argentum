
#define RACE_ARG 1
#define CLASS_ARG 2
#define TOTAL_ARGS 3

#define MAGICIAN_CODE 1
#define CLERIC_CODE 2
#define PALADIN_CODE 3
#define WARRIOR_CODE 4

#define HUMAN_CODE 1
#define ELF_CODE 2
#define DWARF_CODE 3
#define GNOME_CODE 4

#define WRONG_ARG -1

#define ERROR 1
#define USAGE "Uso: ./client <raza> <clase>" 

#include "client_game.h"
#include <string>


int get_class(std::string player_class) {
    if (player_class == "mago") return MAGICIAN_CODE;
    if (player_class == "clerigo") return CLERIC_CODE;
    if (player_class == "paladin") return PALADIN_CODE;
    if (player_class == "guerrero") return WARRIOR_CODE;
    
    return WRONG_ARG;
}


int get_race(std::string race) {
    if (race == "humano") return HUMAN_CODE;
    if (race == "elfo") return ELF_CODE;
    if (race == "enano") return DWARF_CODE;
    if (race == "gnomo") return GNOME_CODE;
    
    return WRONG_ARG;
}



int main(int argc, char* argv[]) {

    if (argc != TOTAL_ARGS) {
        std::cout << USAGE << std::endl;
        return ERROR;
    }

    int race = get_race(argv[RACE_ARG]);
    if (race == WRONG_ARG) {
        std::cout << "Raza invalida. Debe ser alguna de las siguientes:" << std::endl;
        std::cout << "\t* humano" << std::endl;
        std::cout << "\t* elfo" << std::endl;
        std::cout << "\t* enano" << std::endl;
        std::cout << "\t* gnomo" << std::endl;
        return ERROR;
    }

    int player_class = get_class(argv[CLASS_ARG]);
    if (player_class == WRONG_ARG) {
        std::cout << "Clase invalida. Debe ser alguna de las siguientes:" << std::endl;
        std::cout << "\t* mago" << std::endl;
        std::cout << "\t* clerigo" << std::endl;
        std::cout << "\t* paladin" << std::endl;
        std::cout << "\t* guerrero" << std::endl;
        return ERROR;
    }

    Game game(race, player_class);
    game.run();

	return 0;
}


