#ifndef HIT_CIRCLE
#define HIT_CIRCLE

#include "Trackable.h"
#include "Vector2D.h"
#include <memory>

class Hitbox;

class Hitcircle :public Trackable
{
public:
	Hitcircle();
	Hitcircle(Vector2D position, float radius);
	~Hitcircle() {};

	void update(float deltaX, float deltaY); //moves with whatever object the circle is attatched to
	void draw();
		
	bool checkCollision(Hitbox& otherBox); //checks collision with another collider
private:
	Vector2D mPos;
	float mRadius;

	std::shared_ptr<bool> mpShowCircles; //shared pointer that determines whether to draw the boxes or not
};

#endif