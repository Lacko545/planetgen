#ifndef PLANETARIUM_H
#define PLANETARIUM_H

int init(SDL_Window **a, SDL_Surface **b);

int main();

SDL_Surface* load_media(char *path);

int close();

#endif
