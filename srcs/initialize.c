#include "../includes/lem_in.h"

t_lem	*initialize_lem(t_lem *lem)
{
	lem->ants = 0;
	lem->nbr_tunnels = 0;
	lem->first_room = NULL;
	return(lem);
}

t_room	*initialize_room(t_room *room)
{
	room->name = NULL;
	room->y = 0;
	room->x = 0;
	room->roomtype = 0;
	room->prev = NULL;
	room->next = NULL;
	return (room);
}

/*
**		TODO
**		Count the number of tunnels, save in lem for
**		mallocing the array of tunnels.
*/
