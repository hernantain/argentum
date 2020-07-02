#ifndef _DRAWABLE
#define _DRAWABLE

#include <stdint.h>

class Drawable {

    protected:
        int16_t id;
        int velX, velY;
        int frame;
        int orientation;
        int drawable_speed;

    public:
        Drawable(int drawable_speed, int16_t id);


};



#endif
