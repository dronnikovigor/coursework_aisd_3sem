#ifndef _SDL_FUNC_H
#define _SDL_FUNC_H
 
using namespace std;
 
void logSDLError(ostream &os, const string &msg); //Логирование ошибок SDL
SDL_Texture* loadTexture(const string &file, SDL_Renderer *ren); //Загрузка BMP для отображения на экране
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y); //Отрисовка SDL_Texture с помощью SDL_Renderer на x, y, с заданной шириной и высотой
void renderBackground(SDL_Texture *background, SDL_Renderer *renderer); //Отрисовка фона
void renderText(const char *file, int size, int red, int green, int blue, SDL_Renderer *renderer, int x, int y, const char *textOut); //Отрисовка текста
void outputAVL(node* avl, SDL_Texture *root, SDL_Texture *list, SDL_Renderer *renderer, int x_pred, int x, int y); //Отрисовка АВЛ-дерева на экран
 
#endif
