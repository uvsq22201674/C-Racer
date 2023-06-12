
#ifndef WIDGETS_H_INCLUDED
#define WIDGETS_H_INCLUDED

#include <raylib.h>

typedef struct
{
	char * text;
	Vector2 pos;
	Vector2 size;

	Texture2D * sprite;
	Rectangle rest;
	Rectangle activation;

	void (*callback) (int);
	int arg;

	// Internal use only

	int activated;
	int hovered;
	int cooldown;
} Button;

Button CreateButton(char * text, Vector2 pos, Vector2 size, Texture2D * sprite, Rectangle rest, Rectangle activation, void (*callback) (int), int arg)
{
	return (Button) {
		text,
		pos,
		size,
		sprite,
		rest,
		activation,
		callback,
		arg,
		0,
		0,
		0
	};
}
void UpdateButton(Button * b)
{
	if(b->activated)
	{
		b->cooldown -= 1;
		if(b->cooldown <= 0)
		{
			b->activated = 0;
			(*b->callback) (b->arg);
		}
	}

	Vector2 mouse = GetMousePosition();

	int mouse_in = (mouse.x >= b->pos.x 
				 && mouse.y >= b->pos.y
				 && mouse.x <= b->pos.x + b->size.x 
				 && mouse.y <= b->pos.y + b->size.y);

	if(mouse_in && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		b->activated = 1;
		b->cooldown = 10;
	}
	if(mouse_in)
	{
		b->hovered = 1;
	}
}
void DrawButton(Button * b)
{
	Rectangle source = b->rest;
	int text_offset = 0;
	if(b->activated)
	{
		source = b->activation;
		text_offset = 10;
	}

	Color color = {255, 255, 255, 255};
	if(b->hovered)
	{
		color = (Color) {100, 100, 100, 255};
		b->hovered = 0;
	}

	DrawTexturePro(*b->sprite, source, (Rectangle) {b->pos.x + b->size.x/2.f, b->pos.y + b->size.y/2.f, b->size.x, b->size.y}, Vector2Scale(b->size, 0.5f), 0, color);
	DrawText(b->text, b->pos.x + 10, b->pos.y + 10 + text_offset, b->size.y - 25, BLACK);
}

#endif