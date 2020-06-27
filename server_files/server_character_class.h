#ifndef _SERVER_CHARACTER_CLASS
#define _SERVER_CHARACTER_CLASS

#include <jsoncpp/json/json.h>

/* Clase que representa a una clase del juego. Posee algunos stats. */
class CharacterClass {
protected:
    float life_multiplier;
    float mana_multiplier;
    float meditation_multiplier;

public:
    // Contructor
    CharacterClass();

    // Devuelve el multiplicador de vida de la clase
    float get_life_multiplier();

    // Devuelve el multiplicador de mana de la clase
    float get_mana_multiplier();

    // Devuelve el multiplicador de meditacion de la clase
    float get_meditation_multiplier();
};


#endif //_SERVER_CHARACTER_CLASS
