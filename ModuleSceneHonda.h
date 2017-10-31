#ifndef __MODULESCENEHONDA_H__
#define __MODULESCENEHONDA_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleSceneHonda : public Module
{
public:
	ModuleSceneHonda(bool start_enabled = true);
	~ModuleSceneHonda();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect ground;
	SDL_Rect wall;
	SDL_Rect door;
	SDL_Rect roof;
	SDL_Rect poolbase;
	SDL_Rect pooltop;
	SDL_Rect picture;
	
};

#endif // __MODULESCENEHONDA_H__