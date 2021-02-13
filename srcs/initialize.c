#include "../includes/lem_in.h"

t_lem	*initialize_lem()
{
	t_lem	*lem;
	if (!(lem = (t_lem *)malloc(sizeof(t_lem))))
		return (NULL);
	lem->ants = 0;
	lem->nbr_tunnels = 0;
	lem->nbr_rooms = 0;
	lem->nbr_paths = 0;
	lem->found_start_end = 0;
	lem->path_index = 0;
	lem->trigger = 0;
	lem->all_rooms = NULL;
	lem->all_paths = NULL;
	lem->tunnels = NULL;
	lem->start_room_name = NULL;
	lem->end_room_name = NULL;
	lem->tree = NULL;
	lem->forbidden_array = NULL;
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
	room->prev = NULL;
	room->next = NULL;
	return (room);
}

t_tree	*tree_init(char *name)
{
	t_tree	*tree;

	if (!(tree = (t_tree *)malloc(sizeof(t_tree))))
		return (NULL);
    tree->name = ft_strdup(name);
    tree->parent = NULL;
    tree->child = NULL;
    tree->sibling = NULL;
	tree->used = 0;
    return(tree);
}

// t_path	*initialize_path(t_room *room, t_lem *lem)
// {
// 	t_path *path;
// 	t_room *room;

// 	room = lem->all_rooms;
// 	if (!(path = (t_path *)malloc(sizeof(t_path))))
// 		return (NULL);
// 	while (room->next != NULL)
//     {
// 		if (room->roomtype == 1)
// 		{
// 			path->start_room->name = room->name;
// 			path->start_room->x = room->x;
// 			path->start_room->y = room->y;
// 			path->start_room->roomtype = room->roomtype;
// 		}
// 		else if (room->roomtype == 3)
// 		{
// 			path->end_room->name = room->name;
// 			path->end_room->x = room->x;
// 			path->end_room->y = room->y;
// 			path->end_room->roomtype = room->roomtype;
// 		}
// 		room = room->next;
// 	}
// 	path->inbetween_rooms = NULL;
// 	path->length = 0;
// 	path->next = NULL;
// 	path->prev = NULL;
// 	return (path); 
// }