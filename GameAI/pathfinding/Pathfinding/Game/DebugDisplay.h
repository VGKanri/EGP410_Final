#pragma once

#include <Trackable.h>
#include <Vector2D.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

class PathfindingDebugContent;
class GraphicsBuffer;
class GridPathfinder;

const int COIN_SCORE = 10;
const int ENEMY_SCORE = 100;

class DebugDisplay:public Trackable
{
public:
	DebugDisplay( const Vector2D& pos);
	~DebugDisplay();

	void draw( GraphicsBuffer* pBuffer );
	void drawFinal(GraphicsBuffer* pBuffer);

	void coinGot();
	void enemyKilled();

private:
	ALLEGRO_FONT* mpFont;
	ALLEGRO_FONT* mpFinalFont;
	Vector2D mPos;
	Vector2D mFinalPos;
	int mScore;
};