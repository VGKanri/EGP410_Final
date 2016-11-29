#pragma once

#include <Trackable.h>
#include <Vector2D.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

class PathfindingDebugContent;
class GraphicsBuffer;
class GridPathfinder;

class DebugDisplay:public Trackable
{
public:
	DebugDisplay( const Vector2D& pos, PathfindingDebugContent* pContent );
	~DebugDisplay();

	void draw( GraphicsBuffer* pBuffer );

	void changePathfinderData(GridPathfinder* pPathfinder);

private:
	ALLEGRO_FONT* mpFont;
	PathfindingDebugContent* mpContent;
	Vector2D mPos;

};