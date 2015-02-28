#pragma once

#include "tinyxml2.h"
#include "Texture.h"
#include "Character.h"

using namespace std;
using namespace tinyxml2;

class Tile
{
public:
	Tile();
	Tile(int _tileNumber, int _worldX, int _worldY, unsigned _tileWidth, unsigned _tileHeight);
	void InitializeTile(int _tileNumber, int _worldX, int _worldY, unsigned _tileWidth, unsigned _tileHeight);
	void RemoveCharacter();
	~Tile();

	int GetTileNumber() const;
	int GetWorldX() const;
	int GetWorldY() const;
	unsigned GetTileWidth() const;
	unsigned GetTileHeight() const;
	bool GetIsOccupied() const;
	bool GetIsHighlighted() const;
	Character* GetCharacter() const;

	void SetTileNumber(int num);
	void SetWorldX(int num);
	void SetWorldY(int num);
	void SetTileWidth(unsigned num);
	void SetTileHeight(unsigned num);
	void SetIsHighlighted(bool value);
	void SetCharacter(Character* _character);

private:
	int tileNumber;
	int worldX;
	int worldY;
	unsigned tileWidth;
	unsigned tileHeight;
	Character* character;

	bool isHighlighted;
};