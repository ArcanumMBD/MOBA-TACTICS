//Author:	Mathieu Violette
//Date:		3/4/2015(MV)

#ifndef GAMESTATE_MANAGER_H
#define GAMESTATE_MANAGER_H

#include "GameState.h"
#include "IGame.h"
#include "IMenu.h"
#include "LobbyList.h"
#include "LoginScreen.h"
#include "MainMenu.h"
#include "Options.h"

class GameStateManager
{
private:
	GameStateManager();
	GameState currentState;
	IMenu* currentMenu;
	static IGame* gameObject;
public:
	static GameStateManager& GetInstance();
	~GameStateManager();
	GameState GetGameState() const;
	IMenu* GetCurrentMenu() const;
	void SetGameObject(IGame* _game);
	void ChangeToGameState(GameState _newGameState);
	IMenu* GetNewMenu(GameState _newGameState);
};

#endif