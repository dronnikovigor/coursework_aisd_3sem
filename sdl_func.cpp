#include <string>
#include <iostream>
#include <fstream>
#include "SDL.h"
#include "SDL_ttf.h"
#include "avl.h"
#include "sdl_func.h"
 
using namespace std;
 
const int SCREEN_WIDTH = 1280; //ширина окна
const int SCREEN_HEIGHT = 640; //высота окна
 
void logSDLError(ostream &os, const string &msg) {
	os << msg << " error: " << SDL_GetError() << endl;
}
 
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren) {
	SDL_Texture *texture = nullptr;
	//Загрузка изображения
	SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());
	//Если загрузка успешна - конвертация в текстуру
	if (loadedImage != nullptr) {
		texture = SDL_CreateTextureFromSurface(ren, loadedImage);
		SDL_FreeSurface(loadedImage);
		//Проверка на успешную конвертацию
		if (texture == nullptr) {
			logSDLError(cout, "CreateTextureFromSurface");
		}
	}
	else {
		logSDLError(cout, "LoadBMP");
	}
	return texture;
}
 
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y) {
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(ren, tex, NULL, &dst);
}
 
void renderBackground(SDL_Texture *background, SDL_Renderer *renderer) {
	//Отрисовка фона
	for (int j = 0; j < SCREEN_WIDTH / 20; j++) {
		renderTexture(background, renderer, j * 20, 0);
	}
	SDL_RenderPresent(renderer); //Обновление экрана
}
 
void renderText(const char *file, int size, int red, int green, int blue, SDL_Renderer *renderer, int x, int y, const char *textOut) {
	//Инициализация SDL_ttf
	if (TTF_Init() != 0) {
		cerr << "TTF_Init() Failed: " << TTF_GetError() << endl;
		SDL_Quit();
		exit(1);
	}
	//Загрузка шрифта
	TTF_Font *font;
	font = TTF_OpenFont(file, size);
	if (font == NULL) {
		cerr << "TTF_OpenFont() Failed: " << TTF_GetError() << endl;
		TTF_Quit();
		SDL_Quit();
		exit(1);
	}
	SDL_Color text_color = { red , green, blue };
	SDL_Surface *text = TTF_RenderText_Solid(font, textOut, text_color);
	SDL_Texture* text_Texture = SDL_CreateTextureFromSurface(renderer, text);
	renderTexture(text_Texture, renderer, x, y);
	SDL_RenderPresent(renderer); //Обновление экрана
	TTF_Quit();
}
 
void outputAVL(node* avl, SDL_Texture *root, SDL_Texture *list, SDL_Renderer *renderer, int x_pred, int x, int y) {
	if (avl != NULL) {
		int iW, iH;
		if (avl->left == NULL && avl->right == NULL) {
			SDL_QueryTexture(list, NULL, NULL, &iW, &iH);
			renderTexture(list, renderer, x, y);
		}
		else {
			SDL_QueryTexture(root, NULL, NULL, &iW, &iH);
			renderTexture(root, renderer, x, y);
		}
		string str = to_string(avl->key);
		renderText("res/Arial.ttf", 30, 255, 0, 0, renderer, x + 20, y - 20, str.c_str()); //Вывод текста на экран
 
		SDL_Delay(150); //Пауза
 
		outputAVL(avl->left, root, list, renderer, x, x - abs(x - x_pred) / 2, y + 50);
		outputAVL(avl->right, root, list, renderer, x, x + abs(x - x_pred) / 2, y + 50);
	}
}
