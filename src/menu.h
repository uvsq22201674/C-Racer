#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include "widgets.h"


typedef struct
{
	char * name;
	
	Button * buttons;
	unsigned int buttons_count;
} Menu;

Menu CreateMenu(char * name)
{
	return (Menu) {
		name,
		NULL,
		0u
	};
}
void AddButtonTo(Menu * m, Button b)
{
	m->buttons_count ++;

	if(m->buttons_count == 1u)
	{
		m->buttons = malloc(sizeof(Button));
	}
	else
	{
		m->buttons = realloc(m->buttons, m->buttons_count * sizeof(Button));
	}
	
	m->buttons[m->buttons_count - 1] = b;
}
void UpdateMenu(Menu m)
{
	for(int i = 0; i < m.buttons_count; i++)
	{
		UpdateButton(&m.buttons[i]);
	}
}
void DrawMenu(Menu m)
{
	for(int i = 0; i < m.buttons_count; i++)
	{
		DrawButton(&m.buttons[i]);
	}
}
void DestroyMenu(Menu m)
{
	free(m.buttons);
}



#endif