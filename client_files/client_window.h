#ifndef _CLIENT_WINDOW
#define _CLIENT_WINDOW

#include "SDL2/SDL.h"


class LWindow {
	public:
		//Intializes internals
		LWindow();

		//Creates window
		bool init();

		//Creates renderer from internal window
		SDL_Renderer* createRenderer();

		//Handles window events
		void handleEvent( SDL_Event& e );

		//Deallocates internals
		void free();

		//Window dimensions
		int getWidth();
		int getHeight();

		//Window focii
		bool isMinimized();

	private:
		//Window data
		SDL_Window* mWindow;
        SDL_Renderer* gRenderer;

		//Window dimensions
		int mWidth;
		int mHeight;

		//Window focus
		bool mFullScreen;
		bool mMinimized;
};

#endif
