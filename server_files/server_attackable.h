#ifndef _SERVER_ATTACKABLE
#define _SERVER_ATTACKABLE

#include <stdint.h>

/* 
 * Clase que representa a un atacable del juego.
 * Va a funcionar como interfaz para poder hacer
 * polimorfismo entre los NPCs y los Characters
 */
class Attackable {
private:
    void get_experience(Attackable& other, int damage);
    virtual bool can_attack(Attackable& other) = 0;

public:
    virtual bool is_safe() = 0;
    virtual bool is_newbie() = 0;
    virtual bool is_alive() const = 0;
    virtual void drop_items(std::vector<Item> &worldItems) = 0;
    virtual uint16_t get_id() const = 0;
    virtual int16_t get_max_life() const = 0;
    virtual int16_t get_level() const = 0;
    virtual int16_t get_body_pos_X() const = 0;
    virtual int16_t get_body_pos_Y() const = 0;
    virtual int defense(int damage) = 0;
    virtual void attack(Attackable& other) = 0;
};


#endif //_CHARACTER
