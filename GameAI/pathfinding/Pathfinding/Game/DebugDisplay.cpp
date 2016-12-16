#include "DebugDisplay.h"
#include <allegro5/allegro_ttf.h>
#include "GraphicsBuffer.h"
#include "GridPathfinder.h"
#include "DebugContent.h"
#include <sstream>
#include "PathfindingDebugContent.h"

using namespace std;

DebugDisplay::DebugDisplay( const Vector2D& pos )
	:mPos(pos)
{
	//actually load the font
	mpFont = al_load_ttf_font( "cour.ttf", 24, 0 );
	if( mpFont == NULL )
	{
		printf( "ttf font file not loaded properly!\n" ); 
		assert(0);
	}

	mScore = 0;
}

DebugDisplay::~DebugDisplay()
{
	al_destroy_font(mpFont);
}

void DebugDisplay::draw( GraphicsBuffer* pBuffer )
{
	std::stringstream ss;
	ss << "Score: " << mScore;

	al_draw_text( mpFont, al_map_rgb( 255, 255, 255 ), mPos.getX(), mPos.getY(), ALLEGRO_ALIGN_LEFT, ss.str().c_str() );

}

void DebugDisplay::coinGot()
{
	mScore += COIN_SCORE;
}

void DebugDisplay::enemyKilled()
{
	mScore += ENEMY_SCORE;
}
