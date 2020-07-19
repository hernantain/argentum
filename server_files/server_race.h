#ifndef _SERVER_RACE
#define _SERVER_RACE

#include <stdint.h>
#include <jsoncpp/json/json.h>

/* Clase que representa a una raza del juego. Posee algunos stats. */
class Race {
protected:
    uint8_t id;
    // Stats
    int strength, agility, intelligence, constitution;
    // Multipliers
    float life_multiplier, mana_multiplier;
    int recovery_factor;
    // Graphics
    int width, height;

public:
    // Contructor
    explicit Race(int initial_attributes);

    // getter fuerza
    int get_strength() const;

    // getter agilidad
    int get_agility() const;

    // getter inteligencia
    int get_intelligence() const;
    
    // getter constitucion
    int get_constitution() const;

    // getter life multiplier
    float get_life_multiplier() const;

    // getter mana multiplier
    float get_mana_multiplier() const;
    
    // getter recovery factor
    int get_recovery_factor() const;

     // getter recovery factor
    int get_width() const;

     // getter recovery factor
    int get_height() const;

    // getter race id
    uint8_t get_id() const;
};


#endif //_SERVER_RACE
