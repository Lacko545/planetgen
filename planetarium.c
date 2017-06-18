#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include "perlin.h"

int init(SDL_Window **a, SDL_Surface **b)
{
        int success=1;

        if(SDL_Init(SDL_INIT_VIDEO)<0){
                printf("Error initializing video. SDL_Error: %s\n", SDL_GetError());
                success=0;
        }
        else{
                *a= SDL_CreateWindow(   "Planetarium",
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED,
                                        640,480,
                                        SDL_WINDOW_SHOWN
                                        );
                if (*a==NULL){
                        printf("Can't create window. SDL_Error: %s\n", SDL_GetError() );
                        success=0;
                } else {
                        *b=SDL_GetWindowSurface(*a);
                }
        }

        return success;
}


SDL_Surface * load_surface(const char *path)
{
        printf("%s\n", path);
        SDL_Surface * a = NULL;
        a=SDL_LoadBMP(path);
        if(a==NULL){
                printf("Error loading image %s.\n SDL_Error: %s\n",path , SDL_GetError() );
                return NULL;
        }
        return a;
}

SDL_Texture* load_texture(char * path)
{
        SDL_Texture* texture = NULL;
        SDL_Surface* tmp = load_surface(path);

        if (tmp!=NULL){

        }

        SDL_FreeSurface(tmp);
        return NULL;
}



int main(int argc, char *argv[])
{
        SDL_Window  *main_window = NULL;
        SDL_Surface *screen_surface = NULL;
        SDL_Surface *image = NULL;
        SDL_Renderer *renderer = NULL;
        init(&main_window,&screen_surface);
        image=load_surface("sship3.bmp");
        if (image!=NULL){
                printf("ayylmao\n");
                SDL_BlitSurface(image,NULL,screen_surface,NULL);
                SDL_UpdateWindowSurface(main_window);
        }

        SDL_Delay(2000);
        SDL_FreeSurface(screen_surface);
        SDL_FreeSurface(image);
        SDL_DestroyWindow(main_window);
        main_window=NULL;
        screen_surface=NULL;
        image=NULL;
        SDL_Quit();
        return 0;
}
