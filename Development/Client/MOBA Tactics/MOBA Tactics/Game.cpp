//Author:	Mathieu Violette
//Date:		3/22/2014(MV), 3/4/2015(MV)

#include "Game.h"

int StringToInt(const std::string &Text);

Texture *texture;
TileMap *tiles;
Character *character;
vec3 charPos;

Game::Game()
{
	GameIsRunning = true;
	elaspedTime = 0;

	KeyState = SDL_GetKeyboardState(NULL);
}

Game::~Game()
{
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDLNet_Quit();
	SDL_Quit();
}

void Game::Init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDLNet_Init();
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	TTF_Init();
	Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG);
	SDL_Init(SDL_INIT_AUDIO);
	Window = nullptr;

	Window = SDL_CreateWindow("MOBA-Tactics", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_SHOWN);

	Renderer = nullptr;
	Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 400);
	SDL_GetRendererOutputSize(Renderer, &renWidth, &renHeight);

	//Initialize random
	srand(time(NULL));	

}

void Game::LoadContent()
{
	texture = new Texture();
	tiles = new TileMap("../Assets/XML_Files/IsoMap.tmx", vec2(250, 50), "../Assets/Images/HighlightTile.png", Renderer);
	tiles->HighlightTile(1, 0, 0);
	tiles->SetHighlightColor(255, 0, 0);

	charPos = vec3(1, 0, 1);
	character = new Character("../Assets/Images/Character.png", tiles->GetTileAt(1, 0, 1), Renderer);
}

void Game::UnloadContent()
{
	delete texture;
	delete tiles;
	delete character;
}

void Game::Update()
{
	switch (gameStateManager.GetGameState())
	{
		case GameState::NONE:
			//Start of game, set to login screen
			gameStateManager.ChangeToGameState(GameState::LOGIN);
			break;
		case GameState::SCENE:
			tiles->Update();
			character->Update();
			break;
		default:
			gameStateManager.GetCurrentMenu()->Update();
			break;
	}
}

void Game::Draw()
{
	switch (gameStateManager.GetGameState())
	{
		case GameState::NONE:
			break;
		case GameState::SCENE:
			tiles->DrawMap(Renderer);
			character->Draw(Renderer);
			break;
		default:
			gameStateManager.GetCurrentMenu()->Draw(Renderer);
			break;
	}
}

void Game::Exit()
{
	GameIsRunning = false;
}

int StringToInt(const std::string &Text)
{
	std::stringstream ss(Text);
	int result;
	return ss >> result ? result : 0;
}