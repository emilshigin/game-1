/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include "lua_interface.h"	// Lua integration for settings

Vector2 input(Vector2 position, float speed)
{
 // Update
	if(IsKeyDown(KEY_W)){
		position.y -= speed * GetFrameTime();
	}
	if(IsKeyDown(KEY_S)){
		position.y += speed * GetFrameTime();
	}
	if(IsKeyDown(KEY_A)){
		position.x -= speed * GetFrameTime();
	}
	if(IsKeyDown(KEY_D)){
		position.x += speed * GetFrameTime();
	}
	return position;
}

int main ()
{
	// Initialize Lua
	lua_State* L = Lua_Init();

	// Load settings from Lua
	GameSettings settings = Lua_LoadSettings(L, "resources/settings.lua");

	// Create the window with Lua settings
	InitWindow(settings.screenWidth, settings.screenHeight, "Game 1");
	SetTargetFPS(settings.targetFPS);

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Load a texture from the resources directory
	Texture wabbit = LoadTexture("wabbit_alpha.png");
	Vector2 position = { 0.0f, (float)settings.screenHeight/2 - (float)wabbit.height/2 };

	// Set the target FPS
	int fps = settings.targetFPS;
	
	// Game Loop
	// run the loop until the user presses ESCAPE or presses the Close button on the window
	while (!WindowShouldClose())
	{
		position = input(position, settings.playerSpeed);

		// drawing
		BeginDrawing();

			// Setup the back buffer for drawing (clear color and depth buffers)
			ClearBackground(BLACK);

			// Get FPS
			fps =  GetFPS();

			// draw some text using the default font
			DrawText("Game Start", 200,200,20,WHITE);
			DrawText(TextFormat("FPS: %d",fps), 200,240,20,WHITE);
			DrawText(TextFormat("Speed: %.0f",settings.playerSpeed), 200,260,20,WHITE);

			// draw our texture to the screen
			DrawTexture(wabbit, position.x,position.y, WHITE);

		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(wabbit);

	// Cleanup Lua
	Lua_Cleanup(L);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
