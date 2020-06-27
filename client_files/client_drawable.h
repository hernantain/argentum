#ifndef _DRAWABLE
#define _DRAWABLE



class Drawable {

    protected:
        int velX, velY;
        int frame;
        int orientation;
        int drawable_speed;

    public:
        Drawable(int drawable_speed);


};



#endif
