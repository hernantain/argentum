#ifndef _DRAWABLE
#define _DRAWABLE

#include <SDL2/SDL.h>
#include <stdint.h>


class Drawable {

    protected:
        int16_t id;
        int frame;
        int orientation;
        SDL_Renderer* gRenderer;

    public:
        Drawable(int16_t id, SDL_Renderer* gRenderer);

};



#endif
