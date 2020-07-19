#ifndef _CLIENT_COMMON_CLOTHES
#define _CLIENT_COMMON_CLOTHES

#include "client_clothes.h"


class CommonTallClothes: public Clothes {

    public:
        CommonTallClothes(SDL_Renderer* gRenderer, int width, int height);

        virtual bool load_pictures(SDL_Renderer* gRenderer) override;

        virtual ~CommonTallClothes();
};



class CommonShortClothes: public Clothes {

    public:
        CommonShortClothes(SDL_Renderer* gRenderer, int width, int height);

        virtual bool load_pictures(SDL_Renderer* gRenderer) override;

        virtual ~CommonShortClothes();
};


#endif


