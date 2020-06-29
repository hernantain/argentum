#ifndef _CLIENT_WINDOW
#define _CLIENT_WINDOW

#include "SDL2/SDL.h"


class LWindow {
	public:
		LWindow();

		bool init();

		SDL_Renderer* createRenderer();

		void handleEvent( SDL_Event& e );

		void free();

		int getWidth();
		int getHeight();

		bool isMinimized();

	private:
		SDL_Window* mWindow;
        SDL_Renderer* gRenderer;

		int mWidth;
		int mHeight;

		bool mFullScreen;
		bool mMinimized;
};

#endif
