#ifndef CAR_H_INCLUDED
#define CAR_H_INCLUDED

#include <raylib.h>

typedef enum
{
	Classic  = 0,
	Formule1 = 1,
	Beetle = 2,
	Zoe = 3
} CarType;

typedef struct
{
	int accelerate;
	int decelerate;
	int turn_right;
	int turn_left;
} KeyBindings;

typedef struct
{
	float accelerating;
	float decelerating;
	float drifting;

} Friction;

typedef struct
{
	Texture2D * spritesheet;

	Vector2 pos;
	Vector2 size;
	Vector2 speed;
	float rotation;

	CarType type;

	float acceleration;
	float turn_speed;

	Friction friction;
	KeyBindings controls;


	// Internal use only

	bool drifting;
	unsigned int frame;

} Car;

Car CreateCar(CarType arg0, Texture2D * arg1)
{
	return (Car){
		arg1,
		(Vector2){0.f, 0.f},
		(Vector2){64.f, 64.f},
		(Vector2){0.f, 0.f},
		0.f,
		arg0,
		0.8f,
		3.f,
		(Friction){
			0.96f,
			0.99f,
			0.98f
		},
		(KeyBindings){
			KEY_UP,
			KEY_DOWN,
			KEY_RIGHT,
			KEY_LEFT
		},
		false,
		0u
	};
}

void UpdateCar(Car * car)
{

	// Acceleration/Deceleration
	if(IsKeyDown(car->controls.accelerate))
	{
		car->speed.x += car->acceleration * cos(car->rotation * 3.1416f/180.f);
		car->speed.y += car->acceleration * sin(car->rotation * 3.1416f/180.f);

		car->speed = Vector2Scale(car->speed, car->friction.accelerating);
	}else if(IsKeyDown(car->controls.decelerate))
	{
		car->speed.x -= car->acceleration * cos(car->rotation * 3.1416f/180.f);
		car->speed.y -= car->acceleration * sin(car->rotation * 3.1416f/180.f);
		
		car->speed = Vector2Scale(car->speed, car->friction.accelerating);
	}
	else
		car->speed = Vector2Scale(car->speed, car->friction.decelerating);
	
	// Stirring
	if(IsKeyDown(car->controls.turn_right))
		car->rotation += car->turn_speed;
	if(IsKeyDown(car->controls.turn_left))
		car->rotation -= car->turn_speed;

	// Drifting
	if(car->speed.x != 0 || car->speed.y != 0)
	{
		Vector2 direction = {cos(car->rotation * 3.1416f/180.f), sin(car->rotation * 3.1416f/180.f)};
		float speed_norm = sqrt(car->speed.x * car->speed.x + car->speed.y * car->speed.y);
		float teta = acos( (direction.x * car->speed.x + direction.y * car->speed.y)/speed_norm );

		if(teta > 3.1416f/4.f)
		{
			car->speed = Vector2Scale(car->speed, car->friction.drifting);
			car->drifting = true;
		}
		else
			car->drifting = false;
	}

	car->frame ++;
	car->frame%=60;
	car->pos = Vector2Add(car->pos, car->speed);
}

void DrawCar(Car car)
{
	DrawTexturePro(*car.spritesheet, (Rectangle) {2, 2 + 15 * (int) car.type, 13, 13}, (Rectangle) {car.pos.x, car.pos.y, car.size.x, car.size.y}, (Vector2){car.size.x/2.f, car.size.y/2.f}, car.rotation, WHITE);
			
	if(car.drifting)
	{
		DrawTexturePro(*car.spritesheet, (Rectangle){2 + 15 * (car.frame%3), 62, 13, 13}, (Rectangle) {car.pos.x + sin(car.rotation * 3.1416f/180.f) * car.size.y * 0.5f, car.pos.y - cos(car.rotation * 3.1416f/180.f) * car.size.y * 0.5f, car.size.x/2.f, car.size.y/2.f}, (Vector2){car.size.x/4.f, car.size.y/4.f}, 0, WHITE);
		DrawTexturePro(*car.spritesheet, (Rectangle){2 + 15 * (car.frame%3), 62, 13, 13}, (Rectangle) {car.pos.x - sin(car.rotation * 3.1416f/180.f) * car.size.y * 0.5f, car.pos.y + cos(car.rotation * 3.1416f/180.f) * car.size.y * 0.5f, car.size.x/2.f, car.size.y/2.f}, (Vector2){car.size.x/4.f, car.size.y/4.f}, 0, WHITE);
	}
}

#endif