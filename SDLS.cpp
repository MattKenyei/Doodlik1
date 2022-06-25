#include "SDLS.h"
void init(SDL_Window* &win, SDL_Renderer* &rer, int sizeX, int sizeY)
{
	cout << "SDL_Init\n";
	SDL_Init(SDL_INIT_EVERYTHING);
	win = SDL_CreateWindow("Doodle Jump", 100, 100, sizeX, sizeY, 0);
	if (win == NULL) 
		cout << "SDL_CreateWindow error\n";
	
	rer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (rer == NULL) 
		cout << "SDL_CreateRenderer error\n";
	

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		cout << "SDL_image could not initialize! SDL_image Error:" << IMG_GetError() << endl;
	}
}
void deinit(SDL_Window* win, SDL_Renderer* rer)
{
	IMG_Quit();
	SDL_DestroyRenderer(rer);
	SDL_DestroyWindow(win);
	SDL_Quit();
	cout << "SDL_Quit\n";
}
void gameovr(vector<SDL_Texture*> Textures, bool& stop, SDL_Renderer* &rer, SDL_Rect boardRect)
{
	SDL_Event e;

	if (SDL_PollEvent(&e))
		if (e.type == SDL_QUIT)
			return;		
	SDL_RenderClear(rer);
	SDL_RenderPresent(rer);
	SDL_Delay(1000);
	SDL_RenderClear(rer);
	SDL_RenderCopy(rer, Textures[6], NULL, &boardRect);
	SDL_RenderPresent(rer);
	SDL_Delay(15000);
			
	
}