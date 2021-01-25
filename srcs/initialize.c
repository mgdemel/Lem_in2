#include "../includes/lem_in.h"

void	initialize_lem(t_lem *lem)
{
	lem->ants = 0;
}

void	initialize_room(t_lem *room)
{
	room->name = NULL;
	room->y = 0;
	room->x = 0;
	room->roomtype = 0;
	room->prev = NULL;
	room->next = NULL;
}

/*
**		TODO
**		Count the number of tunnels, save in lem for
**		mallocing the array of tunnels.
*/
