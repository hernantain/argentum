#ifndef _DRAWABLE
#define _DRAWABLE

#include <SDL2/SDL.h>
#include <stdint.h>


class Drawable {

    protected:
        uint16_t id;
        int orientation;
        SDL_Renderer* gRenderer;

    public:
        Drawable(uint16_t id, SDL_Renderer* gRenderer);

        virtual ~Drawable();

};

enum PlayerMoving {
	STANDING = 0,
	LEFT = 1,
	RIGHT = 2,
	UP = 3,
	DOWN = 4
};

#endif
