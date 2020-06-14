

#include "client_drawable.h"


Drawable::Drawable( 
    int drawable_speed) : velX(0),
                        velY(0),
                        frame(0),
                        orientation(STANDING),
                        drawable_speed(drawable_speed) {}



Player::Player(
    int bodyPosX, 
    int bodyPosY, 
    int headPosX, 
    int headPosY) : Drawable(3),
                    bodyPosX(bodyPosX), 
                    bodyPosY(bodyPosY),
                    headPosX(headPosX),
                    headPosY(headPosY) {}

    


TallPlayer::TallPlayer() : Player(25, 25, 29, 15) {}


ShortPlayer::ShortPlayer() : Player(25, 25, 28, 13) {}





ProtocolMessage Player::handleEvent( SDL_Event& e ) {
	//If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ) {
		switch( e.key.keysym.sym ) { 						//Adjust velocity
            
            case SDLK_UP: 
				velY -= drawable_speed; 
				orientation = UP;
				break;

            case SDLK_DOWN: 
				velY += drawable_speed;
				orientation = DOWN;
				break;

            case SDLK_LEFT: 
				velX -= drawable_speed;
				orientation = LEFT; 
				break;

            case SDLK_RIGHT: 
				velX += drawable_speed; 
				orientation = RIGHT;
				break;

        }

	} else if( e.type == SDL_KEYUP && e.key.repeat == 0 ) {
		switch( e.key.keysym.sym ) { 						//Adjust velocity
			case SDLK_UP: 
				velY += drawable_speed; 
				break;

            case SDLK_DOWN: 
				velY -= drawable_speed; 
				break;

            case SDLK_LEFT: 
				velX += drawable_speed; 
				break;

            case SDLK_RIGHT: 
				velX -= drawable_speed; 
				break;

        }
		orientation = STANDING;

	} else if ( e.type == SDL_MOUSEBUTTONDOWN) {
		
		// CODIGO PARA CUANDO QUERRAMOS MANEJAR EL CLICK DEL PERSONAJE
		// int x, y; 
		// SDL_GetMouseState( &x, &y ); 
		// std::cout << "CLICK EN: " << x << " Y EN: " << y << std::endl; 
	}

	ProtocolMessage msg(
		(int16_t) 1, 
		(int16_t) this->bodyPosX, 
		(int16_t) this->bodyPosY,
		(int16_t) this->headPosX, 
		(int16_t) this->headPosY, 
		(int16_t) this->velX, 
		(int16_t) this->velY);
	return std::move(msg);
}


void Player::set_position(int newBodyPosX, int newBodyPosY, int newHeadPosX, int newHeadPosY) {
	std::unique_lock<std::mutex> lock(this->m);
	this->bodyPosX = newBodyPosX;
	this->bodyPosY = newBodyPosY;
	this->headPosX = newHeadPosX;
	this->headPosY = newHeadPosY;
}

void Player::update_frames() {
	if (this->frame / 5 >= 5)
		this->frame = 0;
}



void Player::render(SDL_Renderer* gRenderer) {

	std::unique_lock<std::mutex> lock(this->m);
	//Show Character
	if (orientation == RIGHT) {
		SDL_Rect* currentClip = &this->walkingRightPlayer[ this->frame / 5 ];
		SDL_Rect* headClip = &this->headOrientations[1];
		SDL_Rect* helmetClip = &this->helmetOrientations[1];
		this->headTexture.render(headPosX, headPosY, gRenderer, headClip);
		this->helmetTexture.render(headPosX, headPosY, gRenderer, helmetClip);
		this->bodyTexture.render(bodyPosX, bodyPosY, gRenderer, currentClip);
	} else if(orientation == LEFT)  {
		SDL_Rect *currentClip = &this->walkingLeftPlayer[ this->frame / 5 ];
		SDL_Rect* headClip = &this->headOrientations[2];
		SDL_Rect* helmetClip = &this->helmetOrientations[2];
		this->headTexture.render(headPosX, headPosY, gRenderer, headClip);
		this->helmetTexture.render(headPosX, headPosY, gRenderer, helmetClip);
		this->bodyTexture.render(bodyPosX, bodyPosY, gRenderer, currentClip);
	} else if(orientation == UP)  {
		SDL_Rect *currentClip = &this->walkingBackPlayer[ this->frame / 5 ];
		SDL_Rect* headClip = &this->headOrientations[3];
		SDL_Rect* helmetClip = &this->helmetOrientations[3];
		this->headTexture.render(headPosX, headPosY, gRenderer, headClip);
		this->helmetTexture.render(headPosX-1, headPosY-1, gRenderer, helmetClip);
		this->bodyTexture.render(bodyPosX, bodyPosY, gRenderer, currentClip);
	} else if(orientation == DOWN)  {
		SDL_Rect *currentClip = &this->walkingFrontPlayer[ this->frame / 5 ];
		SDL_Rect* headClip = &this->headOrientations[0];
		SDL_Rect* helmetClip = &this->helmetOrientations[0];
		this->headTexture.render(headPosX, headPosY, gRenderer, headClip);
		this->helmetTexture.render(headPosX-1, headPosY-1, gRenderer, helmetClip);
		this->bodyTexture.render(bodyPosX, bodyPosY, gRenderer, currentClip);

	} else {
		SDL_Rect* currentClip = &this->walkingFrontPlayer[0];
		SDL_Rect* headClip = &this->headOrientations[0];
		SDL_Rect* helmetClip = &this->helmetOrientations[0];
		this->headTexture.render(headPosX, headPosY, gRenderer, headClip);
		this->helmetTexture.render(headPosX-1, headPosY-1, gRenderer, helmetClip);
		this->bodyTexture.render( bodyPosX, bodyPosY, gRenderer, currentClip);
	}
	this->frame++;
}





bool TallPlayer::load_images(SDL_Renderer* gRenderer) {
    
    //Load sprite sheet texture
	if( !this->bodyTexture.loadFromFile( "images/armadura_placas_he.png", gRenderer ) ) {
		printf( "Failed to load walking animation texture!\n" );
		return false;
	}

    if (!this->headTexture.loadFromFile("images/head.png", gRenderer)) {
		printf( "Failed to load head texture!\n" );
		return false;
	}

	if (!this->helmetTexture.loadFromFile("images/casco_hierro.png", gRenderer)) {
		printf( "Failed to load head texture!\n" );
		return false;
	}

    this->loadTallWalkingFrontSprite();
	this->loadTallWalkingBackSprite();
	this->loadTallWalkingLeftSprite();
	this->loadTallWalkingRightSprite();
	this->loadHelmetSprite();
	this->loadHeadSprite();
    return true;
}


bool ShortPlayer::load_images(SDL_Renderer* gRenderer) {

    if( !this->bodyTexture.loadFromFile( "images/armadura_placas_eg.png", gRenderer ) ) {
		printf( "Failed to load walking animation texture!\n" );
		return false;
	}

    if (!this->headTexture.loadFromFile("images/head.png", gRenderer)) {
		printf( "Failed to load head texture!\n" );
		return false;
	}

	if (!this->helmetTexture.loadFromFile("images/casco_hierro.png", gRenderer)) {
		printf( "Failed to load head texture!\n" );
		return false;
	}

    this->load_front_walking_sprite();
	this->load_back_walking_sprite();
	this->load_left_walking_sprite();
	this->load_right_walking_sprite();
    this->loadHelmetSprite();
	this->loadHeadSprite();
    return true;
}





/**
 * 
 * SPRITE LOADING
 * 
 * Esto NO queda asi. Hay que generalizarlo para 
 * cada sprite una vez que sepamos que sprites vamos a usar
 * 
 * Por ahora queda hardcodeado para el sprite de testing que estoy usando.
 * 
 */

void ShortPlayer::load_front_walking_sprite() {
	this->walkingFrontPlayer[0].x = 2;
	this->walkingFrontPlayer[0].y = 13;
	this->walkingFrontPlayer[0].w= PLAYER_WIDTH;
	this->walkingFrontPlayer[0].h= PLAYER_HEIGHT;

	this->walkingFrontPlayer[1].x = 27;
	this->walkingFrontPlayer[1].y = 13;
	this->walkingFrontPlayer[1].w= PLAYER_WIDTH;
	this->walkingFrontPlayer[1].h= PLAYER_HEIGHT;

	this->walkingFrontPlayer[2].x = 52;
	this->walkingFrontPlayer[2].y = 13;
	this->walkingFrontPlayer[2].w= PLAYER_WIDTH;
	this->walkingFrontPlayer[2].h= PLAYER_HEIGHT;

	this->walkingFrontPlayer[3].x = 77;
	this->walkingFrontPlayer[3].y = 13;
	this->walkingFrontPlayer[3].w= PLAYER_WIDTH;
	this->walkingFrontPlayer[3].h= PLAYER_HEIGHT;

	this->walkingFrontPlayer[4].x = 102;
	this->walkingFrontPlayer[4].y = 13;
	this->walkingFrontPlayer[4].w= PLAYER_WIDTH;
	this->walkingFrontPlayer[4].h= PLAYER_HEIGHT;

	this->walkingFrontPlayer[5].x = 127;
	this->walkingFrontPlayer[5].y = 13;
	this->walkingFrontPlayer[5].w= PLAYER_WIDTH;
	this->walkingFrontPlayer[5].h= PLAYER_HEIGHT;
}


void ShortPlayer::load_back_walking_sprite() {
	this->walkingBackPlayer[0].x = 2;
	this->walkingBackPlayer[0].y = 58;
	this->walkingBackPlayer[0].w= PLAYER_WIDTH;
	this->walkingBackPlayer[0].h= PLAYER_HEIGHT;

	this->walkingBackPlayer[1].x = 27;
	this->walkingBackPlayer[1].y = 58;
	this->walkingBackPlayer[1].w= PLAYER_WIDTH;
	this->walkingBackPlayer[1].h= PLAYER_HEIGHT;

	this->walkingBackPlayer[2].x = 52;
	this->walkingBackPlayer[2].y = 58;
	this->walkingBackPlayer[2].w= PLAYER_WIDTH;
	this->walkingBackPlayer[2].h= PLAYER_HEIGHT;

	this->walkingBackPlayer[3].x = 77;
	this->walkingBackPlayer[3].y = 58;
	this->walkingBackPlayer[3].w= PLAYER_WIDTH;
	this->walkingBackPlayer[3].h= PLAYER_HEIGHT;

	this->walkingBackPlayer[4].x = 102;
	this->walkingBackPlayer[4].y = 58;
	this->walkingBackPlayer[4].w= PLAYER_WIDTH;
	this->walkingBackPlayer[4].h= PLAYER_HEIGHT;

	this->walkingBackPlayer[5].x = 127;
	this->walkingBackPlayer[5].y = 58;
	this->walkingBackPlayer[5].w= PLAYER_WIDTH;
	this->walkingBackPlayer[5].h= PLAYER_HEIGHT;
}


void ShortPlayer::load_left_walking_sprite() {
	this->walkingLeftPlayer[0].x = 2;
	this->walkingLeftPlayer[0].y = 103;
	this->walkingLeftPlayer[0].w= PLAYER_WIDTH;
	this->walkingLeftPlayer[0].h= PLAYER_HEIGHT;

	this->walkingLeftPlayer[1].x = 27;
	this->walkingLeftPlayer[1].y = 103;
	this->walkingLeftPlayer[1].w= PLAYER_WIDTH;
	this->walkingLeftPlayer[1].h= PLAYER_HEIGHT;

	this->walkingLeftPlayer[2].x = 52;
	this->walkingLeftPlayer[2].y = 103;
	this->walkingLeftPlayer[2].w= PLAYER_WIDTH;
	this->walkingLeftPlayer[2].h= PLAYER_HEIGHT;

	this->walkingLeftPlayer[3].x = 77;
	this->walkingLeftPlayer[3].y = 103;
	this->walkingLeftPlayer[3].w= PLAYER_WIDTH;
	this->walkingLeftPlayer[3].h= PLAYER_HEIGHT;

	this->walkingLeftPlayer[4].x = 102;
	this->walkingLeftPlayer[4].y = 103;
	this->walkingLeftPlayer[4].w= PLAYER_WIDTH;
	this->walkingLeftPlayer[4].h= PLAYER_HEIGHT;
}


void ShortPlayer::load_right_walking_sprite() {
	this->walkingRightPlayer[0].x = 2;
	this->walkingRightPlayer[0].y = 148;
	this->walkingRightPlayer[0].w= PLAYER_WIDTH;
	this->walkingRightPlayer[0].h= PLAYER_HEIGHT;

	this->walkingRightPlayer[1].x = 27;
	this->walkingRightPlayer[1].y = 148;
	this->walkingRightPlayer[1].w= PLAYER_WIDTH;
	this->walkingRightPlayer[1].h= PLAYER_HEIGHT;

	this->walkingRightPlayer[2].x = 52;
	this->walkingRightPlayer[2].y = 148;
	this->walkingRightPlayer[2].w= PLAYER_WIDTH;
	this->walkingRightPlayer[2].h= PLAYER_HEIGHT;

	this->walkingRightPlayer[3].x = 77;
	this->walkingRightPlayer[3].y = 148;
	this->walkingRightPlayer[3].w= PLAYER_WIDTH;
	this->walkingRightPlayer[3].h= PLAYER_HEIGHT;

	this->walkingRightPlayer[4].x = 102;
	this->walkingRightPlayer[4].y = 148;
	this->walkingRightPlayer[4].w= PLAYER_WIDTH;
	this->walkingRightPlayer[4].h= PLAYER_HEIGHT;
}



void Player::loadHeadSprite() {
	this->headOrientations[0].x = 1;
	this->headOrientations[0].y = 0;
	this->headOrientations[0].w= 15;
	this->headOrientations[0].h= 17;

	this->headOrientations[1].x = 18;
	this->headOrientations[1].y = 0;
	this->headOrientations[1].w= 15;
	this->headOrientations[1].h= 17;

	this->headOrientations[2].x = 36;
	this->headOrientations[2].y = 0;
	this->headOrientations[2].w= 15;
	this->headOrientations[2].h= 17;

	this->headOrientations[3].x = 52;
	this->headOrientations[3].y = 0;
	this->headOrientations[3].w= 15;
	this->headOrientations[3].h= 17;
}

void Player::loadHelmetSprite() {
	this->helmetOrientations[0].x = 0;
	this->helmetOrientations[0].y = 0;
	this->helmetOrientations[0].w= 17;
	this->helmetOrientations[0].h= 17;

	this->helmetOrientations[1].x = 17;
	this->helmetOrientations[1].y = 0;
	this->helmetOrientations[1].w= 17;
	this->helmetOrientations[1].h= 17;

	this->helmetOrientations[2].x = 34;
	this->helmetOrientations[2].y = 0;
	this->helmetOrientations[2].w= 17;
	this->helmetOrientations[2].h= 17;

	this->helmetOrientations[3].x = 51;
	this->helmetOrientations[3].y = 0;
	this->helmetOrientations[3].w= 17;
	this->helmetOrientations[3].h= 17;
}


void TallPlayer::loadTallWalkingFrontSprite() {
	this->walkingFrontPlayer[0].x = 1;
	this->walkingFrontPlayer[0].y = 2;
	this->walkingFrontPlayer[0].w= PLAYER_WIDTH;
	this->walkingFrontPlayer[0].h= PLAYER_HEIGHT;

	this->walkingFrontPlayer[1].x = 26;
	this->walkingFrontPlayer[1].y = 2;
	this->walkingFrontPlayer[1].w= PLAYER_WIDTH;
	this->walkingFrontPlayer[1].h= PLAYER_HEIGHT;

	this->walkingFrontPlayer[2].x = 51;
	this->walkingFrontPlayer[2].y = 2;
	this->walkingFrontPlayer[2].w= PLAYER_WIDTH;
	this->walkingFrontPlayer[2].h= PLAYER_HEIGHT;

	this->walkingFrontPlayer[3].x = 76;
	this->walkingFrontPlayer[3].y = 2;
	this->walkingFrontPlayer[3].w= PLAYER_WIDTH;
	this->walkingFrontPlayer[3].h= PLAYER_HEIGHT;

	this->walkingFrontPlayer[4].x = 101;
	this->walkingFrontPlayer[4].y = 2;
	this->walkingFrontPlayer[4].w= PLAYER_WIDTH;
	this->walkingFrontPlayer[4].h= PLAYER_HEIGHT;

	this->walkingFrontPlayer[5].x = 126;
	this->walkingFrontPlayer[5].y = 2;
	this->walkingFrontPlayer[5].w= PLAYER_WIDTH;
	this->walkingFrontPlayer[5].h= PLAYER_HEIGHT;
}



void TallPlayer::loadTallWalkingBackSprite() {
	this->walkingBackPlayer[0].x = 1;
	this->walkingBackPlayer[0].y = 48;
	this->walkingBackPlayer[0].w= PLAYER_WIDTH;
	this->walkingBackPlayer[0].h= PLAYER_HEIGHT;

	this->walkingBackPlayer[1].x = 26;
	this->walkingBackPlayer[1].y = 48;
	this->walkingBackPlayer[1].w= PLAYER_WIDTH;
	this->walkingBackPlayer[1].h= PLAYER_HEIGHT;

	this->walkingBackPlayer[2].x = 51;
	this->walkingBackPlayer[2].y = 48;
	this->walkingBackPlayer[2].w= PLAYER_WIDTH;
	this->walkingBackPlayer[2].h= PLAYER_HEIGHT;

	this->walkingBackPlayer[3].x = 76;
	this->walkingBackPlayer[3].y = 48;
	this->walkingBackPlayer[3].w= PLAYER_WIDTH;
	this->walkingBackPlayer[3].h= PLAYER_HEIGHT;

	this->walkingBackPlayer[4].x = 101;
	this->walkingBackPlayer[4].y = 48;
	this->walkingBackPlayer[4].w= PLAYER_WIDTH;
	this->walkingBackPlayer[4].h= PLAYER_HEIGHT;

	this->walkingBackPlayer[5].x = 126;
	this->walkingBackPlayer[5].y = 48;
	this->walkingBackPlayer[5].w= PLAYER_WIDTH;
	this->walkingBackPlayer[5].h= PLAYER_HEIGHT;
}


void TallPlayer::loadTallWalkingLeftSprite() {
	this->walkingLeftPlayer[0].x = 1;
	this->walkingLeftPlayer[0].y = 93;
	this->walkingLeftPlayer[0].w= PLAYER_WIDTH;
	this->walkingLeftPlayer[0].h= PLAYER_HEIGHT;

	this->walkingLeftPlayer[1].x = 23;
	this->walkingLeftPlayer[1].y = 93;
	this->walkingLeftPlayer[1].w= PLAYER_WIDTH;
	this->walkingLeftPlayer[1].h= PLAYER_HEIGHT;

	this->walkingLeftPlayer[2].x = 49;
	this->walkingLeftPlayer[2].y = 93;
	this->walkingLeftPlayer[2].w= PLAYER_WIDTH;
	this->walkingLeftPlayer[2].h= PLAYER_HEIGHT;

	this->walkingLeftPlayer[3].x = 74;
	this->walkingLeftPlayer[3].y = 93;
	this->walkingLeftPlayer[3].w= PLAYER_WIDTH;
	this->walkingLeftPlayer[3].h= PLAYER_HEIGHT;

	this->walkingLeftPlayer[4].x = 99;
	this->walkingLeftPlayer[4].y = 93;
	this->walkingLeftPlayer[4].w= PLAYER_WIDTH;
	this->walkingLeftPlayer[4].h= PLAYER_HEIGHT;
}


void TallPlayer::loadTallWalkingRightSprite() {
	this->walkingRightPlayer[0].x = 1;
	this->walkingRightPlayer[0].y = 138;
	this->walkingRightPlayer[0].w= PLAYER_WIDTH;
	this->walkingRightPlayer[0].h= PLAYER_HEIGHT;

	this->walkingRightPlayer[1].x = 29;
	this->walkingRightPlayer[1].y = 138;
	this->walkingRightPlayer[1].w= PLAYER_WIDTH;
	this->walkingRightPlayer[1].h= PLAYER_HEIGHT;

	this->walkingRightPlayer[2].x = 54;
	this->walkingRightPlayer[2].y = 138;
	this->walkingRightPlayer[2].w= PLAYER_WIDTH;
	this->walkingRightPlayer[2].h= PLAYER_HEIGHT;

	this->walkingRightPlayer[3].x = 78;
	this->walkingRightPlayer[3].y = 138;
	this->walkingRightPlayer[3].w= PLAYER_WIDTH;
	this->walkingRightPlayer[3].h= PLAYER_HEIGHT;

	this->walkingRightPlayer[4].x = 103;
	this->walkingRightPlayer[4].y = 138;
	this->walkingRightPlayer[4].w= PLAYER_WIDTH;
	this->walkingRightPlayer[4].h= PLAYER_HEIGHT;
}
