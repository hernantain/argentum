
#include "client_drawable.h"
#include "client_player_picture.h"


/**
 * CommonClothes
 */


CommonTallClothes::CommonTallClothes(
    SDL_Renderer* gRenderer, 
    int width, 
    int height) : Clothes(width, height) {

    this->load_pictures(gRenderer); 

}


bool CommonTallClothes::load_pictures(SDL_Renderer* gRenderer) {
    if( !this->bodyTexture.loadFromFile( "images/vestimenta_comun_he.png", gRenderer ) ) {
		printf( "Failed to load walking animation texture!\n" );
		return false;
	}

    this->set_tall_sprites();
    return true;
}


CommonShortClothes::CommonShortClothes(
    SDL_Renderer* gRenderer, 
    int width, 
    int height) : Clothes(width, height) {

    this->load_pictures(gRenderer); 

}


bool CommonShortClothes::load_pictures(SDL_Renderer* gRenderer) {
    if( !this->bodyTexture.loadFromFile( "images/vestimenta_comun_eg.png", gRenderer ) ) {
		printf( "Failed to load walking animation texture!\n" );
		return false;
	}

    this->set_short_sprites();
    return true;
}

/**
 * PlateArmor
 */

PlateTallArmor::PlateTallArmor(
    SDL_Renderer* gRenderer, 
    int width, 
    int height) : Clothes(width, height) {

    this->load_pictures(gRenderer); 

}


bool PlateTallArmor::load_pictures(SDL_Renderer* gRenderer) {
    if( !this->bodyTexture.loadFromFile( "images/armadura_placas_he.png", gRenderer ) ) {
		printf( "Failed to load walking animation texture!\n" );
		return false;
	}

    this->set_tall_sprites();
    return true;
}


PlateShortArmor::PlateShortArmor(
    SDL_Renderer* gRenderer, 
    int width, 
    int height) : Clothes(width, height) {

    this->load_pictures(gRenderer); 

}


bool PlateShortArmor::load_pictures(SDL_Renderer* gRenderer) {
    if( !this->bodyTexture.loadFromFile( "images/armadura_placas_eg.png", gRenderer ) ) {
		printf( "Failed to load walking animation texture!\n" );
		return false;
	}

    this->set_short_sprites();
    return true;
}


/**
 * LeatherArmor
 */

LeatherTallArmor::LeatherTallArmor(
    SDL_Renderer* gRenderer, 
    int width, 
    int height) : Clothes(width, height) {

    this->load_pictures(gRenderer); 

}

bool LeatherTallArmor::load_pictures(SDL_Renderer* gRenderer) {
    if( !this->bodyTexture.loadFromFile( "images/armadura_cuero_he.png", gRenderer ) ) {
		printf( "Failed to load walking animation texture!\n" );
		return false;
	}

    this->set_tall_sprites();
    return true;
    
}


LeatherShortArmor::LeatherShortArmor(
    SDL_Renderer* gRenderer, 
    int width, 
    int height) : Clothes(width, height) {

    this->load_pictures(gRenderer); 

}

bool LeatherShortArmor::load_pictures(SDL_Renderer* gRenderer) {
    if( !this->bodyTexture.loadFromFile( "images/armadura_cuero_eg.png", gRenderer ) ) {
		printf( "Failed to load walking animation texture!\n" );
		return false;
	}

    this->set_short_sprites();
    return true;
    
}


/**
 * PlayerPicture
 */

PlayerPicture::PlayerPicture(SDL_Renderer* gRenderer, const char* head_path) {

    this->load_pictures(gRenderer, head_path); 

}



bool PlayerPicture::load_pictures(SDL_Renderer* gRenderer, const char* head_path) {
    if( !this->headTexture.loadFromFile( head_path, gRenderer ) ) {
		printf( "Failed to load walking animation texture!\n" );
		return false;
	}

    this->set_head_sprite();
    return true;
}


void PlayerPicture::set_head_sprite() {
    this->headOrientations[0].x = 1;
	this->headOrientations[0].y = 0;
	this->headOrientations[0].w= 15;
	this->headOrientations[0].h= 20;

	this->headOrientations[1].x = 18;
	this->headOrientations[1].y = 0;
	this->headOrientations[1].w= 15;
	this->headOrientations[1].h= 20;

	this->headOrientations[2].x = 36;
	this->headOrientations[2].y = 0;
	this->headOrientations[2].w= 15;
	this->headOrientations[2].h= 20;

	this->headOrientations[3].x = 52;
	this->headOrientations[3].y = 0;
	this->headOrientations[3].w= 15;
	this->headOrientations[3].h= 20;
}


void PlayerPicture::set_clothes(Clothes* clothes) {
    this->clothes = clothes;
}




void PlayerPicture::render(int &bodyPosX, int &bodyPosY, int &headPosX, int &headPosY, SDL_Renderer* gRenderer, int &orientation, int &frame) {
    
	//Show Character
	if (orientation == RIGHT) {
		SDL_Rect* headClip = &this->headOrientations[1];
		this->headTexture.render(headPosX, headPosY, gRenderer, headClip);
        
	} else if(orientation == LEFT)  {
		SDL_Rect* headClip = &this->headOrientations[2];
		this->headTexture.render(headPosX, headPosY, gRenderer, headClip);
	
    } else if(orientation == UP)  {
		SDL_Rect* headClip = &this->headOrientations[3];
		this->headTexture.render(headPosX, headPosY, gRenderer, headClip);
	
    } else if(orientation == DOWN)  {
		SDL_Rect* headClip = &this->headOrientations[0];
		this->headTexture.render(headPosX, headPosY, gRenderer, headClip);

	} else {
		SDL_Rect* headClip = &this->headOrientations[0];
		this->headTexture.render(headPosX, headPosY, gRenderer, headClip);
    }

    this->clothes->render(bodyPosX, bodyPosY, gRenderer, orientation, frame);
}









/**
 * Clothes
 */


Clothes::Clothes(int width, int height) : width(width), height(height) {}


void Clothes::render(int &bodyPosX, int &bodyPosY, SDL_Renderer* gRenderer, int &orientation, int &frame) {
    // Show Character

    if (orientation == RIGHT) {
		SDL_Rect* currentClip = &this->walkingRightPlayer[ frame / 5 ];
		this->bodyTexture.render(bodyPosX, bodyPosY, gRenderer, currentClip);
        
	} else if(orientation == LEFT)  {
		SDL_Rect *currentClip = &this->walkingLeftPlayer[ frame / 5 ];
		this->bodyTexture.render(bodyPosX, bodyPosY, gRenderer, currentClip);
	
    } else if(orientation == UP)  {
		SDL_Rect *currentClip = &this->walkingBackPlayer[ frame / 5 ];
		this->bodyTexture.render(bodyPosX, bodyPosY, gRenderer, currentClip);
	
    } else if(orientation == DOWN)  {
		SDL_Rect *currentClip = &this->walkingFrontPlayer[ frame / 5 ];
		this->bodyTexture.render(bodyPosX, bodyPosY, gRenderer, currentClip);

	} else {
		SDL_Rect* currentClip = &this->walkingFrontPlayer[0];
		this->bodyTexture.render( bodyPosX, bodyPosY, gRenderer, currentClip);
    }
}





void Clothes::set_short_sprites() {
    this->load_front_walking_sprite();
    this->load_left_walking_sprite();
    this->load_right_walking_sprite();
    this->load_back_walking_sprite();
}




void Clothes::set_tall_sprites() {
    loadTallWalkingFrontSprite();
    loadTallWalkingBackSprite();
    loadTallWalkingLeftSprite();
    loadTallWalkingRightSprite();
}




void Clothes::load_front_walking_sprite() {
	this->walkingFrontPlayer[0].x = 2;
	this->walkingFrontPlayer[0].y = 13;
	this->walkingFrontPlayer[0].w = width;
	this->walkingFrontPlayer[0].h = height;

	this->walkingFrontPlayer[1].x = 27;
	this->walkingFrontPlayer[1].y = 13;
	this->walkingFrontPlayer[1].w = width;
	this->walkingFrontPlayer[1].h = height;

	this->walkingFrontPlayer[2].x = 52;
	this->walkingFrontPlayer[2].y = 13;
	this->walkingFrontPlayer[2].w = width;
	this->walkingFrontPlayer[2].h = height;

	this->walkingFrontPlayer[3].x = 77;
	this->walkingFrontPlayer[3].y = 13;
	this->walkingFrontPlayer[3].w = width;
	this->walkingFrontPlayer[3].h = height;

	this->walkingFrontPlayer[4].x = 102;
	this->walkingFrontPlayer[4].y = 13;
	this->walkingFrontPlayer[4].w = width;
	this->walkingFrontPlayer[4].h = height;

	this->walkingFrontPlayer[5].x = 127;
	this->walkingFrontPlayer[5].y = 13;
	this->walkingFrontPlayer[5].w = width;
	this->walkingFrontPlayer[5].h = height;
}


void Clothes::load_back_walking_sprite() {
	this->walkingBackPlayer[0].x = 2;
	this->walkingBackPlayer[0].y = 58;
	this->walkingBackPlayer[0].w = width;
	this->walkingBackPlayer[0].h = height;

	this->walkingBackPlayer[1].x = 27;
	this->walkingBackPlayer[1].y = 58;
	this->walkingBackPlayer[1].w = width;
	this->walkingBackPlayer[1].h = height;

	this->walkingBackPlayer[2].x = 52;
	this->walkingBackPlayer[2].y = 58;
	this->walkingBackPlayer[2].w = width;
	this->walkingBackPlayer[2].h = height;

	this->walkingBackPlayer[3].x = 77;
	this->walkingBackPlayer[3].y = 58;
	this->walkingBackPlayer[3].w = width;
	this->walkingBackPlayer[3].h = height;

	this->walkingBackPlayer[4].x = 102;
	this->walkingBackPlayer[4].y = 58;
	this->walkingBackPlayer[4].w = width;
	this->walkingBackPlayer[4].h = height;

	this->walkingBackPlayer[5].x = 127;
	this->walkingBackPlayer[5].y = 58;
	this->walkingBackPlayer[5].w = width;
	this->walkingBackPlayer[5].h = height;
}


void Clothes::load_left_walking_sprite() {
	this->walkingLeftPlayer[0].x = 2;
	this->walkingLeftPlayer[0].y = 103;
	this->walkingLeftPlayer[0].w = width;
	this->walkingLeftPlayer[0].h = height;

	this->walkingLeftPlayer[1].x = 27;
	this->walkingLeftPlayer[1].y = 103;
	this->walkingLeftPlayer[1].w = width;
	this->walkingLeftPlayer[1].h = height;

	this->walkingLeftPlayer[2].x = 52;
	this->walkingLeftPlayer[2].y = 103;
	this->walkingLeftPlayer[2].w = width;
	this->walkingLeftPlayer[2].h = height;

	this->walkingLeftPlayer[3].x = 77;
	this->walkingLeftPlayer[3].y = 103;
	this->walkingLeftPlayer[3].w = width;
	this->walkingLeftPlayer[3].h = height;

	this->walkingLeftPlayer[4].x = 102;
	this->walkingLeftPlayer[4].y = 103;
	this->walkingLeftPlayer[4].w = width;
	this->walkingLeftPlayer[4].h = height;
}


void Clothes::load_right_walking_sprite() {
	this->walkingRightPlayer[0].x = 2;
	this->walkingRightPlayer[0].y = 148;
	this->walkingRightPlayer[0].w = width;
	this->walkingRightPlayer[0].h = height;

	this->walkingRightPlayer[1].x = 27;
	this->walkingRightPlayer[1].y = 148;
	this->walkingRightPlayer[1].w = width;
	this->walkingRightPlayer[1].h = height;

	this->walkingRightPlayer[2].x = 52;
	this->walkingRightPlayer[2].y = 148;
	this->walkingRightPlayer[2].w = width;
	this->walkingRightPlayer[2].h = height;

	this->walkingRightPlayer[3].x = 77;
	this->walkingRightPlayer[3].y = 148;
	this->walkingRightPlayer[3].w = width;
	this->walkingRightPlayer[3].h = height;

	this->walkingRightPlayer[4].x = 102;
	this->walkingRightPlayer[4].y = 148;
	this->walkingRightPlayer[4].w = width;
	this->walkingRightPlayer[4].h = height;
}


void Clothes::loadTallWalkingFrontSprite() {
	this->walkingFrontPlayer[0].x = 1;
	this->walkingFrontPlayer[0].y = 2;
	this->walkingFrontPlayer[0].w  = width;
	this->walkingFrontPlayer[0].h  = height;

	this->walkingFrontPlayer[1].x = 26;
	this->walkingFrontPlayer[1].y = 2;
	this->walkingFrontPlayer[1].w  = width;
	this->walkingFrontPlayer[1].h  = height;

	this->walkingFrontPlayer[2].x = 51;
	this->walkingFrontPlayer[2].y = 2;
	this->walkingFrontPlayer[2].w  = width;
	this->walkingFrontPlayer[2].h  = height;

	this->walkingFrontPlayer[3].x = 76;
	this->walkingFrontPlayer[3].y = 2;
	this->walkingFrontPlayer[3].w  = width;
	this->walkingFrontPlayer[3].h  = height;

	this->walkingFrontPlayer[4].x = 101;
	this->walkingFrontPlayer[4].y = 2;
	this->walkingFrontPlayer[4].w  = width;
	this->walkingFrontPlayer[4].h  = height;

	this->walkingFrontPlayer[5].x = 126;
	this->walkingFrontPlayer[5].y = 2;
	this->walkingFrontPlayer[5].w  = width;
	this->walkingFrontPlayer[5].h  = height;
}



void Clothes::loadTallWalkingBackSprite() {
	this->walkingBackPlayer[0].x = 1;
	this->walkingBackPlayer[0].y = 48;
	this->walkingBackPlayer[0].w  = width;
	this->walkingBackPlayer[0].h  = height;

	this->walkingBackPlayer[1].x = 26;
	this->walkingBackPlayer[1].y = 48;
	this->walkingBackPlayer[1].w  = width;
	this->walkingBackPlayer[1].h  = height;

	this->walkingBackPlayer[2].x = 51;
	this->walkingBackPlayer[2].y = 48;
	this->walkingBackPlayer[2].w  = width;
	this->walkingBackPlayer[2].h  = height;

	this->walkingBackPlayer[3].x = 76;
	this->walkingBackPlayer[3].y = 48;
	this->walkingBackPlayer[3].w  = width;
	this->walkingBackPlayer[3].h  = height;

	this->walkingBackPlayer[4].x = 101;
	this->walkingBackPlayer[4].y = 48;
	this->walkingBackPlayer[4].w  = width;
	this->walkingBackPlayer[4].h  = height;

	this->walkingBackPlayer[5].x = 126;
	this->walkingBackPlayer[5].y = 48;
	this->walkingBackPlayer[5].w  = width;
	this->walkingBackPlayer[5].h  = height;
}


void Clothes::loadTallWalkingLeftSprite() {
	this->walkingLeftPlayer[0].x = 1;
	this->walkingLeftPlayer[0].y = 93;
	this->walkingLeftPlayer[0].w  = width;
	this->walkingLeftPlayer[0].h  = height;

	this->walkingLeftPlayer[1].x = 23;
	this->walkingLeftPlayer[1].y = 93;
	this->walkingLeftPlayer[1].w  = width;
	this->walkingLeftPlayer[1].h  = height;

	this->walkingLeftPlayer[2].x = 49;
	this->walkingLeftPlayer[2].y = 93;
	this->walkingLeftPlayer[2].w  = width;
	this->walkingLeftPlayer[2].h  = height;

	this->walkingLeftPlayer[3].x = 74;
	this->walkingLeftPlayer[3].y = 93;
	this->walkingLeftPlayer[3].w  = width;
	this->walkingLeftPlayer[3].h  = height;

	this->walkingLeftPlayer[4].x = 99;
	this->walkingLeftPlayer[4].y = 93;
	this->walkingLeftPlayer[4].w  = width;
	this->walkingLeftPlayer[4].h  = height;
}


void Clothes::loadTallWalkingRightSprite() {
	this->walkingRightPlayer[0].x = 1;
	this->walkingRightPlayer[0].y = 138;
	this->walkingRightPlayer[0].w  = width;
	this->walkingRightPlayer[0].h  = height;

	this->walkingRightPlayer[1].x = 29;
	this->walkingRightPlayer[1].y = 138;
	this->walkingRightPlayer[1].w  = width;
	this->walkingRightPlayer[1].h  = height;

	this->walkingRightPlayer[2].x = 54;
	this->walkingRightPlayer[2].y = 138;
	this->walkingRightPlayer[2].w  = width;
	this->walkingRightPlayer[2].h  = height;

	this->walkingRightPlayer[3].x = 78;
	this->walkingRightPlayer[3].y = 138;
	this->walkingRightPlayer[3].w  = width;
	this->walkingRightPlayer[3].h  = height;

	this->walkingRightPlayer[4].x = 103;
	this->walkingRightPlayer[4].y = 138;
	this->walkingRightPlayer[4].w  = width;
	this->walkingRightPlayer[4].h  = height;
}









/**
 * EquippedPlayer
 */



EquippedPlayer::EquippedPlayer(PlayerPicture* player) {
	this->player = player;
	this->helmet = NULL;
}



void EquippedPlayer::setHelmet(Helmet* helmet) {
	this->helmet = helmet;
}


void EquippedPlayer::render(
	int &bodyPosX, 
	int &bodyPosY,int &headPosX, int &headPosY, SDL_Renderer* gRenderer, int &orientation, int &frame) {

	player->render(bodyPosX, bodyPosY, headPosX, headPosY, gRenderer, orientation, frame);
	
	if (helmet != NULL)
		helmet->render(headPosX, headPosY, gRenderer, orientation, frame);		
			
}




/**
 * Helmet
 */


Helmet::Helmet(int offset) : offset(offset) {}


void Helmet::render(int &headPosX, int &headPosY, SDL_Renderer* gRenderer, int &orientation, int &frame) {
	//Show Character
	if (orientation == RIGHT) {
		SDL_Rect* headClip = &this->helmetOrientation[1];
		this->helmetTexture.render(headPosX-1, headPosY+offset, gRenderer, headClip);
        
	} else if(orientation == LEFT)  {
		SDL_Rect* headClip = &this->helmetOrientation[2];
		this->helmetTexture.render(headPosX-1, headPosY+offset, gRenderer, headClip);
	
    } else if(orientation == UP)  {
		SDL_Rect* headClip = &this->helmetOrientation[3];
		this->helmetTexture.render(headPosX-1, headPosY+offset, gRenderer, headClip);
	
    } else if(orientation == DOWN)  {
		SDL_Rect* headClip = &this->helmetOrientation[0];
		this->helmetTexture.render(headPosX-1, headPosY+offset, gRenderer, headClip);

	} else {
		SDL_Rect* headClip = &this->helmetOrientation[0];
		this->helmetTexture.render(headPosX-1, headPosY+offset, gRenderer, headClip);
    }
}



/**
 * Hood
 * 
 */


Hood::Hood(SDL_Renderer* gRenderer) : Helmet(-2) {

    this->load_pictures(gRenderer); 

}


bool Hood::load_pictures(SDL_Renderer* gRenderer) {
    if( !this->helmetTexture.loadFromFile( "images/capucha.png", gRenderer ) ) {
		printf( "Failed to load walking animation texture!\n" );
		return false;
	}

    this->set_sprites();
    return true;
}


void Hood::set_sprites() {
	this->helmetOrientation[0].x = 0;
	this->helmetOrientation[0].y = 0;
	this->helmetOrientation[0].h = 17;
	this->helmetOrientation[0].w = 17;

	this->helmetOrientation[1].x = 17;
	this->helmetOrientation[1].y = 0;
	this->helmetOrientation[1].h = 17;
	this->helmetOrientation[1].w = 17;

	this->helmetOrientation[2].x = 35;
	this->helmetOrientation[2].y = 0;
	this->helmetOrientation[2].h = 17;
	this->helmetOrientation[2].w = 17;

	this->helmetOrientation[3].x = 51;
	this->helmetOrientation[3].y = 0;
	this->helmetOrientation[3].h = 17;
	this->helmetOrientation[3].w = 17;
}



/**
 * Hood
 * 
 */


IronHelmet::IronHelmet(SDL_Renderer* gRenderer) : Helmet(-2) {

    this->load_pictures(gRenderer); 

}


bool IronHelmet::load_pictures(SDL_Renderer* gRenderer) {
    if( !this->helmetTexture.loadFromFile( "images/casco_hierro.png", gRenderer ) ) {
		printf( "Failed to load walking animation texture!\n" );
		return false;
	}

    this->set_sprites();
    return true;
}


void IronHelmet::set_sprites() {
	this->helmetOrientation[0].x = 0;
	this->helmetOrientation[0].y = 0;
	this->helmetOrientation[0].h = 17;
	this->helmetOrientation[0].w = 17;

	this->helmetOrientation[1].x = 17;
	this->helmetOrientation[1].y = 0;
	this->helmetOrientation[1].h = 17;
	this->helmetOrientation[1].w = 17;

	this->helmetOrientation[2].x = 35;
	this->helmetOrientation[2].y = 0;
	this->helmetOrientation[2].h = 17;
	this->helmetOrientation[2].w = 17;

	this->helmetOrientation[3].x = 51;
	this->helmetOrientation[3].y = 0;
	this->helmetOrientation[3].h = 17;
	this->helmetOrientation[3].w = 17;
}








/**
 * MagicHat
 * 
 */


MagicHat::MagicHat(SDL_Renderer* gRenderer) : Helmet(-12) {

    this->load_pictures(gRenderer); 

}


bool MagicHat::load_pictures(SDL_Renderer* gRenderer) {
    if( !this->helmetTexture.loadFromFile( "images/sombrero_magico.png", gRenderer ) ) {
		printf( "Failed to load walking animation texture!\n" );
		return false;
	}

    this->set_sprites();
    return true;
}


void MagicHat::set_sprites() {
	this->helmetOrientation[0].x = 0;
	this->helmetOrientation[0].y = 2;
	this->helmetOrientation[0].h = 17;
	this->helmetOrientation[0].w = 18;

	this->helmetOrientation[1].x = 17;
	this->helmetOrientation[1].y = 0;
	this->helmetOrientation[1].h = 17;
	this->helmetOrientation[1].w = 18;

	this->helmetOrientation[2].x = 34;
	this->helmetOrientation[2].y = 2;
	this->helmetOrientation[2].h = 17;
	this->helmetOrientation[2].w = 18;

	this->helmetOrientation[3].x = 51;
	this->helmetOrientation[3].y = 2;
	this->helmetOrientation[3].h = 17;
	this->helmetOrientation[3].w = 18;
}
