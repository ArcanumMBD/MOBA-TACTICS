//Author:	Mathieu Violette
//Date:		3/26/2015(MV)

#include "TextSprite.h"

//===========================
//		 PROPERTIES
//===========================

std::string& TextSprite::GetText()
{
	return label;
}

void TextSprite::SetText(const char* _text)
{
	label = _text;

	if (Text != nullptr)
		SDL_DestroyTexture(Text);

	SDL_Surface* textSurface = TTF_RenderText_Solid(font, label.c_str(), labelColor);

	Text = SDL_CreateTextureFromSurface(ClientAPI::mainRenderer, textSurface);

	SDL_FreeSurface(textSurface);

	ResizeTextDimensions();
}

SDL_Color& TextSprite::GetTextColor()
{
	return labelColor;
}

void TextSprite::SetTextColor(SDL_Color& colour)
{
	labelColor = colour;
}

float TextSprite::GetTextScale()
{
	return labelScale;
}

void TextSprite::SetTextScale(float scale)
{
	labelScale = scale;
}

//===========================
//  CONSTRUCTOR / DESTRUCTOR
//===========================

TextSprite::TextSprite(const char* text, SDL_Rect& dimensions, SDL_Renderer* ren, TTF_Font* _font, bool useOrigin, float scale, SDL_RendererFlip spriteEffect)
{
	font = _font;
	
	//Make invisible background
	SDL_Surface* loadedSurface = IMG_Load("../Assets/Images/white1x1.png");
	Image = SDL_CreateTextureFromSurface(ren, loadedSurface);
	SetAlpha(0);
	SetBlendMode(SDL_BLENDMODE_BLEND);

	Initialize(dimensions.w, dimensions.h, vec2(dimensions.x, dimensions.y), useOrigin, scale, spriteEffect);

	SetText(text);

	SDL_FreeSurface(loadedSurface);
}

TextSprite::TextSprite(SDL_Color& colour, SDL_Renderer* ren, SDL_Rect& dimensions, TTF_Font* _font, bool useOrigin, float scale, SDL_RendererFlip spriteEffect)
{
	font = _font;

	SDL_Surface* loadedSurface = IMG_Load("../Assets/Images/white1x1.png");
	Image = SDL_CreateTextureFromSurface(ren, loadedSurface);

	SetColor(colour.r, colour.g, colour.b);
	SetAlpha(colour.a);

	Initialize(dimensions.w, dimensions.h, vec2(dimensions.x, dimensions.y), useOrigin, scale, spriteEffect);

	SDL_FreeSurface(loadedSurface);
}

TextSprite::TextSprite(SDL_Surface *image, SDL_Renderer* ren, vec2 pos, TTF_Font* _font, bool useOrigin, float scale, SDL_RendererFlip spriteEffect)
{
	font = _font;

	Image = SDL_CreateTextureFromSurface(ren, image);

	Initialize(image->w, image->h, pos, useOrigin, scale, spriteEffect);

	SDL_FreeSurface(image);
}

void TextSprite::Initialize(int width, int height, vec2 pos, bool useOrigin, float scale, SDL_RendererFlip spriteEffect)
{
	label = "";
	labelColor = ClientAPI::Color.Black;
	SetTextScale(0.925f);

	Sprite::Initialize(width, height, pos, useOrigin, scale, spriteEffect);
}

TextSprite::~TextSprite()
{
	if (Image != NULL)
		SDL_DestroyTexture(Image);

	if (Text != NULL)
		SDL_DestroyTexture(Text);

	font = nullptr;
}

void TextSprite::Draw(SDL_Renderer* ren)
{
	Sprite::Draw(ren);

	if (Text != nullptr)
	{
		SDL_RenderCopyEx(ren, Text, NULL, &textDimensions, Rotation, &origin, SpriteEffect);
	}
}

//===========================
//	   UTILITY METHODS
//===========================

void TextSprite::ResizeTextDimensions()
{
	//Text width & height
	int w, h;

	TTF_SizeText(font, label.c_str(), &w, &h);

	float scale = Scale * labelScale;
	int x = rect.x + ((dimensions.x * .5f) - (dimensions.x * scale * .5f));
	int y = rect.y + (rect.h - h)*.5f + rect.h*.05f;
	//int w = rect.w * scale;
	//int h = rect.h * scale;
	
	textDimensions = ClientAPI::createRectangle(x, y, w, h);
}