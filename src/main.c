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
#include "menu.h"
#include "user_interface.h"
#include "game_user_interface.h"

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

	int running = 1;	

	Texture2D button_texture = LoadTexture("img/button.png");

	UserInterface ui = CreateUserInterface();
	CreateGameUserInterface(&ui, &button_texture, &running, &test);


	int frame = 0;
	while(!WindowShouldClose() && running)
	{
		BeginDrawing();
		ClearBackground((Color) {150, 150, 150, 255});

		if(ui.current_menu == 0)
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

		UpdateUserInterface(ui);
		DrawUserInterface(ui);

		EndDrawing();

	}

	DestroyUserInterface(ui);
	DestroyCircuitView(circuit);
	DestroyCircuitBone(model);

	UnloadTexture(button_texture);
	UnloadTexture(spritesheet);

	CloseWindow();

	return EXIT_SUCCESS;
}
