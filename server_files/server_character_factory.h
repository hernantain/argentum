#ifndef _CHARACTER_FACTORY_H
#define _CHARACTER_FACTORY_H

#include <stdint.h>
#include "server_race.h"
#include "server_elf.h"
#include "server_gnome.h"
#include "server_dwarf.h"
#include "server_human.h"
#include "server_magician.h"
#include "server_cleric.h"
#include "server_warrior.h"
#include "server_paladin.h"

/* Clase que funciona como factory para los distintos tipos de personaje de la aplicacion */
class CharacterFactory {
public:

    /* Recibiendo un id crea la clase correspondiente */
    static CharacterClass make_class(const uint8_t class_id, Json::Value& config);
    static Race make_race(const uint8_t race_id, Json::Value& config);

};

#endif // _CHARACTER_FACTORY_H
