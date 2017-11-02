#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA
ModulePlayer::ModulePlayer(bool start_enabled) : Module(start_enabled)
{
	position.x = 120;
	position.y = 120;


	// idle animation (arcade sprite sheet)
	idle.frames.push_back({7, 14, 60, 90});
	idle.frames.push_back({95, 15, 60, 89});
	idle.frames.push_back({184, 14, 60, 90});
	idle.frames.push_back({276, 11, 60, 93});
	idle.frames.push_back({366, 12, 60, 92});
	idle.speed = 0.2f;
	
	// walk backward animation (arcade sprite sheet)
	backward.frames.push_back({542, 131, 61, 87});
	backward.frames.push_back({628, 129, 59, 90});
	backward.frames.push_back({713, 128, 57, 90});
	backward.frames.push_back({797, 127, 57, 90});
	backward.frames.push_back({883, 128, 58, 91});
	backward.frames.push_back({974, 129, 57, 89});
	backward.speed = 0.2f;

	// TODO 8: setup the walk forward animation from ryu4.png
	forward.frames.push_back({ 9, 136, 53, 85 });
	forward.frames.push_back({ 78, 131, 62, 90 });
	forward.frames.push_back({ 162, 128, 65, 94 });
	forward.frames.push_back({ 259, 128, 62, 94 });
	forward.frames.push_back({ 352, 128, 55, 94 });
	forward.frames.push_back({ 432, 131, 50, 91 });
	forward.speed = 0.2f;

	//up jum animation
	jump.frames.push_back({ 16,846,55,87 });
	jump.frames.push_back({ 100,822,60,106 });
	jump.frames.push_back({ 174,804,61,89 });
	jump.frames.push_back({ 249,797,56,78 });
	jump.frames.push_back({ 325,812,50,71 });
	jump.frames.push_back({ 396,809,49,90 });
	jump.frames.push_back({ 463,818,57,111 });
	jump.frames.push_back({ 16,846,55,87 });
	jump.speed = 0.1f;

	currentAnimation = &idle;
}

ModulePlayer::~ModulePlayer()
{
	// Homework : check for memory leaks
}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("ryu4.png"); // arcade version

	App->renderer->Blit(graphics, position.x, position.y, (&currentAnimation->GetCurrentFrame()), 1.0f);

	referenceDrawPosition.x = position.x + currentAnimation->frames[currentAnimation->getPosCurrentFrame()].w / 2;
	referenceDrawPosition.y = position.y + currentAnimation->frames[currentAnimation->getPosCurrentFrame()].h;
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update
update_status ModulePlayer::Update()
{
	// TODO 9: Draw the player with its animation  make sure to detect player movement and change its
	// position while cycling the animation(check Animation.h)

	// First we check "special movement" as jump, bend, etc
	if (jumpSt.jumping) {
		referenceDrawPosition.y -= jumpSt.jumpingMove*jumpSt.jumpingOrientation;
		// Player will ascend half way and descend the other half (if jump frames animation has a pair number of frames)
		if (currentAnimation->getPosCurrentFrameFloat() + currentAnimation->speed > currentAnimation->frames.size() / 2 && jumpSt.jumpingOrientation>0) {
			jumpSt.jumpingOrientation *= -1;
		}
 		if (currentAnimation->getPosCurrentFrameFloat() + currentAnimation->speed >= currentAnimation->frames.size()) {
			referenceDrawPosition.y -= jumpSt.jumpingMove*jumpSt.jumpingOrientation;
			jumpSt.jumping = false;
			jumpSt.jumpingOrientation *= -1;
		}

	}

	// In any case we check if any key was pushed this frame and also apply horizontal move logical if thats the case, and we use its animation but when any special move is currently activated
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
		if (position.x >= 1) {
			referenceDrawPosition.x -= 1;
		}
		if (!jumpSt.jumping) {
			currentAnimation = &backward;
		}
	}else if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
		if (position.x <= 450) {		
			referenceDrawPosition.x += 1;
		}
		if (!jumpSt.jumping) {
			currentAnimation = &forward;
		}
		
	}
	else if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
		jumpSt.jumping = true;
		currentAnimation = &jump;
	}
	else {
		if (jumpSt.jumping == false)
		currentAnimation = &idle;
	}

	// We use this method only once before the animation drawing to apply the speed over the frames list just once per frame
	currentAnimation->GetCurrentFrame();

	
	position.x = referenceDrawPosition.x - currentAnimation->frames[currentAnimation->getPosCurrentFrame()].w / 2;
	position.y = referenceDrawPosition.y - currentAnimation->frames[currentAnimation->getPosCurrentFrame()].h;
	
   	App->renderer->Blit(graphics, position.x, position.y,&currentAnimation->frames[currentAnimation->getPosCurrentFrame()], 1.0f);
	referenceDrawPosition.x = position.x + currentAnimation->frames[currentAnimation->getPosCurrentFrame()].w / 2;
	referenceDrawPosition.y = position.y + currentAnimation->frames[currentAnimation->getPosCurrentFrame()].h;	

	return UPDATE_CONTINUE;
}