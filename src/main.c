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
	if (settings.enabledVSync) SetTargetFPS(60); else SetTargetFPS(0);
	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");
	
	
	
	// Load a texture from the resources directory
	Texture wabbit = LoadTexture("wabbit_alpha.png");
	Vector2 player = { 0.0f, (float)settings.screenHeight/2 - (float)wabbit.height/2 };
	
	Texture house = LoadTexture("house_1_floor_planes_example.png");
	Vector2 house_1 = { 0.0f, (float)settings.screenHeight/2 - (float)house.height/2 };
	
	// Camera setup
	Camera2D camera = { 0 };
    camera.target = (Vector2){ player.x + 20.0f, player.y + 20.0f };
    camera.offset = (Vector2){ settings.screenWidth/2.0f, settings.screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
	
	// Set the target FPS
	int fps = 0;
	float speed = 250;

	// Get the mouse cursor
	int cursor_x = GetMouseX();
	int cursor_y = GetMouseY();
	
	// Game Loop
	// run the loop until the user presses ESCAPE or presses the Close button on the window
	while (!WindowShouldClose())
	{
		// player input
		player = input(player, speed);
		camera.target = (Vector2){ player.x + 20, player.y + 20 };

		// drawing
		BeginDrawing();

			// Setup the back buffer for drawing (clear color and depth buffers)
			ClearBackground(BLACK);

			// draw some text using the default font			
			if (settings.enabledDebug){
				fps =  GetFPS();
				DrawText(TextFormat("FPS: %d",fps), 20,20,20,WHITE);
				DrawText(TextFormat("Speed: %.0f",speed), 20,40,20,WHITE);
				cursor_x = GetMouseX();
				cursor_y = GetMouseY();
				DrawText(TextFormat("Cursor x,y: %d,%d",cursor_x,cursor_y), 20,60,20,WHITE);
			}
			
			// Camera target follows player


			// draw our texture to the screen
			DrawTexture(house, house_1.x+600, house_1.y, WHITE);
			DrawTexture(wabbit, player.x,player.y, WHITE);

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
