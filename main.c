/*
** LepetitdHomme Fractales prog. 21/10/2107
** gcc main.c libft/libft.a `sdl2-config --cflags --libs`
*/


#include "libft/libft.h"
#include <SDL2/SDL.h>
# define SCRX 1200
# define SCRY 800

void  exit_properly(int i, SDL_Window *window, SDL_Renderer *renderer)
{
  (void *)renderer;
  if (i == 1) { ft_putendl("SDL failed, exiting."); EXIT_FAILURE; }
  else if (i == 2) { ft_putendl("Could not create windowm exiting."); SDL_Quit(); EXIT_FAILURE; }
  else if (i == 3) {
    ft_putendl("Could not create render, exiting");
    SDL_DestroyWindow(window);
    SDL_Quit();
    EXIT_FAILURE;
  }
  else { SDL_Quit(); EXIT_SUCCESS; }
}


int   set_color(SDL_Renderer *renderer, int a, int maxit)
{
  int r = a * 255 / maxit;
  SDL_SetRenderDrawColor(renderer, 0, 0, r, 255);
  return 0;
}

int   loop(SDL_Renderer *renderer, int maxit, double zoom, int moveX, int moveY)
{
  int x = 0;
  int y = 0;
  int a = 0;
  double minX = -2.4;
  double maxX =  2.4;
  double minY = -1.5;
  double maxY =  1.5;
  double rc, ic, rz, iz, tmpR, tmpI;
  while (x < SCRX)
  {
    y = 0;
    while (y < SCRY)
    {
      //rc = 1.5 * (x - SCRX / 2) / (0.5 * zoom * SCRX) + moveX;
      //ic = (y - SCRY / 2) / (0.5 * zoom * SCRY) + moveY;
      rc = minX + (maxX - minX)/(SCRX * 0.5 * zoom + moveX) * x;
      ic = minY + (maxY - minY)/(SCRY * 0.5 * zoom + moveY) * y;
      rz = 0;
      iz = 0;
      a = 0;
      while (a < maxit)
      {
        tmpR = rz;
        tmpI = iz;
        rz = tmpR * tmpR - tmpI * tmpI + rc;
        iz = 2 * tmpR * tmpI + ic;
        if (rz * rz  + iz * iz >= 4)
          break;
        a++;
      }
      set_color(renderer, a, maxit);
      SDL_RenderDrawPoint(renderer, x, y);
      y++;
    }
    x++;
  }
  return 0;
}

int   main(int argc, char **argv)
{
  SDL_Window *window = NULL;
  SDL_Renderer  *renderer = NULL;

  if (SDL_Init(SDL_INIT_VIDEO) != 0) exit_properly(1, NULL, NULL);
  if ((window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCRX, SCRY, SDL_WINDOW_SHOWN)) == NULL) exit_properly(2, NULL, NULL);
  if ((renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)) == NULL) exit_properly(3, window, NULL);

  int play = 0;
  SDL_Event event;
  int maxit = 60;
  double zoom = 2;
  int moveX = 0, moveY = 0;
  loop(renderer, maxit, zoom, moveX, moveY);
  SDL_RenderPresent(renderer);
  while (!play && SDL_WaitEvent(&event))
  {
    if (event.type == SDL_QUIT)
      play = 1;
    else if (event.type == SDL_KEYDOWN)
    {
      if(event.key.keysym.scancode == SDL_SCANCODE_Q)
      {
        zoom *= 1.1;
        loop(renderer, maxit, zoom, moveX, moveY);
        SDL_RenderPresent(renderer);  
      }
      else if(event.key.keysym.scancode == SDL_SCANCODE_W)
      {
        zoom = 1;
        loop(renderer, maxit, zoom, moveX, moveY);
        SDL_RenderPresent(renderer);  
      }
      else if(event.key.keysym.scancode == SDL_SCANCODE_A)
      {
        if (maxit > 0) {maxit++;}
        loop(renderer, maxit, zoom, moveX, moveY);
        SDL_RenderPresent(renderer);  
      }
      else if(event.key.keysym.scancode == SDL_SCANCODE_S)
      {
        if (maxit < 2000) {maxit--;}
        loop(renderer, maxit, zoom, moveX, moveY);
        SDL_RenderPresent(renderer);  
      }
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
    {
        SDL_GetMouseState(&moveX, &moveY);
        loop(renderer, maxit, zoom, moveX, moveY);
        SDL_RenderPresent(renderer);  
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_RIGHT)
    {
        moveX = 0;
        moveY = 0;
        loop(renderer, maxit, zoom, moveX, moveY);
        SDL_RenderPresent(renderer);  
    }
    else { continue; }
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}