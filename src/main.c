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

	int state = 1;
	int running = 1;
	
	void change_menu(int arg)
	{
		state = arg;
	}
	void stopRunning(int arg)
	{
		running = 0;
	}

	int * changing_key = NULL;
	
	
	void set_car_classic(int arg)
	{
		test.type = Classic;
	}
	void set_car_formule1(int arg)
	{
		test.type = Formule1;
	}
	void set_car_beetle(int arg)
	{
		test.type = Beetle;
	}
	void set_car_zoe(int arg)
	{
		test.type = Zoe;
	}

	Texture2D button_texture = LoadTexture("img/button.png");

	Menu pause  = CreateMenu("Pause", Normal);
	AddButtonTo(&pause, CreateButton("   Controls",  (Vector2){200, 100}, (Vector2){400, 80}, &button_texture, (Rectangle){0, 0, 17, 6}, (Rectangle){0, 6, 17, 6}, &change_menu, 2));
	AddButtonTo(&pause, CreateButton("       Car",  (Vector2){200, 190}, (Vector2){400, 80}, &button_texture, (Rectangle){0, 0, 17, 6}, (Rectangle){0, 6, 17, 6}, &change_menu, 3));
	AddButtonTo(&pause, CreateButton("      Host",   (Vector2){200, 280}, (Vector2){400, 80}, &button_texture, (Rectangle){0, 0, 17, 6}, (Rectangle){0, 6, 17, 6}, &change_menu, 1));
	AddButtonTo(&pause, CreateButton("      Join",   (Vector2){200, 370}, (Vector2){400, 80}, &button_texture, (Rectangle){0, 0, 17, 6}, (Rectangle){0, 6, 17, 6}, &change_menu, 1));
	AddButtonTo(&pause, CreateButton("    Resume",   (Vector2){200, 460}, (Vector2){400, 80}, &button_texture, (Rectangle){0, 0, 17, 6}, (Rectangle){0, 6, 17, 6}, &change_menu, 0));
	AddButtonTo(&pause, CreateButton("      Quit",   (Vector2){200, 700}, (Vector2){400, 80}, &button_texture, (Rectangle){0, 0, 17, 6}, (Rectangle){0, 6, 17, 6}, &stopRunning, 0));


	Menu bindings = CreateMenu("Bindings", KeyChange);
	AddButtonTo(&bindings, CreateButton("Forward", (Vector2){200, 100}, (Vector2){400, 80}, &button_texture, (Rectangle){0, 0, 17, 6}, (Rectangle){0, 6, 17, 6}, NULL, 0));
	AddButtonTo(&bindings, CreateButton("Backward", (Vector2){200, 190}, (Vector2){400, 80}, &button_texture, (Rectangle){0, 0, 17, 6}, (Rectangle){0, 6, 17, 6}, NULL, 0));
	AddButtonTo(&bindings, CreateButton("Left", (Vector2){200, 280}, (Vector2){400, 80}, &button_texture, (Rectangle){0, 0, 17, 6}, (Rectangle){0, 6, 17, 6}, NULL, 0));
	AddButtonTo(&bindings, CreateButton("Right", (Vector2){200, 370}, (Vector2){400, 80}, &button_texture, (Rectangle){0, 0, 17, 6}, (Rectangle){0, 6, 17, 6}, NULL, 0));
	AddButtonTo(&bindings, CreateButton("    Go back", (Vector2){200, 700}, (Vector2){400, 80}, &button_texture, (Rectangle){0, 0, 17, 6}, (Rectangle){0, 6, 17, 6}, &change_menu, 1));


	Menu car_skin = CreateMenu("Car", Normal);
	AddButtonTo(&car_skin, CreateButton("Classic", (Vector2){200, 100}, (Vector2){400, 80}, &button_texture, (Rectangle){0, 0, 17, 6}, (Rectangle){0, 6, 17, 6}, &set_car_classic, 0));
	AddButtonTo(&car_skin, CreateButton("Formule 1", (Vector2){200, 190}, (Vector2){400, 80}, &button_texture, (Rectangle){0, 0, 17, 6}, (Rectangle){0, 6, 17, 6}, &set_car_formule1, 0));
	AddButtonTo(&car_skin, CreateButton("Beetle", (Vector2){200, 280}, (Vector2){400, 80}, &button_texture, (Rectangle){0, 0, 17, 6}, (Rectangle){0, 6, 17, 6}, &set_car_beetle, 0));
	AddButtonTo(&car_skin, CreateButton("Zoe", (Vector2){200, 370}, (Vector2){400, 80}, &button_texture, (Rectangle){0, 0, 17, 6}, (Rectangle){0, 6, 17, 6}, &set_car_zoe, 0));
	AddButtonTo(&car_skin, CreateButton("    Go back", (Vector2){200, 700}, (Vector2){400, 80}, &button_texture, (Rectangle){0, 0, 17, 6}, (Rectangle){0, 6, 17, 6}, &change_menu, 1));


	UserInterface ui = CreateUserInterface();

	Button play = CreateButton("   Pause", (Vector2){650, 700}, (Vector2){100, 40}, &button_texture, (Rectangle){0, 0, 17, 6}, (Rectangle){0, 6, 17, 6}, &change_menu, 1);
	AddButtonTo(ui.menus, play);

	AddMenuTo(&ui, pause);
	AddMenuTo(&ui, bindings);
	void change_key(int arg)
	{
		switch(arg)
		{
		case 0:
			ui.menus[2].changing_value = &test.controls.accelerate;
		break;
		case 1:
			ui.menus[2].changing_value = &test.controls.decelerate;
		break;
		case 2:
			ui.menus[2].changing_value = &test.controls.turn_left;
		break;
		case 3:
			ui.menus[2].changing_value = &test.controls.turn_right;
		break;
		}
	}

	for(int i = 0; i < 4; i++)
	{
		ui.menus[ui.menus_count - 1].buttons[i].callback = &change_key;
		ui.menus[ui.menus_count - 1].buttons[i].arg = i;
	}

	AddMenuTo(&ui, car_skin);

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

		/*if(state != 1)
		{
			DrawRectangle(0, 0, 800, 800, (Color) {0, 0, 0, 100});
			
			if(state == 0)
			{
				UpdateMenu(pause);		
				DrawMenu(pause);
			}
			else if(state == 2)
			{
				UpdateMenu(bindings);
				DrawMenu(bindings);
				
				if(changing_key != NULL)
				{	
					int pressed = GetKeyPressed();
					if(pressed != 0)
					{
						*changing_key = pressed;
						changing_key = NULL;
					}

				}	
			}
			else if(state == 3)
			{
				UpdateMenu(car_skin);
				DrawMenu(car_skin);	
			}
		}
		else
		{
			UpdateButton(&play);
			DrawButton(&play);
		}*/
		ui.current_menu = state;
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
