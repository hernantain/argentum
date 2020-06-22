

#include "client_drawable.h"
#include "client_player_picture.h"

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
    int headPosY) : Drawable(10),
                    bodyPosX(bodyPosX), 
                    bodyPosY(bodyPosY),
                    headPosX(headPosX),
                    headPosY(headPosY) {}


int Player::getPosX() const {
	return this->bodyPosX;
}
    
int Player::getPosY() const {
	return this->bodyPosY;
}
    
void Player::set_camera(SDL_Rect &camera) {

	camera.x = ( this->bodyPosX +  18 ) - 640 / 2;
	camera.y = ( this->bodyPosY + 18 ) - 480 / 2;

	//Keep the camera in bounds
	if( camera.x < 0 )
		camera.x = 0;
	
	if( camera.y < 0 ) 
		camera.y = 0;
	
	if( camera.x > 3200 - camera.w )
		camera.x = 3200 - camera.w;
	
	if( camera.y > 3200 - camera.h )
		camera.y = 3200 - camera.h; 
}


TallPlayer::TallPlayer(SDL_Renderer* gRenderer, const char* head_path) : Player(25, 25, 29, 15) {
	this->load_clothes(gRenderer);
	this->load_helmets(gRenderer);
	this->playerPicture = new PlayerPicture(gRenderer, head_path);
	this->playerPicture->set_clothes(this->clothes[0]);
	this->equippedPlayer = new EquippedPlayer(playerPicture);
}



void TallPlayer::load_clothes(SDL_Renderer* gRenderer) {
	Clothes* common = new CommonTallClothes(gRenderer, PLAYER_WIDTH, PLAYER_HEIGHT);
	Clothes* plateArmor = new PlateTallArmor(gRenderer, PLAYER_WIDTH, PLAYER_HEIGHT);
	Clothes* leatherArmor = new LeatherTallArmor(gRenderer, PLAYER_WIDTH, PLAYER_HEIGHT);
	this->clothes.push_back(common);
	this->clothes.push_back(plateArmor);
	this->clothes.push_back(leatherArmor);
}




void Player::load_helmets(SDL_Renderer* gRenderer) {
	Helmet* hood = new Hood(gRenderer);
	Helmet* ironHelmet = new IronHelmet(gRenderer);
	Helmet* magicHat = new MagicHat(gRenderer);
	this->helmets.push_back(hood);
	this->helmets.push_back(ironHelmet);
	this->helmets.push_back(magicHat);
}






ShortPlayer::ShortPlayer(SDL_Renderer* gRenderer, const char* head_path) : Player(25, 25, 28, 13) {
	this->load_clothes(gRenderer);
	this->load_helmets(gRenderer);
	this->playerPicture = new PlayerPicture(gRenderer, head_path);
	this->playerPicture->set_clothes(this->clothes[0]);
	this->equippedPlayer = new EquippedPlayer(playerPicture);
}


void ShortPlayer::load_clothes(SDL_Renderer* gRenderer) {
	Clothes* common = new CommonShortClothes(gRenderer, PLAYER_WIDTH, PLAYER_HEIGHT);
	Clothes* plateArmor = new PlateShortArmor(gRenderer, PLAYER_WIDTH, PLAYER_HEIGHT);
	Clothes* leatherArmor = new LeatherShortArmor(gRenderer, PLAYER_WIDTH, PLAYER_HEIGHT);
	this->clothes.push_back(common);
	this->clothes.push_back(plateArmor);
	this->clothes.push_back(leatherArmor);
}


Human::Human(SDL_Renderer* gRenderer) : TallPlayer(gRenderer, "images/humano.png") {}

Elf::Elf(SDL_Renderer* gRenderer) : TallPlayer(gRenderer, "images/elfo.png") {}

Gnome::Gnome(SDL_Renderer* gRenderer) : ShortPlayer(gRenderer, "images/gnomo.png") {}

Dwarf::Dwarf(SDL_Renderer* gRenderer) : ShortPlayer(gRenderer, "images/enano.png") {}




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


			/* A CAMBIAR */
			case SDLK_m:
				this->playerPicture->set_clothes(this->clothes[1]);
				break;

			case SDLK_n:
				this->playerPicture->set_clothes(this->clothes[2]);
				break;

			case SDLK_b:
				this->playerPicture->set_clothes(this->clothes[0]);
				break;

			case SDLK_h:
				this->equippedPlayer->setHelmet(this->helmets[0]);
				break;

			case SDLK_j:
				this->equippedPlayer->setHelmet(this->helmets[1]);
				break;

			case SDLK_k:
				this->equippedPlayer->setHelmet(this->helmets[2]);
				break;

			case SDLK_l:
				this->equippedPlayer->setHelmet(NULL);
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



void Player::render(SDL_Renderer* gRenderer, int camPosX, int camPosY) {
	std::unique_lock<std::mutex> lock(this->m);
	int bodyCenteredX = this->bodyPosX - camPosX;
	int bodyCenteredY = this->bodyPosY - camPosY;
	int headCenteredX = this->headPosX - camPosX;
	int headCenteredY = this->headPosY - camPosY;
	equippedPlayer->render(
		bodyCenteredX, 
		bodyCenteredY, 
		headCenteredX, 
		headCenteredY, 
		gRenderer, 
		this->orientation, 
		this->frame);

	this->frame++;

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



// void TallPlayer::loadBaculoSprites() {
//     this->baculoSprites[0].x = 0;
//     this->baculoSprites[0].y = 0;
//     this->baculoSprites[0].w = 23;
//     this->baculoSprites[0].h = 46;

//     this->baculoSprites[1].x = 23;
//     this->baculoSprites[1].y = 0;
//     this->baculoSprites[1].w = 23;
//     this->baculoSprites[1].h = 46;

//     this->baculoSprites[2].x = 47;
//     this->baculoSprites[2].y = 0;
//     this->baculoSprites[2].w = 23;
//     this->baculoSprites[2].h = 46;

//     this->baculoSprites[3].x = 90;
//     this->baculoSprites[3].y = 0;
//     this->baculoSprites[3].w = 23;
//     this->baculoSprites[3].h = 46;

//     this->baculoSprites[4].x = 114;
//     this->baculoSprites[4].y = 0;
//     this->baculoSprites[4].w = 23;
//     this->baculoSprites[4].h = 46;

//     this->baculoSprites[5].x = 0;
//     this->baculoSprites[5].y = 0;
//     this->baculoSprites[5].w = 23;
//     this->baculoSprites[5].h = 46;
// }