#include "server_character_factory.h"

#define MAGICIAN 1
#define CLERIC 2
#define PALADIN 3
#define WARRIOR 4

#define HUMAN 1
#define ELF 2
#define DWARF 3
#define GNOME 4

CharacterClass CharacterFactory::make_class(const int class_id, Json::Value& config) {
    switch (class_id) {
        case MAGICIAN: return Magician(config);
        case CLERIC: return Cleric(config);
        case PALADIN: return Paladin(config);
    }
    return Warrior(config);
}

Race CharacterFactory::make_race(const int race_id, Json::Value& config) {
    switch (race_id) {
        case HUMAN: return Human(config);
        case ELF: return Elf(config);
        case DWARF: return Dwarf(config);
    }
    return Gnome(config);
}
