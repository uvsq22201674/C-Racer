#ifndef CARCAMERA_H_INCLUDED
#define CARCAMERA_H_INCLUDED

void UpdateCarCamera(Camera2D * cam, Car car)
{
	cam->target = Vector2Add(cam->target, Vector2Scale(Vector2Subtract(Vector2Subtract(car.pos, Vector2Scale((Vector2) {400.f, 400.f}, 1.f/cam->zoom)), cam->target), 0.1f));

	float old_zoom = cam->zoom;
	
	cam->zoom = 1.f/(((car.speed.x * car.speed.x + car.speed.y * car.speed.y) + 400.f) / 400.f);
	
	Vector2 old_center = Vector2Add(cam->target, Vector2Scale((Vector2){400.f, 400.f}, 1.f/old_zoom));
	Vector2 new_center = Vector2Add(cam->target, Vector2Scale((Vector2){400.f, 400.f}, 1.f/cam->zoom));

	cam->target = Vector2Add(cam->target, Vector2Subtract(old_center, new_center));
}


#endif