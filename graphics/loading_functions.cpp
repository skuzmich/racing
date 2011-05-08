// Copyright (C) 2011 Horoshenkih Sergey
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "loading_functions.h"

int IsNPOT(int width, int height) { // Now it returns 0...
/*
	if ((int)powf(2.0f, ceilf(logf((float)width)/logf(2.0f))) != width)
		return 1;
	if ((int)powf(2.0f, ceilf(logf((float)height)/logf(2.0f))) != height)
		return 1;
	else
  */
		return 0;
}

GLuint LoadGLTexture(const char *filename, SDL_Color *colorkey){

	SDL_Surface *temp, *image;
	GLuint texnum;
	Uint32 key;
	Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000; gmask = 0x00ff0000; bmask = 0x0000ff00;	amask = 0x000000ff;
#else
	rmask = 0x000000ff;	gmask = 0x0000ff00;	bmask = 0x00ff0000;	amask = 0xff000000;
#endif

	if ((temp = (SDL_Surface *) IMG_Load(filename))) {

		printf("image width = %d\n", temp->w);
		printf("image height = %d\n", temp->h);

		int max_size;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max_size);
		if ((temp->w > max_size) || (temp->h > max_size)) {
			fprintf(stderr, "Image size exceeds max texture size, which is %d pixels for each side\n", max_size);
			SDL_FreeSurface(temp);
			exit(-1);
		}

		/* Check for NPOT textures */
		if (IsNPOT(temp->w, temp->h)) {
			printf("NPOT texture, using special code for automatic padding\n");
				
			GLint wreal = 0, hreal = 0;
			GLint xpad = 0, ypad = 0;
			
			wreal = (int)powf(2.0, ceilf(logf((float)temp->w)/logf(2.0f)));
			hreal = (int)powf(2.0, ceilf(logf((float)temp->h)/logf(2.0f)));
			xpad = (wreal - temp->w)/2;
			ypad = (hreal - temp->h)/2;
      
			printf("tex width = %d\n", wreal);
			printf("tex height = %d\n", hreal);
			
			if (colorkey != NULL)
				image = SDL_CreateRGBSurface(SDL_SWSURFACE, wreal, hreal, 32, rmask, gmask, bmask, amask);
			else
				image = SDL_CreateRGBSurface(SDL_SWSURFACE, wreal, hreal, 24, rmask, gmask, bmask, 0);
			SDL_Rect dst = {xpad, ypad, temp->w, temp->h};

			if (colorkey != NULL) {
				key = SDL_MapRGB(temp->format, colorkey->r, colorkey->g, colorkey->b);
				SDL_FillRect(image, NULL, key); /* Without GL_BLEND transparent areas will be like colorkey and not black */
				SDL_SetColorKey(temp, SDL_SRCCOLORKEY, key);
			}
			SDL_BlitSurface(temp, 0, image, &dst);
			SDL_FreeSurface(temp);
		}
		/* POT textures */	
		else if (colorkey != NULL) {
			key = SDL_MapRGB(temp->format, colorkey->r, colorkey->g, colorkey->b);
			image = SDL_CreateRGBSurface(SDL_SWSURFACE, temp->w, temp->h, 32, rmask, gmask, bmask, amask);
			SDL_FillRect(image, NULL, key); /* Disabling GL_BLEND transparent areas will be like colorkey and not black */
			SDL_SetColorKey(temp, SDL_SRCCOLORKEY, key);
			SDL_BlitSurface(temp, 0, image, 0);
			SDL_FreeSurface(temp);
		}
		else {
			image = temp;
		}

		
		/* OpenGL Texture creation */	
		glGenTextures(1, &texnum);
		glBindTexture(GL_TEXTURE_2D, texnum);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		if (colorkey != NULL)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
		else
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

		SDL_FreeSurface(image);
		return texnum;
	}
	
	else
		return 0;
}
