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

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneKen::ModuleSceneKen(bool start_enabled) : Module(start_enabled)
{
	// ground
	ground.x = 8;
	ground.y = 391;
	ground.w = 896;
	ground.h = 72;

	// TODO 2 : setup the foreground (red ship) with
	// coordinates x,y,w,h from ken_stage.png
	foreground.x = 8;
	foreground.y = 24;
	foreground.w = 524;
	foreground.h = 194;
	
	// Background / sky
	background.x = 72;
	background.y = 208;
	background.w = 768;
	background.h = 176;

	// flag animation
	flag.frames.push_back({848, 208, 40, 40});
	flag.frames.push_back({848, 256, 40, 40});
	flag.frames.push_back({848, 304, 40, 40});
	flag.speed = 0.08f;

	// TODO 4: Setup Girl Animation from coordinates from ken_stage.png
	girl.frames.push_back({625,15,32,57});
	girl.frames.push_back({625,79,32,57});
	girl.frames.push_back({625,143,32,57});
	girl.speed = 0.025f;
	

}

ModuleSceneKen::~ModuleSceneKen()
{}

// Load assets
bool ModuleSceneKen::Start()
{
	LOG("Loading ken scene");
	
	graphics = App->textures->Load("ken_stage.png");
	// TODO 0: trigger background music
	//App->audio->Init(); In case the music doesn't work uncomment this line
	App->audio->PlayMusic("../Game/ken.ogg", 0);
	
	// TODO 7: Enable the player module
	App->player->Init();
	App->player->Start();
	
	return true;
}

// UnLoad assets
bool ModuleSceneKen::CleanUp()
{
	LOG("Unloading ken scene");

	App->textures->Unload(graphics);
	App->player->Disable();
	
	return true;
}

// Update: draw background
update_status ModuleSceneKen::Update()
{
	 //TODO 5: make sure the ship goes up and down

	if (frameCounter % 50 == 0)
	{
		if (positionShipY > -10 && positionShipY < 10) {
			
			positionShipY += shipYMovement;
			positionGirlY += shipYMovement;
		}
		else if (positionShipY >= 10) {
			positionShipY--;
			positionGirlY--;
		}
		else if (positionShipY <= -10) {
			positionShipY++;
			positionGirlY++;
		}
		shipYMovement *= -1;
	}
	frameCounter++;
		

	// Draw everything --------------------------------------
	// TODO 1: Tweak the movement speed of the sea&sky + flag to your taste
	App->renderer->Blit(graphics, 0, 0, &background, 3.0f); // sea and sky
	App->renderer->Blit(graphics, 560, 8, &(flag.GetCurrentFrame()), 3.0f); // flag animation

	// TODO 3: Draw the ship. Be sure to tweak the speed.
	App->renderer->Blit(graphics, 0, positionShipY, &foreground, 3.0f);

	// TODO 6: Draw the girl. Make sure it follows the ship movement!
	App->renderer->Blit(graphics, 0, 170, &ground, 3.0f);
	App->renderer->Blit(graphics, 193, positionGirlY, &(girl.GetCurrentFrame()), 3.0f);

	// TODO 10: Build an entire new scene "honda", you can find its
	// and music in the Game/ folder

	// TODO 11: Make that pressing space triggers a switch to honda logic module
	// using FadeToBlack module
	App->player->Update();
	return UPDATE_CONTINUE;
}