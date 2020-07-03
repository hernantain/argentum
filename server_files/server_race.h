#ifndef _SERVER_RACE
#define _SERVER_RACE

#include <stdint.h>
#include <jsoncpp/json/json.h>

/* Clase que representa a una raza del juego. Posee algunos stats. */
class Race {
protected:
    int16_t id;
    // Stats
    int strength;
    int agility;
    int intelligence;
    int constitution;
    // Multipliers
    float life_multiplier;
    float mana_multiplier;
    float recovery_multiplier;

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
    
    // getter recovery multiplier
    float get_recovery_multiplier();

    // getter race id
    int16_t get_id() const;
};


#endif //_SERVER_RACE
