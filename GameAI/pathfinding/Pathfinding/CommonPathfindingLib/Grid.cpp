#include "Grid.h"
#include "GraphicsSystem.h"
#include "Vector2D.h"
#include <memory.h>

Grid::Grid( int pixelWidth, int pixelHeight, int squareSize )
:mPixelWidth(pixelWidth)
,mPixelHeight(pixelHeight)
,mSquareSize(squareSize)
{
	srand(time(NULL));
	mGridWidth = pixelWidth / squareSize;
	mGridHeight = pixelHeight / squareSize;
	mpValues = new int[ mGridWidth * mGridHeight ];
	memset( mpValues, 0, sizeof(int) * mGridWidth * mGridHeight  );
}

Grid::~Grid()
{
	delete [] mpValues;
}

int Grid::getSquareIndexFromPixelXY( int x, int y ) const
{
	x /= mSquareSize;
	y /= mSquareSize;
	return y * mGridWidth + x;
}

int Grid::getValueAtIndex( int index ) const
{
	if (index >= 0 && index < mGridWidth*mGridHeight)
	{
		return *(mpValues + index);
	}
	else
	{
		return CLEAR_VALUE;
	}
}

int Grid::getValueAtPixelXY( int x, int y ) const
{
	int index = getSquareIndexFromPixelXY( x, y );
	return getValueAtIndex( index );
}
	
void Grid::setValueAtIndex( int index, int value )
{
	if (index >= 0 && index < mGridWidth*mGridHeight)
	{
		*(mpValues + index) = value;
	}
}

void Grid::setValueAtPixelXY( int x, int y, int value )
{
	int index = getSquareIndexFromPixelXY( x, y );
	setValueAtIndex( index, value );
}

Vector2D Grid::getULCornerOfSquare( int index ) const
{
	int squareY = index / mGridWidth;
	int squareX = index % mGridWidth;
	Vector2D pos( (float)(squareX * mSquareSize), (float)(squareY * mSquareSize) );
	return pos;
}

Vector2D Grid::getCenterOfSquare(int index) const
{
	int squareY = index / mGridWidth;
	int squareX = index % mGridWidth;
	Vector2D pos((float)(squareX * mSquareSize) + mSquareSize/2, (float)(squareY * mSquareSize) + mSquareSize/2);
	return pos;
}

int Grid::getIndexOfPlayerSpawn() const
{
	for (int i = 0; i < mGridWidth * mGridHeight; ++i)
	{
		if (getValueAtIndex(i) == PLAYER_SPAWN)
		{
			return i;
		}
	}

	return 0;
}

bool Grid::searchForValue(int value)
{
	for (int i = 0; i < mGridWidth * mGridHeight; ++i)
	{
		if (mpValues[i] == value)
		{
			return true;
		}
	}

	return false;
}

//Randomly generate coin drops
void Grid::generateCoins()
{
	int tmp;

	for (int i = 0; i < mGridWidth * mGridHeight; ++i)
	{
		//only generate a coin if the area is clear
		if (mpValues[i] == CLEAR_VALUE)
		{
			tmp = rand() % 10 + 1;

			if (tmp == 1)
			{
				setValueAtIndex(i, COIN);
			}
		}		
	}
}

//get adjacent grid square indices
std::vector<int> Grid::getAdjacentIndices( int theSquareIndex ) const
{
	std::vector<int> indices;

	static const int NUM_DIRS = 4;
	//						        N  NE	E  SE	S	SW	 W	NW
	//static int xMods[NUM_DIRS] = {	0,	1,	1,	1,	0,	-1,	-1,	-1 };
	//static int yMods[NUM_DIRS] = { -1, -1,	0,	1,	1,	 1,	 0,	-1 };

	static int xMods[NUM_DIRS] = { 0,	1,	0,	-1, };
	static int yMods[NUM_DIRS] = { -1,	0,	1,	 0, };

	//find the x,y of the passed in index
	int x = theSquareIndex % mGridWidth;
	int y = theSquareIndex / mGridWidth;

	for( int i=0; i<NUM_DIRS; i++ )
	{
		//calc adjacent x,y
		int adjX = x + xMods[i];
		int adjY = y + yMods[i];

		//convert back to an index if on the Grid
		if( adjX >= 0 && adjX < mGridWidth && adjY >=0 && adjY < mGridHeight )
		{
			int adjIndex = ( adjY * mGridWidth ) + adjX;

			//add to vector of indices
			indices.push_back( adjIndex );
		}
	}
	return indices;
}


void Grid::save( std::ofstream& file )
{
	int numSquares = mGridWidth * mGridHeight;
	for( int i=0; i<numSquares; i++ )
	{
		file << mpValues[i] << " ";
	}
}

void Grid::load( std::ifstream& file )
{
	int numSquares = mGridWidth * mGridHeight;
	for( int i=0; i<numSquares; i++ )
	{
		file >> mpValues[i];
	}
}
