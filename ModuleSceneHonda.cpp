#include "Globals.h"
#include "Application.h"
#include "ModuleSceneKen.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"
#include "ModuleSceneHonda.h"


ModuleSceneHonda::ModuleSceneHonda(bool start_enabled) : Module(start_enabled)
{
	// ground
	ground.x = 120;
	ground.y = 377;
	ground.w = 656;
	ground.h = 63;

	// Background / wall
	wall.x = 205;
	wall.y = 175;
	wall.w = 579;
	wall.h = 130;

	// ROOF
	roof.x = 91;
	roof.y = 8;
	roof.w = 766;
	roof.h = 49;

	//DOOR
	door.x = 127;
	door.y = 130;
	door.w = 77;
	door.h = 200;

	//poolbase
	poolbase.x = 311;
	poolbase.y = 336;
	poolbase.w = 337;
	poolbase.h = 32;

	//pooltop
	pooltop.x = 311;
	pooltop.y = 312;
	pooltop.w = 337;
	pooltop.h = 20;

	/*
	SDL_Rect picture;*/
}


ModuleSceneHonda::~ModuleSceneHonda()
{

}

bool ModuleSceneHonda::Start()
{
	LOG("Loading Honda scene");

	graphics = App->textures->Load("honda_stage.png");
	App->audio->PlayMusic("../Game/honda.ogg", 0);

	App->player->Init();
	App->player->Start();

	return true;

}

update_status ModuleSceneHonda::Update()
{
	// Draw everything --------------------------------------
	if (App->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN) {
		CleanUp();
		App->fade->Start();
		App->fade->FadeToBlack((Module*)App->scene_ken, this, 0.95f);
		App->player->Start();
		return UPDATE_CONTINUE;
	}

	App->renderer->Blit(graphics,-1, 160, &ground, 3.0f); 
	App->renderer->Blit(graphics, 76, 31, &wall, 3.0f);	
	App->renderer->Blit(graphics, -1, -10, &door, 3.0f);
	App->renderer->Blit(graphics, 200, 125, &pooltop, 3.0f);
	App->renderer->Blit(graphics, 200, 145, &poolbase, 3.0f);
	App->renderer->Blit(graphics, -57, -16, &roof, 3.0f);
	App->player->Update();

	return UPDATE_CONTINUE;
}

bool ModuleSceneHonda::CleanUp()
{
	LOG("Unloading ken scene");

	App->textures->Unload(graphics);
	App->player->Disable();

	return true;
}
