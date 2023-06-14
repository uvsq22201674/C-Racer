#ifndef GAME_USER_INTERFACE_H_INCLUDED
#define GAME_USER_INTERFACE_H_INCLUDED

#include "user_interface.h"
#include "car.h"

void SetValue(int * var, int val1)
{
		*var = val1;
}

void CreateGameUserInterface(UserInterface * to_return, Texture2D * button_texture, int * exit_var, Car * car)
{
	Button play = CreateButton("   Pause", (Vector2){650, 700}, (Vector2){100, 40}, button_texture, (Rectangle){0, 0, 17, 6}, (Rectangle){0, 6, 17, 6}, &SetValue, &to_return->current_menu, 1);
	AddButtonTo(to_return->menus, play);

	Menu pause  = CreateMenu("Pause", Normal);
	AddButtonTo(&pause, CreateButton("       Car",   (Vector2){200, 190}, (Vector2){400, 80}, button_texture, (Rectangle){0, 0, 17, 6}, (Rectangle){0, 6, 17, 6}, &SetValue, &to_return->current_menu, 2));
	AddButtonTo(&pause, CreateButton("      Host",   (Vector2){200, 280}, (Vector2){400, 80}, button_texture, (Rectangle){0, 0, 17, 6}, (Rectangle){0, 6, 17, 6}, &SetValue, &to_return->current_menu, 1));
	AddButtonTo(&pause, CreateButton("      Join",   (Vector2){200, 370}, (Vector2){400, 80}, button_texture, (Rectangle){0, 0, 17, 6}, (Rectangle){0, 6, 17, 6}, &SetValue, &to_return->current_menu, 1));
	AddButtonTo(&pause, CreateButton("    Resume",   (Vector2){200, 460}, (Vector2){400, 80}, button_texture, (Rectangle){0, 0, 17, 6}, (Rectangle){0, 6, 17, 6}, &SetValue, &to_return->current_menu, 0));
	AddButtonTo(&pause, CreateButton("      Quit",   (Vector2){200, 700}, (Vector2){400, 80}, button_texture, (Rectangle){0, 0, 17, 6}, (Rectangle){0, 6, 17, 6}, &SetValue, exit_var, 0));
	AddMenuTo(to_return, pause);
	to_return->current_menu = 1u;

	Menu car_skin = CreateMenu("Car", Normal);
	AddButtonTo(&car_skin, CreateButton("Classic", (Vector2){200, 100}, (Vector2){400, 80}, button_texture, (Rectangle){0, 0, 17, 6}, (Rectangle){0, 6, 17, 6}, &SetValue, (int*) &car->type, Classic));
	AddButtonTo(&car_skin, CreateButton("Formule 1", (Vector2){200, 190}, (Vector2){400, 80}, button_texture, (Rectangle){0, 0, 17, 6}, (Rectangle){0, 6, 17, 6}, &SetValue, (int*) &car->type, Formule1));
	AddButtonTo(&car_skin, CreateButton("Beetle", (Vector2){200, 280}, (Vector2){400, 80}, button_texture, (Rectangle){0, 0, 17, 6}, (Rectangle){0, 6, 17, 6}, &SetValue, (int*) &car->type, Beetle));
	AddButtonTo(&car_skin, CreateButton("Zoe", (Vector2){200, 370}, (Vector2){400, 80}, button_texture, (Rectangle){0, 0, 17, 6}, (Rectangle){0, 6, 17, 6}, &SetValue, (int*) &car->type, Zoe));
	AddButtonTo(&car_skin, CreateButton("    Go back", (Vector2){200, 700}, (Vector2){400, 80}, button_texture, (Rectangle){0, 0, 17, 6}, (Rectangle){0, 6, 17, 6}, &SetValue, &to_return->current_menu, 1));
	AddMenuTo(to_return, car_skin);

};

#endif