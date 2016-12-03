#include "StateManager.h"
#include "Game.h"

#include <allegro5\allegro.h>
#include <sstream>
#include <iomanip>
#include <fstream>

StateManager::StateManager(float defaultVel, float defaultRad, float defaultAngular, bool defaultShowBox,
	float defaultAlignWeight, float defaultSeperateWeight, float defaultCohesionWeight):
mpEnemyVel(new float(defaultVel)),
mpEnemyRadius(new float(defaultRad)),
mpEnemyAngularVel(new float(defaultAngular)),
mpShowCollisionBoxes(new bool(defaultShowBox)),
mpAlignmentWeight(new float(defaultAlignWeight)),
mpCohesionWeight(new float(defaultCohesionWeight)),
mpSeperationWeight(new float(defaultSeperateWeight))
{
	//init strings
	setState(VELOCITY); //note to self, mActive is defaultly true so this will still work
	
	//read save data
	std::ifstream saveData("SaveData.txt");
	if (saveData.is_open())
	{
		saveData >> *mpAlignmentWeight;

		saveData >> *mpCohesionWeight;

		saveData >> *mpSeperationWeight;

		saveData.close();
	}

	std::stringstream ss;

	ss << std::fixed << std::setprecision(1) << *mpEnemyVel;
	mEnemyVelText = "[V] Enemy Velocity: " + ss.str();
	ss.str(std::string());

	ss << std::fixed << std::setprecision(1) << *mpEnemyRadius;
	mEnemyRadiusText = "[R] Enemy Reaction Radius: " + ss.str();
	ss.str(std::string());

	ss << std::fixed << std::setprecision(1) << *mpEnemyAngularVel;
	mEnemyAngularVelText = "[E] Enemy Angular Velocity: " + ss.str();
	ss.str(std::string());

	mCollisionDebugText = "[B] Collision Debug: Off";

	ss << std::fixed << std::setprecision(1) << *mpAlignmentWeight;
	mAlignmentWeightText = "[A] Alignment Weight: " + ss.str();
	ss.str(std::string());

	ss << std::fixed << std::setprecision(1) << *mpCohesionWeight;
	mCohesionWeightText = "[C] Cohesion Weight: " + ss.str();
	ss.str(std::string());

	ss << std::fixed << std::setprecision(1) << *mpSeperationWeight;
	mSeperationWeightText = "[S] Seperation Weight: " + ss.str();
	ss.str(std::string());

	mActive = false;
}

StateManager::~StateManager()
{

}

void StateManager::update()
{
	if (mActive)
	{
		//draw strings
		al_draw_text(gpGame->getFont(), WHITE, 5, 0, ALLEGRO_ALIGN_LEFT, mEnemyVelText.c_str());
		al_draw_text(gpGame->getFont(), WHITE, 5, 20, ALLEGRO_ALIGN_LEFT, mEnemyRadiusText.c_str());
		al_draw_text(gpGame->getFont(), WHITE, 5, 40, ALLEGRO_ALIGN_LEFT, mEnemyAngularVelText.c_str());
		al_draw_text(gpGame->getFont(), WHITE, 5, 60, ALLEGRO_ALIGN_LEFT, mCollisionDebugText.c_str());
		al_draw_text(gpGame->getFont(), WHITE, 5, 80, ALLEGRO_ALIGN_LEFT, mAlignmentWeightText.c_str());
		al_draw_text(gpGame->getFont(), WHITE, 5, 100, ALLEGRO_ALIGN_LEFT, mCohesionWeightText.c_str());
		al_draw_text(gpGame->getFont(), WHITE, 5, 120, ALLEGRO_ALIGN_LEFT, mSeperationWeightText.c_str());

		//redraw active value in selected color
		switch (mState)
		{
		case VELOCITY:
			al_draw_text(gpGame->getFont(), MAGENTA, 5, 0, ALLEGRO_ALIGN_LEFT, mEnemyVelText.c_str());
			break;
		case RADIUS:
			al_draw_text(gpGame->getFont(), MAGENTA, 5, 20, ALLEGRO_ALIGN_LEFT, mEnemyRadiusText.c_str());
			break;
		case ANGULAR:
			al_draw_text(gpGame->getFont(), MAGENTA, 5, 40, ALLEGRO_ALIGN_LEFT, mEnemyAngularVelText.c_str());
			break;
		case COLLISION_BOXES:
			al_draw_text(gpGame->getFont(), MAGENTA, 5, 60, ALLEGRO_ALIGN_LEFT, mCollisionDebugText.c_str());
			break;
		case ALIGNMENT_WEIGHT:
			al_draw_text(gpGame->getFont(), MAGENTA, 5, 80, ALLEGRO_ALIGN_LEFT, mAlignmentWeightText.c_str());
			break;
		case COHESION_WEIGHT:
			al_draw_text(gpGame->getFont(), MAGENTA, 5, 100, ALLEGRO_ALIGN_LEFT, mCohesionWeightText.c_str());
			break;
		case SEPERATION_WEIGHT:
			al_draw_text(gpGame->getFont(), MAGENTA, 5, 120, ALLEGRO_ALIGN_LEFT, mSeperationWeightText.c_str());
			break;
		}
		
	}
}

void StateManager::addToAnEnemyStat()
{
	if (mActive)
	{
		std::stringstream ss;

		switch (mState)
		{
		case VELOCITY:
			*mpEnemyVel += 10.0f;
			ss << std::fixed << std::setprecision(1) << *mpEnemyVel;
			mEnemyVelText = "[V] Enemy Velocity: " + ss.str();
			ss.str(std::string());
			break;
		case RADIUS:
			*mpEnemyRadius += 10.0f;
			ss << std::fixed << std::setprecision(1) << *mpEnemyRadius;
			mEnemyRadiusText = "[R] Enemy Reaction Radius: " + ss.str();
			ss.str(std::string());
			break;
		case ANGULAR:
			*mpEnemyAngularVel += 5.0f;
			ss << std::fixed << std::setprecision(1) << *mpEnemyAngularVel;
			mEnemyAngularVelText = "[E] Enemy Angular Velocity: " + ss.str();
			ss.str(std::string());
			break;
		case COLLISION_BOXES:
			*mpShowCollisionBoxes = true;
			mCollisionDebugText = "[B] Collision Debug: On";
			break;
		case ALIGNMENT_WEIGHT:
			*mpAlignmentWeight += 0.5f;
			ss << std::fixed << std::setprecision(1) << *mpAlignmentWeight;
			mAlignmentWeightText = "[A] Alignment Weight: " + ss.str();
			ss.str(std::string());
			break;
		case COHESION_WEIGHT:
			*mpCohesionWeight += 0.5f;
			ss << std::fixed << std::setprecision(1) << *mpCohesionWeight;
			mCohesionWeightText = "[C] Cohesion Weight: " + ss.str();
			ss.str(std::string());
			break;
		case SEPERATION_WEIGHT:
			*mpSeperationWeight += 0.5f;
			ss << std::fixed << std::setprecision(1) << *mpSeperationWeight;
			mSeperationWeightText = "[S] Seperation Weight: " + ss.str();
			ss.str(std::string());
			break;
		}
	}
}

void StateManager::subtractFromAnEnemyStat()
{
	if (mActive)
	{
		std::stringstream ss;

		switch (mState)
		{
		case VELOCITY:
			*mpEnemyVel -= 10.0f;
			ss << std::fixed << std::setprecision(1) << *mpEnemyVel;
			mEnemyVelText = "[V] Enemy Velocity: " + ss.str();
			ss.str(std::string());
			break;
		case RADIUS:
			*mpEnemyRadius -= 10.0f;
			ss << std::fixed << std::setprecision(1) << *mpEnemyRadius;
			mEnemyRadiusText = "[R] Enemy Reaction Radius: " + ss.str();
			ss.str(std::string());
			break;
		case ANGULAR:
			*mpEnemyAngularVel -= 5.0f;
			ss << std::fixed << std::setprecision(1) << *mpEnemyAngularVel;
			mEnemyAngularVelText = "[E] Enemy Angular Velocity: " + ss.str();
			ss.str(std::string());
		case COLLISION_BOXES:
			*mpShowCollisionBoxes = false;
			mCollisionDebugText = "[B] Collision Debug: Off";
			break;
		case ALIGNMENT_WEIGHT:
			*mpAlignmentWeight -= 0.5f;
			ss << std::fixed << std::setprecision(1) << *mpAlignmentWeight;
			mAlignmentWeightText = "[A] Alignment Weight: " + ss.str();
			ss.str(std::string());
			break;
		case COHESION_WEIGHT:
			*mpCohesionWeight -= 0.5f;
			ss << std::fixed << std::setprecision(1) << *mpCohesionWeight;
			mCohesionWeightText = "[C] Cohesion Weight: " + ss.str();
			ss.str(std::string());
			break;
		case SEPERATION_WEIGHT:
			*mpSeperationWeight -= 0.5f;
			ss << std::fixed << std::setprecision(1) << *mpSeperationWeight;
			mSeperationWeightText = "[S] Seperation Weight: " + ss.str();
			ss.str(std::string());
			break;
		}
	}
}

void StateManager::setState(ManagerState state)
{
	if (mActive)
	{
		mState = state;
	}
}

void StateManager::saveData()
{
	std::ofstream saveFile;
	saveFile.open("SaveData.txt");
	saveFile << *mpAlignmentWeight << std::endl
		<< *mpCohesionWeight << std::endl
		<< *mpSeperationWeight << std::endl;
	saveFile.close();
}
