#include "../includes/lem_in.h"

t_lem	*initialize_lem()
{
	t_lem	*lem;
	if (!(lem = (t_lem *)malloc(sizeof(t_lem))))
		return (NULL);
	lem->ants = 0;
	lem->nbr_tunnels = 0;
	lem->nbr_rooms = 0;
	lem->all_rooms = NULL;
	lem->tunnels = NULL;
	lem->start_room_name = NULL;
	lem->end_room_name = NULL;
	lem->found_start_end = 0;
	return(lem);
}

t_room	*initialize_room()
{
	t_room 	*room;
	if (!(room = (t_room *)malloc(sizeof(t_room))))
		return (NULL);
	room->name = NULL;
	room->x = 0;
	room->y = 0;
	room->roomtype = 2; //defaults to type 2, changes in GNL linked list loop
	room->first = 0;
	room->prev = NULL;
	room->next = NULL;
	return (room);
}
