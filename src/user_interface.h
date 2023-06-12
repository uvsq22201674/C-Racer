#ifndef USER_INTERFACE_H_INCLUDED
#define USER_INTERFACE_H_INCLUDED

#include <raylib.h>
#include "menu.h"

typedef struct
{

	Menu * menus;
	unsigned int menus_count;
	unsigned int current_menu;

} UserInterface;

UserInterface CreateUserInterface()
{
	Menu * menu = malloc(sizeof(Menu));
	*menu = CreateMenu("Game", Normal);

	return (UserInterface) {
		menu,
		1u,
		0u
	};
}
void AddMenuTo(UserInterface * ui, Menu m)
{
	ui->menus_count ++;
	ui->menus = realloc(ui->menus, ui->menus_count * sizeof(Menu));
	ui->menus[ui->menus_count - 1] = m;
	if(ui->menus[ui->menus_count - 1].type != Normal)
		printf("%s\n", "Bitches be hating");
}
void UpdateUserInterface(UserInterface ui)
{
	UpdateMenu(ui.menus[ui.current_menu]);


	int pressed = 0;
	if(ui.menus[ui.current_menu].type == KeyChange
	&& ui.menus[ui.current_menu].changing_value != NULL
	&& (pressed = GetKeyPressed()) != 0)
	{
		*ui.menus[ui.current_menu].changing_value = pressed;
		ui.menus[ui.current_menu].changing_value = NULL;
	}
}
void DrawUserInterface(UserInterface ui)
{
	if(ui.current_menu != 0)
		DrawRectangle(0, 0, 800, 800, (Color) {0, 0, 0, 100});
	DrawMenu(ui.menus[ui.current_menu]);

	if(ui.menus[ui.current_menu].type == KeyChange
	&& ui.menus[ui.current_menu].changing_value != NULL)
		DrawText("Press a key", 10, 10, 48, RED);
}

void DestroyUserInterface(UserInterface ui)
{
	for(int i = 0; i < ui.menus_count; i++)
	{
		DestroyMenu(ui.menus[i]);
	}

	free(ui.menus);
}


#endif