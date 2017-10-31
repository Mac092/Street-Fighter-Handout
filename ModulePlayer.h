#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Point.h"

struct SDL_Texture;

struct JumpSt {
	bool jumping = false;
	int jumpingOrientation = 1;
	int jumpingMove = 2;
	//bool higherPointReached = false;
	//bool landReached = false;
};

class ModulePlayer : public Module
{
public:
	ModulePlayer(bool start_enabled = true);
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	Animation idle;
	Animation backward;
	Animation forward;
	Animation jump;
	iPoint position;
	Animation *currentAnimation = nullptr;
	
	JumpSt jumpSt;
	SDL_Rect *lastFrame = nullptr;
	
	
};

#endif // __MODULEPLAYER_H__