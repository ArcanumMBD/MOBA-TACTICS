//Author:	Mathieu Violette
//Date:		3/22/2014(MV), 3/4/2015(MV)

#include "Game.h"

#include "Camera.h"
#include "TileMap.h"
#include "Character.h"

//FOR DEBUGGING: SWITCH TO DIFFERENT STARTING STATE
GameState startingState = GameState::LOGIN;
//GameState startingState = GameState::SCENE;

Game::Game()
{
	GameIsRunning = true;
	elaspedTime = 0;

	eventManager.KeyState = SDL_GetKeyboardState(NULL);
}

Game::~Game()
{
	SDL_DestroyRenderer(ClientAPI::mainRenderer);
	SDL_DestroyWindow(ClientAPI::mainWindow);
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
	
	ClientAPI::mainWindow = nullptr;
	ClientAPI::mainWindow = SDL_CreateWindow("MOBA-Tactics", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_SHOWN);

	ClientAPI::mainRenderer = nullptr;
	ClientAPI::mainRenderer = SDL_CreateRenderer(ClientAPI::mainWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_SetRenderDrawColor	(ClientAPI::mainRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 400);
	SDL_GetRendererOutputSize(ClientAPI::mainRenderer, &renWidth, &renHeight);

	ClientAPI::mainRenderer = ClientAPI::mainRenderer;
	ClientAPI::mainWindow = ClientAPI::mainWindow;
	ClientAPI::camera = ClientAPI::createCamera(vec2(0, 0), 1024, 768);
	//camera = new Camera(ClientAPI::mainRenderer, vec2(0, 0), 1024, 768); 

	//Initialize random
	srand(time(NULL));	

}

void Game::LoadContent()
{
	ClientAPI::mainFont = TTF_OpenFont("../Assets/Font/lazy.ttf", 72);

	ClientAPI::tileMap = ClientAPI::createMap("../Assets/XML_Files/IsoMap.tmx", vec2(400, 100), "../Assets/Images/HighlightTile.png");
	//tiles = new TileMap("../Assets/XML_Files/IsoMap.tmx", vec2(400, 100), "../Assets/Images/HighlightTile.png", ClientAPI::mainRenderer);
	//tiles = new TileMap("../Assets/XML_Files/IsoMap.tmx", vec2(0, 0), "../Assets/Images/HighlightTile.png", ClientAPI::mainRenderer);
	TILEMAP->SetHighlightColor(255, 0, 0);

	ClientAPI::character = ClientAPI::createCharacter("../Assets/Images/Character.png", ClientAPI::tileMap->GetTileAt(1, 0, 0));
	//character = new Character("../Assets/Images/Character.png", tiles->GetTileAt(1, 0, 0), ClientAPI::mainRenderer);
	CAMERA->AddToDrawList(TILEMAP);
	CAMERA->AddToDrawList(CHARACTER);
	CAMERA->SetPosition(vec2(100, 100));
}

void Game::UnloadContent()
{
	//End program

	delete ClientAPI::tileMap;
	delete ClientAPI::character;
	delete ClientAPI::camera;

	TTF_CloseFont(ClientAPI::mainFont);

	Mix_FreeChunk(ClientAPI::_audioChannel);
	Mix_FreeChunk(ClientAPI::_audioChannel1);
	Mix_FreeChunk(ClientAPI::_audioChannel2);
	Mix_FreeChunk(ClientAPI::_audioChannel3);

	ClientAPI::_audioChannel = NULL;
	ClientAPI::_audioChannel1 = NULL;
	ClientAPI::_audioChannel2 = NULL;
	ClientAPI::_audioChannel3 = NULL;

	Mix_FreeMusic(ClientAPI::mainMusic);
	ClientAPI::mainMusic = NULL;

	SDL_DestroyRenderer(ClientAPI::mainRenderer);
	SDL_DestroyWindow(ClientAPI::mainWindow);
	ClientAPI::mainRenderer = NULL;
	ClientAPI::mainWindow = NULL;
}

void Game::Update()
{
	switch (gameStateManager.GetGameState())
	{
		case GameState::NONE:
			//Start of game, set to login screen
			gameStateManager.QueueChangeToGameState(startingState);
			break;
		case GameState::SCENE:
			CAMERA->Update();
			TILEMAP->Update();
			CHARACTER->Update();
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
			CAMERA->Draw(ClientAPI::mainRenderer);
			//tiles->Draw(vec2(0, 0), ClientAPI::mainRenderer);
			//tiles->Draw(ClientAPI::mainRenderer);
			//tiles->DrawTile(vec2(0, 0), 1, 5, 5, ClientAPI::mainRenderer);
			//character->Draw(ClientAPI::mainRenderer);
			break;
		default:
			gameStateManager.GetCurrentMenu()->Draw(ClientAPI::mainRenderer);
			break;
	}
}

void Game::Exit()
{
	GameIsRunning = false;
}