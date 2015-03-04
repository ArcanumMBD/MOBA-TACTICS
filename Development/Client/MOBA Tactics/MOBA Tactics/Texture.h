//Author:	Nicholas Higa
//Date:		3/4/2014(NH)
#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "glm/glm.hpp"

using namespace glm;

//Texture wrapper class
class Texture
{
public:
	//Initializes variables
	Texture();

	//Deallocates memory
	~Texture();

	//Loads image at specified path
	bool LoadFromFile(std::string path, SDL_Renderer *ren);

	void SetBlendMode(SDL_BlendMode blending);
	void SetColor(Uint8 r, Uint8 g, Uint8 b);
	void SetAlpha(Uint8 alpha);

	//Deallocates texture
	void Free();

	void Update();

	//Renders texture at given point
	void Render(int x, int y, SDL_Rect* clip, SDL_Renderer* ren);

	//Gets image dimensions
	int GetWidth();
	int GetHeight();

private:
	//The actual hardware texture
	SDL_Texture* texture;

	//Image dimensions
	int width;
	int height;
};