/* 
 * File:   main.c
 * Author: raichu
 *
 * Created on January 26, 2012, 10:38 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "headers/HD.h"
/*
 * 
 */
    SDL_Event event;
  //  SDL_Surface *menu = NULL;

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
    //Make a temporary rectangle to hold the offsets
    SDL_Rect offset;
    //Give the offsets to the rectangle
    offset.x = x;
    offset.y = y;
    //Blit the surface
    SDL_BlitSurface( source, NULL, destination, &offset );
}

int main(int argc, char** argv) {

    int e;
//        e = HawaiianEarring();
//	e = init();
  if ( SDL_Init(SDL_INIT_VIDEO) < 0 )
  {
    fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
    exit(1);
  }

  // Register SDL_Quit to be called at exit; makes sure things are
  // cleaned up when we quit.
  atexit(SDL_Quit);

  // Attempt to create a 640x480 window with 32bit pixels.
    SDL_putenv("SDL_VIDEO_CENTERED=center");
    screen = SDL_SetVideoMode(1024, 868, 32, SDL_SWSURFACE);

    menu = SDL_LoadBMP("/home/raichu/NetBeansProjects5/11.fractals/images/menu.bmp");
	SDL_Rect offset;
	offset.x = 0;
	offset.y = HEIGHT-200;
    SDL_BlitSurface(menu, NULL, screen, &offset);

    SDL_WM_SetCaption( "Afractal", NULL );
    apply_surface(1024, 200, menu, screen );
  // If we fail, return error.
  if ( screen == NULL )
  {
    fprintf(stderr, "Unable to set 640x480 video: %s\n", SDL_GetError());
    exit(1);
  }
        SDL_Flip(screen);

int quit=0;
   while(!quit)
   {
      while(SDL_WaitEvent(&event)){
	 if(event.type == SDL_KEYDOWN){
		printf("ihuu!\n\n\n");
		switch (event.key.keysym.sym){
//**
			case SDLK_a:
				SDL_FillRect( SDL_GetVideoSurface(), NULL, 0 );
				e = SierpinskiPyramid();
				apply_surface(1024, 468, menu, screen );
				SDL_FillRect( SDL_GetVideoSurface(), NULL, 0 );
			break;
//**
			case SDLK_b:
				SDL_FillRect( SDL_GetVideoSurface(), NULL, 0 );
				e = SierpinskiTriangle();
//				apply_surface(0, 668, menu, screen );
				SDL_Flip(screen);
				SDL_FillRect( SDL_GetVideoSurface(), NULL, 0 );
			break;
//**
			case SDLK_c:
				SDL_FillRect( SDL_GetVideoSurface(), NULL, 0 );
				e = MandelbrotSet();
				//apply_surface(0, 668, menu, screen );
				SDL_BlitSurface(menu, NULL, screen, &offset);
				SDL_FillRect( SDL_GetVideoSurface(), NULL, 0 );
			break;
//**
			case SDLK_d:
				SDL_FillRect( SDL_GetVideoSurface(), NULL, 0 );
				e = JuliaSet();
			//	apply_surface(0, 668, menu, screen );
				SDL_BlitSurface(menu, NULL, screen, &offset);
				SDL_FillRect( SDL_GetVideoSurface(), NULL, 0 );
			break;
//**
			case SDLK_e:
				SDL_FillRect( SDL_GetVideoSurface(), NULL, 0 );
				e = HawaiianEarring();
				SDL_FillRect( SDL_GetVideoSurface(), NULL, 0 );
			break;

//**
			case SDLK_s:
			event.type = SDL_QUIT;
			break;
		}
	 }
         if(event.type == SDL_QUIT) { quit = 1; break; }
      }
   }

    SDL_FreeSurface(screen);
    return (EXIT_SUCCESS);



}
