#pragma once

#include <fstream>
#include <vector>
#include "Trackable.h"

class Vector2D;

const int CLEAR_VALUE = 0;
const int BLOCKING_VALUE = 1;
const int PLAYER_SPAWN = 2;
const int ENEMY_SPAWN = 3;
const int CANDY_SPAWN = 4;
const int DOOR_1 = 5;
const int DOOR_2 = 6;
const int DOOR_3 = 7;
const int DOOR_4 = 8;

class Grid:public Trackable
{
public:
	Grid( int pixelWidth, int pixelHeight, int squareSize );
	~Grid();

	int getSquareIndexFromPixelXY( int x, int y ) const;

	int getValueAtIndex( int index ) const;
	int getValueAtPixelXY( int x, int y ) const;
	void setValueAtIndex( int index, int value );
	void setValueAtPixelXY( int x, int y, int value );
	Vector2D getULCornerOfSquare( int index ) const;

	//accessors
	int getPixelWidth() const { return mPixelWidth; };
	int getPixelHeight() const { return mPixelHeight; };
	int getGridWidth() const { return mGridWidth; };
	int getGridHeight() const { return mGridHeight; };
	int getSquareSize() const { return mSquareSize; };

	//get adjacent grid square indices
	std::vector<int> getAdjacentIndices( int theSquareIndex ) const;

	void save( std::ofstream& file );
	void load( std::ifstream& file );

private:
	int* mpValues;
	int mPixelWidth;
	int mPixelHeight;
	int mSquareSize;
	int mGridWidth;
	int mGridHeight;
};