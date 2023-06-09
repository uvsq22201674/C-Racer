#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include <raymath.h>
#include <time.h>
#include <math.h>
#include "../Circuit Editor/src/circuit_model.h"
#include "../Circuit Editor/src/circuit_view.h"
#include "car.h"
#include "carcamera.h"
#include "widgets.h"

int main()
{
	srand(time(NULL));

	InitWindow(800, 800, "Course !");
	SetTargetFPS(60);
	SetWindowState(FLAG_VSYNC_HINT);
	SetExitKey(KEY_NULL);

	Texture2D spritesheet = LoadTexture("img/spritesheet.png");
	
	Camera2D cam = {0};
	cam.zoom = 1.f;

	CircuitBone model = CreateCircuitBone((Vector2){50, 75});

	FILE * save = fopen("Circuit Editor/save.txt", "r ");

	if(save != NULL)
	{
		fseek(save, 0L, SEEK_END);
	
		unsigned int char_count = ftell(save);
		char * data = malloc(char_count);
		rewind(save);
		fread(data, char_count, char_count, save);

		char x_buffer[9] = {0};
		char y_buffer[9] = {0};
		int state = 0;
		unsigned int index = 0u;
		for(int i = 0; i < char_count; i++)
		{
			if(data[i] == '\n')
			{
				AddCheckpointTo(&model, (Vector2) {strtol(x_buffer, NULL, 10), strtol(y_buffer, NULL, 10)});
				
				for(int j = 0; j < 9; j++)
				{
					x_buffer[j] = 0;
					y_buffer[j] = 0;
				}
				state = 0;
				index = 0u;
			}
			else if(data[i] == ';')
			{
				state = 1;
				index = 0;
			}
			else if(state)
			{
				y_buffer[index] = data[i];
				index ++;
			}
			else
			{
				x_buffer[index] = data[i];
				index ++;
			}
		}

		free(data);
	}

	fclose(save);


	CircuitView circuit = CreateCircuitView(model, 200.f);

	Car test = CreateCar((CarType) rand()%4, &spritesheet);

	int state = 0;
	int running = 1;
	void playPause()
	{
		if(state)
			state=0;
		else
			state=1;
	}
	void openKeyMenu()
	{
		state = 2;
	}
	void stopRunning()
	{
		running = 0;
	}
	Texture2D button_texture = LoadTexture("img/button.png");
	Button play = CreateButton("Play/Pause", (Vector2){650, 700}, (Vector2){100, 40}, &button_texture, (Rectangle){0, 0, 17, 6}, (Rectangle){0, 6, 17, 6}, &playPause);

	Button quit     = CreateButton("      Quit",   (Vector2){200, 100}, (Vector2){400, 80}, &button_texture, (Rectangle){0, 0, 17, 6}, (Rectangle){0, 6, 17, 6}, &stopRunning);
	Button controls = CreateButton("   Controls", (Vector2){200, 190}, (Vector2){400, 80}, &button_texture, (Rectangle){0, 0, 17, 6}, (Rectangle){0, 6, 17, 6}, &openKeyMenu);

	int frame = 0;
	while(!WindowShouldClose() && running)
	{
		BeginDrawing();
		ClearBackground((Color) {150, 150, 150, 255});

		if(state == 1)
		{
			frame ++;

			UpdateCar(&test);
			UpdateCarCamera(&cam, test); 
		}

		BeginMode2D(cam);
				
			DrawCircuit(circuit);

			DrawCar(test);

			EndMode2D();

		DrawFPS(10, 10);

		if(state == 0)
		{
			DrawRectangle(0, 0, 800, 800, (Color) {0, 0, 0, 100});
			
			UpdateButton(&quit);
			UpdateButton(&controls);

			DrawButton(&quit);
			DrawButton(&controls);
		}

		UpdateButton(&play);
		DrawButton(&play);
		EndDrawing();

	}

	DestroyCircuitView(circuit);
	DestroyCircuitBone(model);

	UnloadTexture(button_texture);
	UnloadTexture(spritesheet);

	CloseWindow();

	return EXIT_SUCCESS;
}