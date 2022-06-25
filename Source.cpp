#include "SDLS.h"
using namespace std;
enum { BACKGROUND = 0, DOODLE, PLATFORM, RIGHT, PNGEGG, LEFT, GVR, shtg};
Uint32 start;
int sizeX = 400, sizeY = 533;
const int FPS = 60;
const int ANIMATION_DELAY = 1000;
SDL_Rect boardRect = { 0, 0, sizeX, sizeY };
SDL_Window* win;
SDL_Renderer* rer;
const int platformsCnt = 10;
//int showmenu(SDL_Surface* screen, TTF_Font* font)
//{
//
//	Uint32 time;
//	int x, y;
//	const int NUMMENU = 2;
//	const char* labels[NUMMENU] = { "Continue","Exit" };
//	SDL_Surface* menus[NUMMENU];
//
//	bool selected[NUMMENU] = { 0,0 };
//	SDL_Color color[2] = { {255,255,255},{255,0,0} };
//
//	menus[0] = TTF_RenderText_Solid(font, labels[0], color[0]);
//	menus[1] = TTF_RenderText_Solid(font, labels[1], color[0]);
//
//	SDL_Rect pos[NUMMENU];
//	pos[0].x = screen->clip_rect.w / 2 - menus[0]->clip_rect.w / 2;
//	pos[0].y = screen->clip_rect.h / 2 - menus[0]->clip_rect.h;
//	pos[1].x = screen->clip_rect.w / 2 - menus[0]->clip_rect.w / 2;
//	pos[1].y = screen->clip_rect.h / 2 - menus[0]->clip_rect.h;
//
//	SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
//
//	SDL_Event event;
//	while (true)
//	{
//		time = SDL_GetTicks();
//		while (SDL_PollEvent(&event))
//		{
//			switch (event.type)
//			{
//			case SDL_QUIT:
//				for (int i = 0; i < NUMMENU; i++)
//				{
//					SDL_FreeSurface(menus[i]);
//				}
//				return 1;
//
//			case SDL_MOUSEMOTION:
//				x = event.motion.x;
//				y = event.motion.y;
//				for (int i = 0; i < NUMMENU; i++)
//				{
//					if (x >= pos[1].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h)
//					{
//						if (!selected[i])
//						{
//							selected[i] = 1;
//							SDL_FreeSurface(menus[i]);
//							menus[i] = TTF_RenderText_Solid(font, labels[i], color[1]);
//
//						}
//					}
//
//					else
//					{
//						if (selected[i])
//						{
//							selected[i] = 0;
//							SDL_FreeSurface(menus[i]);
//							menus[i] = TTF_RenderText_Solid(font, labels[i], color[0]);
//						}
//
//					}
//
//				}
//				break;
//
//			case SDL_MOUSEBUTTONDOWN:
//				x = event.button.x;
//				y = event.button.y;
//
//				for (int i = 0; i < NUMMENU; i++)
//				{
//					if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h)
//					{
//						for (int j = 0; j < NUMMENU; j++)
//							SDL_FreeSurface(menus[j]);
//
//						return i;
//					}
//				}
//				break;
//
//			case SDL_KEYDOWN:
//				switch (event.key.keysym.sym)
//				{
//				case SDLK_ESCAPE:
//					for (int i = 0; i < NUMMENU; i++)
//						SDL_FreeSurface(menus[i]);
//
//					return 0;
//				}
//
//			}
//
//		}
//
//		for (int i = 0; i < NUMMENU; i++)
//			SDL_BlitSurface(menus[i], NULL, screen, &pos[i]);
//
//
//		SDL_Flip(screen);
//
//	}
//
//}




int main(int argc, char** argv) 
{
	bool stop = false;
	bool perm = false;
	bool shoot = false;
	init(win, rer, sizeX, sizeY);
	SDL_Surface* screenSurface = SDL_GetWindowSurface(win);
	vector<string> Bitmaps;
	Bitmaps.push_back("background.png");
	Bitmaps.push_back("img/doodle.png");
	Bitmaps.push_back("img/normal_platform.png");
	Bitmaps.push_back("img/right.png");
	Bitmaps.push_back("img/pngegg.png");
	Bitmaps.push_back("img/left.png");
	Bitmaps.push_back("img/gameover.png");
	Bitmaps.push_back("img/shooting.png");
	vector<SDL_Texture*> Textures;
	for (auto bitmap : Bitmaps) {
		Textures.push_back(IMG_LoadTexture(rer, bitmap.c_str()));
		if (Textures.back() == NULL) {
			cout << bitmap.c_str() << " SDL_CreateTextureFromSurface error\n";
		}
		else
			cout << bitmap.c_str() << " SDL_CreateTextureFromSurface OK\n";
	}
	SDL_Point plat[platformsCnt];
	for (int i = 0; i < platformsCnt; i++)
	{
		plat[i].x = rand() % sizeX;
		plat[i].y = rand() % sizeY;
	}
	double x = 100, y = 100;
	int h = 200;
	double dx = 0, dy = 0;
	SDL_Rect doodleRect;
	while (1) {
		start = SDL_GetTicks();
		SDL_Event e;
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				break;
			}
			if (e.type == SDL_WINDOWEVENT)
			{
				if (e.window.type == SDL_WINDOWEVENT_RESIZED)
				{
					sizeX = e.window.data1;
					sizeY = e.window.data2;
				}
			}
			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_LEFT:
					shoot = false;
					x -= 10.27;
					perm = false;
					break;
				case SDLK_RIGHT:
					shoot = false;
					x += 10.27;
					perm = true;
					break;
				case SDLK_UP:
					shoot = true;
					break;
				case SDLK_DOWN:
					break;
				default:
					cout << "Key not supported" << endl;
					break;
				}
			}
		}
		if (x < 0 || x> sizeX || y > sizeY - 1.0)
		{
				stop = true;
				break;
		}
		SDL_RenderClear(rer);
		if (shoot)
		{
			SDL_RenderClear(rer);
			SDL_RenderCopy(rer, Textures[shtg], NULL, &doodleRect);
		}
		SDL_RenderCopy(rer, Textures[BACKGROUND], NULL, &boardRect);

		for (int i = 0; i < platformsCnt; i++) {
			SDL_Rect platRect = { plat[i].x, plat[i].y, 68, 16 };
			SDL_RenderCopy(rer, Textures[PLATFORM], NULL, &platRect);
		}

		doodleRect = { (int)x, (int)y, 80, 80 };
		if (SDL_GetTicks() < 10000)
		{
			if (shoot)
			{
				
				SDL_RenderCopy(rer, Textures[shtg], NULL, &doodleRect);
			}
			if (!perm)
				SDL_RenderCopy(rer, Textures[LEFT], NULL, &doodleRect);
			else
				SDL_RenderCopy(rer, Textures[RIGHT], NULL, &doodleRect);
			
		}
		else
		{
			if (!perm)
				SDL_RenderCopy(rer, Textures[DOODLE], NULL, &doodleRect);
			else
				SDL_RenderCopy(rer, Textures[PNGEGG], NULL, &doodleRect);
			
		}
		SDL_RenderPresent(rer);
		dy += 0.2;
		y += dy;

		if (y > sizeY)
			dy = -10;
		if (y < h)
			for (int i = 0; i < platformsCnt; i++) {
				y = h;
				plat[i].y = plat[i].y - dy;

				if (plat[i].y > sizeY) {
					plat[i].y = 0;
					plat[i].x = rand() % sizeX;
				}
			}

		for (int i = 0; i < platformsCnt; i++)
			if ((x + 50 > plat[i].x) && (x + 20 < plat[i].x + 68.0) && (y + 70 > plat[i].y) && (y + 70 < plat[i].y + 14.0) && (dy > 0))
				dy = -10;
		cout << SDL_GetTicks() << endl;
		if (ANIMATION_DELAY / FPS > SDL_GetTicks() - start)
			SDL_Delay(ANIMATION_DELAY / FPS - (SDL_GetTicks() - start));
	}
	if (stop)
	gameovr(Textures, stop, rer, boardRect);
	
	for (auto texture : Textures)
		SDL_DestroyTexture(texture);
	deinit(win, rer);
	
	return 0;
}