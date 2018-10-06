/************************************************************************
 * This file is part of Wizznic.                                        *
 * Copyright 2009-2015 Jimmy Christensen <dusted@dusted.dk>             *
 * Wizznic is free software: you can redistribute it and/or modify      *
 * it under the terms of the GNU General Public License as published by *
 * the Free Software Foundation, either version 3 of the License, or    *
 * (at your option) any later version.                                  *
 *                                                                      *
 * Wizznic is distributed in the hope that it will be useful,           *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public License    *
 * along with Wizznic.  If not, see <http://www.gnu.org/licenses/>.     *
 ************************************************************************/

#include "swscale.h"
#include "settings.h"
#include "defs.h"
#include "pixel.h"

static SDL_Surface* scale;

SDL_Surface* swScaleInit( int sdlVideoModeFlags, int doScale )
{
#ifdef RS97
  scale = SDL_SetVideoMode(320, 480, 16, sdlVideoModeFlags);
  SDL_Surface* screen = SDL_CreateRGBSurface(SDL_SWSURFACE, 320, 240, 16, 0, 0, 0, 0);

  //Set scaling
  setting()->scaleFactor= (float)1.0;
#else	
  scale = SDL_SetVideoMode(SCREENW*doScale,SCREENH*doScale,16, sdlVideoModeFlags);
  SDL_Surface* screen = SDL_CreateRGBSurface(SDL_SWSURFACE, 320,240,16, scale->format->Rmask,scale->format->Gmask,scale->format->Bmask,0xff000000);

  //Set scaling
  setting()->scaleFactor= (float)scale->h/240.0;
#endif 

  return( screen );
}

void swScale( SDL_Surface* screen, int doScale )
{
#ifdef RS97
	if(doScale==97)
    {
      for(int y=0; y< SCREENH; y++)
      {
          memcpy(scale->pixels + y * 2 * scale->pitch, screen->pixels + y * screen->pitch, screen->pitch);
          memcpy(scale->pixels + y * 2 * scale->pitch + scale->pitch, screen->pixels + y * screen->pitch, screen->pitch);
      }
    } else
#endif    
    if(doScale==2)
    {
      int x,xx,y,yy;
      for(y=0; y< SCREENH; y++)
      {
        for(x=0; x < SCREENW; x++)
        {
          uint16_t c = freadPixel(screen,x,y);/*SDL_MapRGB(scale->format,r,g,b);*/
          xx=x*2;
          yy=y*2;
          plotPixelu(scale, xx,yy, c);
          plotPixelu(scale, xx+1,yy, c);
          plotPixelu(scale, xx,yy+1, c);
          plotPixelu(scale, xx+1,yy+1, c);
        }
      }
    } else if(doScale>2)
    {
      int x,y;
      SDL_Rect r;
      for(y=0; y< SCREENH; y++)
      {
        for(x=0; x < SCREENW; x++)
        {
          r.x=x*doScale;
          r.y=y*doScale;
          r.w=doScale;
          r.h=doScale;
          SDL_FillRect(scale, &r, freadPixel(screen,x,y));
        }
      }
    }

    if( doScale > -1 )
    {
      SDL_Flip(scale);
    }
}
