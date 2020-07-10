#ifndef _SERVER_RACE
#define _SERVER_RACE

#include <stdint.h>
#include <jsoncpp/json/json.h>

/* Clase que representa a una raza del juego. Posee algunos stats. */
class Race {
protected:
    int16_t id;
    // Stats
    int strength, agility, intelligence, constitution;
    // Multipliers
    float life_multiplier, mana_multiplier;
    int recovery_factor;

public:
    // Contructor
    explicit Race(int initial_attributes);

    // getter fuerza
    int get_strength();

    // getter agilidad
    int get_agility();

    // getter inteligencia
    int get_intelligence();
    
    // getter constitucion
    int get_constitution();

    // getter life multiplier
    float get_life_multiplier();

    // getter mana multiplier
    float get_mana_multiplier();
    
    // getter recovery factor
    int get_recovery_factor();

    // getter race id
    int16_t get_id() const;
};


#endif //_SERVER_RACE
