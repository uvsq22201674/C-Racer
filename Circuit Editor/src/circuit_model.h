#ifndef CIRCUIT_MODEL_H_INCLUDED
#define CIRCUIT_MODEL_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

#define nullptr ((void*) 0)

struct Checkpoint
{

	Vector2 position;
	struct Checkpoint * previous;
	struct Checkpoint * next;

};
typedef struct Checkpoint Checkpoint;

typedef struct
{
	Checkpoint * start;
	unsigned int checkpoint_count;

} CircuitBone;
CircuitBone CreateCircuitBone(Vector2 const first)
{
	Checkpoint * orig = malloc(sizeof(Checkpoint));
	orig->position = first;
	orig->previous = orig;
	orig->next = orig;

	CircuitBone to_return = {orig, 1};

	return to_return;
}
CircuitBone DestroyCircuitBone(CircuitBone const bone)
{
	Checkpoint * destroying = bone.start;

	unsigned int count = 0u;
	do
	{
		Checkpoint * next = destroying->next;
		
		if(destroying != nullptr)
		{
			free(destroying);
			count ++;
			printf("\t%s\n", "Checkpoint deleted");
		}
		else
			break;

		destroying = next;
	}while(destroying != bone.start);

	if(count == bone.checkpoint_count)
	{
		printf("\t%s\n", "Successfully destroyed circuit bone.");
	}
	else
	{
		printf("\tError : Freed %u out of %u checkpoints when destroying circuit bone.\n", count, bone.checkpoint_count);
	}
}
int AddCheckpointTo(CircuitBone * bone, Vector2 const pos)
{
	Checkpoint * to_add = malloc(sizeof(Checkpoint));
	if(to_add != nullptr)
	{
		to_add->position = pos;
		to_add->next = bone->start;

		Checkpoint * last_cp = bone->start;
		while(last_cp->next != bone->start)
		{
			last_cp = last_cp->next;
		}
		last_cp->next = to_add;
		to_add->previous = last_cp;
		
		bone->checkpoint_count ++;

		return 1;
	}
	else
		return 0;
}

#endif