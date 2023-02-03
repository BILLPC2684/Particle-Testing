#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

typedef struct {
 uint16_t x,y,z,temp;
 uint64_t attached[26];
}  partical;

int main(int argc, char *argv[]) {
 printf("initializing SDL... %d\n", SDL_Init(SDL_INIT_VIDEO));
 printf("-3\n");
 SDL_Window* window = SDL_CreateWindow("Particle Testing...", 0, 0, 640, 480, SDL_WINDOW_SHOWN|SDL_WINDOW_VULKAN);
 printf("-2\n");
 SDL_Renderer* screen = SDL_CreateRenderer(window,-1,0);
 bool running=true;
 printf("-1\n");
 SDL_Surface* canvas = SDL_CreateRGBSurface(0, 1280, 720, 32, 0,0,0,255); SDL_SetSurfaceBlendMode(canvas, SDL_BLENDMODE_BLEND);
 SDL_Surface* sprite = SDL_CreateRGBSurface(0,    8,   8, 32, 0,0,0,255); SDL_SetSurfaceBlendMode(sprite, SDL_BLENDMODE_BLEND);

 SDL_FillRect(canvas, &(SDL_Rect){.x=0,.y=0,.w=1280,.h=720}, 0x000000FF);
 SDL_FillRect(canvas, &(SDL_Rect){.x=0,.y=0,.w=10,.h=10}, 0x7FFF0000);

 printf("0\n");
 uint32_t offset=10;
 uint8_t palette[4*1280*720]={0};
 memcpy(palette, canvas->pixels, canvas->pitch*canvas->h);
 printf("2\n");
 for(int y=0;y<11;y++) { //ARGB
  for(int x=0;x<11;x++) { offset = (y*1280)+x;
   palette[0+(offset*4)]=0x00;
   printf("canvas.pixels[X: %2i, Y: %2i, I: %5i]: RGBA(%3i, %3i, %3i, %3i)\n",x,y,offset,palette[3+(offset*4)],palette[2+(offset*4)],palette[1+(offset*4)],palette[0+(offset*4)]);
 }} memcpy(canvas->pixels, palette, canvas->pitch*canvas->h);
 while(running) {
  SDL_SetRenderDrawColor(screen, 0, 0, 0, 255);
  SDL_RenderClear(screen);
  
  int8_t b;
//  SDL_Surface* texsurf = SDL_CreateRGBSurface(0, 640, 480, 32, 0, 0, 0, 0);  SDL_SetSurfaceBlendMode(texsurf, SDL_BLENDMODE_BLEND);
//  SDL_UnlockSurface(texsurf);
//  if((b = SDL_BlitScaled(
//    texsurf, &(SDL_Rect){.x = 0,.y = 0,.w = 640,.h = 480},
//    canvas, &(SDL_Rect){.x = 0,.y = 0,.w = 640,.h = 480}))<0) {
//   printf("Error: %i (%s)\n",b,SDL_GetError());
//  }
//  SDL_LockSurface(texsurf);
  if((b = SDL_RenderCopy(screen, SDL_CreateTextureFromSurface(screen, canvas), &(SDL_Rect){.x = 0,.y = 0,.w = 640,.h = 480}, &(SDL_Rect){.x = 0,.y = 0,.w = 640,.h = 480}))<0) {
   printf("Error: %i (%s)\n",b,SDL_GetError());
  }
  SDL_SetRenderDrawColor(screen, 255, 0, 0, 255);
  SDL_Rect rect2 = {.x = 250,.y = 150,.w = 200,.h = 200};
  SDL_RenderFillRect(screen, &rect2);
  SDL_RenderPresent(screen);
  SDL_Event event;
  while(SDL_PollEvent(&event)) {
//   printf("Event: %i\n",event.type);
   switch(event.type) {
    case 256: running=false; break;
    case SDL_KEYDOWN:
     printf("Key press detected %s, %i\n",SDL_GetKeyName(event.key.keysym.sym),event.key.keysym.scancode);
     break;
    case SDL_KEYUP:
     printf("Key release detected %s, %i\n",SDL_GetKeyName(event.key.keysym.sym),event.key.keysym.scancode);
     break;
    default:
     break;
   }
  }
 }
 SDL_Quit();
 return 0;
}
