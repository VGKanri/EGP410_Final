#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include "GridVisualizer.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "GraphicsBufferManager.h"
#include "Grid.h"
#include "Sprite.h"
#include "Vector2D.h"
#include "Game.h"


GridVisualizer::GridVisualizer( Grid* pGrid, bool inEditor)
:mpGrid(pGrid)
,mDirty(true)
{
	mInEditor = inEditor;

	if (!mInEditor)
	{
		mpWallSprite = new Sprite(gpGame->getGraphicsBufferManager()->getBuffer(WALL_SPRITE_ID), 0, 0, 32, 32);
		mpFloorSprite = new Sprite(gpGame->getGraphicsBufferManager()->getBuffer(FLOOR_SPRITE_ID), 0, 0, 32, 32);
		mpCoinSprite = new Sprite(gpGame->getGraphicsBufferManager()->getBuffer(COIN_SPRITE_ID), 0, 0, 32, 32);
		mpDoorSprite = new Sprite(gpGame->getGraphicsBufferManager()->getBuffer(DOOR_SPRITE_ID), 0, 0, 32, 32);
	}
}

GridVisualizer::~GridVisualizer()
{
	if (!mInEditor)
	{
		delete mpWallSprite;
		delete mpFloorSprite;
		delete mpCoinSprite;
		delete mpDoorSprite;
	}
}

void GridVisualizer::switchGrid(Grid* pGrid)
{
	mpGrid = pGrid;
	mDirty = true;
}

void GridVisualizer::refresh()
{	
	if( mDirty )
	{
		//remove old entries first
		removeAllEntriesOfColor(WALL_COLOR);
		removeAllEntriesOfColor(PLAYER_COLOR);
		removeAllEntriesOfColor(ENEMY_COLOR);
		removeAllEntriesOfColor(CANDY_COLOR);
		removeAllEntriesOfColor(DOOR_1_COLOR);
		removeAllEntriesOfColor(DOOR_2_COLOR);
		removeAllEntriesOfColor(DOOR_3_COLOR);
		removeAllEntriesOfColor(DOOR_4_COLOR);

		int size = mpGrid->getGridWidth() * mpGrid->getGridHeight();
		//get any non-zero squares and send them to the visualizer
		for( int i=0; i<size; i++ )
		{
 			switch (mpGrid->getValueAtIndex(i))
			{
			case BLOCKING_VALUE:
				addColor(i, WALL_COLOR);
				break;
			case PLAYER_SPAWN:
				addColor(i, PLAYER_COLOR);
				break;
			case ENEMY_SPAWN:
				addColor(i, ENEMY_COLOR);
				break;
			case CANDY_SPAWN:
				addColor(i, CANDY_COLOR);
				break;
			case DOOR_1:
				addColor(i, DOOR_1_COLOR);
				break;
			case DOOR_2:
				addColor(i, DOOR_2_COLOR);
				break;
			case DOOR_3:
				addColor(i, DOOR_3_COLOR);
				break;
			case DOOR_4:
				addColor(i, DOOR_4_COLOR);
				break;				
			}
		}
	}
	mDirty = false;
}

void GridVisualizer::addColor( int index, const ALLEGRO_COLOR& color )
{
	//set dirty flag
	mDirty = true;

	//find the existing entry in the map (if it exists)
	std::map< ALLEGRO_COLOR, std::vector<int>, AllegroColorCompare >::iterator iter = mColormap.find( color );

	if( iter != mColormap.end() )//found the existing entry
	{
		iter->second.push_back( index );
	}
	else
	{
		//create a vector to put in the map
		std::vector<int> colorVector;
		colorVector.push_back( index );

		//put the vector into the map
		mColormap[color] = colorVector;
	}
}

void GridVisualizer::removeAllEntriesOfColor( const ALLEGRO_COLOR& color )
{
	//find the existing entry in the map (if it exists)
	std::map< ALLEGRO_COLOR, std::vector<int>, AllegroColorCompare >::iterator iter = mColormap.find( color );
	
	if( iter != mColormap.end() )
	{
		mColormap.erase( iter );
	}
}

void GridVisualizer::draw( GraphicsBuffer& dest )
{
	if( mDirty )
	{
		refresh();
	}

	ALLEGRO_BITMAP* pOldTarget = GraphicsSystem::switchTargetBitmap( dest.getBitmap() );

	int gridHeight = mpGrid->getGridHeight();
	int gridWidth = mpGrid->getGridWidth();
	int numSquares = gridWidth * gridHeight;
	int squareSize = mpGrid->getSquareSize();

	//we need these so we can know which square is the start and goal
	static ALLEGRO_COLOR startColor = al_map_rgb(1, 255, 128);
	static ALLEGRO_COLOR stopColor = al_map_rgb(255, 255, 0);

	//the draw loop for the editor. Uses Dean's weird stuff.
	if (mInEditor)
	{
		std::map< ALLEGRO_COLOR, std::vector<int>, AllegroColorCompare >::iterator iter;
		for (iter = mColormap.begin(); iter != mColormap.end(); ++iter)
		{
			std::vector<int> theIndices = iter->second;

			for (unsigned int i = 0; i < theIndices.size(); i++)
			{
				Vector2D ulPos = mpGrid->getULCornerOfSquare(theIndices[i]);

				//this is gonna get kinda gross, but for now, this is what needs to draw in the editor
				al_draw_filled_rectangle(ulPos.getX(), ulPos.getY(), ulPos.getX() + squareSize, ulPos.getY() + squareSize, iter->first);

				//Check if square's color matches the start or goal colors, so we can draw the text
				if (iter->first.r == startColor.r && iter->first.g == startColor.g && iter->first.b == startColor.b)
				{
					al_draw_text(gpGame->getFont(), al_map_rgb(0, 0, 0), ulPos.getX() + squareSize / 2, ulPos.getY(), ALLEGRO_ALIGN_CENTER, "S");
				}
				else if (iter->first.r == stopColor.r && iter->first.g == stopColor.g && iter->first.b == stopColor.b)
				{
					al_draw_text(gpGame->getFont(), al_map_rgb(0, 0, 0), ulPos.getX() + squareSize / 2, ulPos.getY(), ALLEGRO_ALIGN_CENTER, "G");
				}

				//these should only apply for the editor. May need to set a flag for this later on
				else if (iter->first.r == PLAYER_COLOR.r && iter->first.g == PLAYER_COLOR.g && iter->first.b == PLAYER_COLOR.b)
				{
					al_draw_text(gpGame->getFont(), al_map_rgb(0, 0, 0), ulPos.getX() + squareSize / 2, ulPos.getY(), ALLEGRO_ALIGN_CENTER, "P");
				}
				else if (iter->first.r == ENEMY_COLOR.r && iter->first.g == ENEMY_COLOR.g && iter->first.b == ENEMY_COLOR.b)
				{
					al_draw_text(gpGame->getFont(), al_map_rgb(0, 0, 0), ulPos.getX() + squareSize / 2, ulPos.getY(), ALLEGRO_ALIGN_CENTER, "E");
				}
				else if (iter->first.r == CANDY_COLOR.r && iter->first.g == CANDY_COLOR.g && iter->first.b == CANDY_COLOR.b)
				{
					al_draw_text(gpGame->getFont(), al_map_rgb(0, 0, 0), ulPos.getX() + squareSize / 2, ulPos.getY(), ALLEGRO_ALIGN_CENTER, "C");
				}
				else if (iter->first.r == DOOR_1_COLOR.r && iter->first.g == DOOR_1_COLOR.g && iter->first.b == DOOR_1_COLOR.b)
				{
					al_draw_text(gpGame->getFont(), al_map_rgb(0, 0, 0), ulPos.getX() + squareSize / 2, ulPos.getY(), ALLEGRO_ALIGN_CENTER, "1");
				}
				else if (iter->first.r == DOOR_2_COLOR.r && iter->first.g == DOOR_2_COLOR.g && iter->first.b == DOOR_2_COLOR.b)
				{
					al_draw_text(gpGame->getFont(), al_map_rgb(0, 0, 0), ulPos.getX() + squareSize / 2, ulPos.getY(), ALLEGRO_ALIGN_CENTER, "2");
				}
				else if (iter->first.r == DOOR_3_COLOR.r && iter->first.g == DOOR_3_COLOR.g && iter->first.b == DOOR_3_COLOR.b)
				{
					al_draw_text(gpGame->getFont(), al_map_rgb(0, 0, 0), ulPos.getX() + squareSize / 2, ulPos.getY(), ALLEGRO_ALIGN_CENTER, "3");
				}
				else if (iter->first.r == DOOR_4_COLOR.r && iter->first.g == DOOR_4_COLOR.g && iter->first.b == DOOR_4_COLOR.b)
				{
					al_draw_text(gpGame->getFont(), al_map_rgb(0, 0, 0), ulPos.getX() + squareSize / 2, ulPos.getY(), ALLEGRO_ALIGN_CENTER, "4");
				}
			}
		}
	}

	//the draw loop for the actual game
	else
	{
		for (int i = 0; i < mpGrid->getSize(); ++i)
		{
			Vector2D ulPos = mpGrid->getULCornerOfSquare(i);
			//if empty space
			if (mpGrid->getValueAtIndex(i) != BLOCKING_VALUE)
			{
				mpFloorSprite->draw(dest, ulPos.getX(), ulPos.getY());

				if (mpGrid->getValueAtIndex(i) == COIN)
				{
					mpCoinSprite->draw(dest, ulPos.getX(), ulPos.getY());
				}
				else if (mpGrid->getValueAtIndex(i) == DOOR_1 || mpGrid->getValueAtIndex(i) == DOOR_2 ||
						 mpGrid->getValueAtIndex(i) == DOOR_3 || mpGrid->getValueAtIndex(i) == DOOR_4)
				{
					mpDoorSprite->draw(dest, ulPos.getX(), ulPos.getY());
				}
			}
			//if wall
			else if((mpGrid->getValueAtIndex(i) == BLOCKING_VALUE))
			{
				mpWallSprite->draw(dest, ulPos.getX(), ulPos.getY());
			}
		}		
	}
	
	GraphicsSystem::switchTargetBitmap( pOldTarget );
}

void GridVisualizer::clear()
{
	mColormap.clear();
}