#include <raylib.h>
#include <stdlib.h>
#include <raymath.h>
#include <stdio.h>
#include "circuit_model.h"
#include "circuit_view.h"

int main()
{

	InitWindow(800, 800, "Circuit Editor");
	SetTargetFPS(60);
	SetWindowState(FLAG_VSYNC_HINT);

	CircuitBone test = CreateCircuitBone((Vector2) {50.f, 75.f});

	CircuitView test1 = CreateCircuitView(test, 30.f);

	Camera2D cam = {0};
	cam.zoom = 1.f;

	while(!WindowShouldClose())
	{

		if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
			cam.target = Vector2Subtract(cam.target, Vector2Scale(GetMouseDelta(), 1.f/cam.zoom));

		cam.zoom += GetMouseWheelMove() * 0.1f;


		if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			AddCheckpointTo(&test, GetScreenToWorld2D(GetMousePosition(), cam));
			DestroyCircuitView(test1);
			test1 = CreateCircuitView(test, 30.f);
		}
		if(IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_S))
		{
			FILE * save = fopen("save.txt", "w");
			if(save != NULL)
			{
				Checkpoint * drawing = test.start;
				do
				{

					fprintf(save, "%d;%d\n", (int) drawing->position.x, (int) drawing->position.y);

					drawing = drawing->next;
				}while(drawing != test.start);
			}
			fclose(save);
		}

		BeginDrawing();
		BeginMode2D(cam);
			ClearBackground(BLACK);

			DrawText("Click !", 0, 0, 48, BLUE);

			DrawCircuit(test1);

			Checkpoint * drawing = test.start;
			do
			{

				DrawCircle(drawing->position.x, drawing->position.y, 5, RED);

				drawing = drawing->next;
			}while(drawing != test.start);

		EndMode2D();
		EndDrawing();
	}

	DestroyCircuitView(test1);
	DestroyCircuitBone(test);

	CloseWindow();

	return EXIT_SUCCESS;
}