#ifndef CIRCUIT_VIEW_H_INCLUDED
#define CIRCUIT_VIEW_H_INCLUDED

#include <raylib.h>
#include "circuit_model.h"

typedef struct
{
	Vector2 * points;
	unsigned int point_count;
	float width;
} CircuitView;


CircuitView CreateCircuitView(CircuitBone const model, float width)
{

	CircuitView to_return;
	to_return.points = malloc(sizeof(Vector2) * 2);
	to_return.point_count = 2;
	to_return.width = width;

	for(int i = 0; i < 2; i++)
		to_return.points[i] = model.start->position;

	Checkpoint * current = model.start;
	Checkpoint * next    = model.start->next;

	do
	{
		to_return.point_count += 2;
		to_return.points = realloc(to_return.points, sizeof(Vector2) * to_return.point_count);

		to_return.points[to_return.point_count - 2] = (Vector2){current->position.x, current->position.y};
		to_return.points[to_return.point_count - 1] = (Vector2){next->position.x, next->position.y};

		/*printf("%f;%f\n", to_return.points[3].x, to_return.points[3].y);
		printf("%f;%f\n", to_return.points[4].x, to_return.points[4].y);
		printf("%f;%f\n", to_return.points[5].x, to_return.points[5].y);
		printf("%s\n", "____________________________");*/


		current = next;
		next = next->next;
	}while(current != model.start);

	/*for(int i = 2; i < to_return.point_count; i+=2)
	{
		printf("%f;%f\n", to_return.points[i].x, to_return.points[i].y);
		printf("%f;%f\n", to_return.points[i+1].x, to_return.points[i+1].y);
		printf("____________\n");
		
	}*/

	return to_return;
}
void DrawCircuit(CircuitView const arg)
{
	for(int i = 2; i < arg.point_count; i+=2)
	{
		DrawLineEx(arg.points[i], arg.points[i+1], arg.width, BLUE);
	}
}

void DestroyCircuitView(CircuitView view)
{
	free(view.points);
}

#endif