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
	lem->all_rooms = NULL;
	lem->all_paths = NULL;
	lem->tunnels = NULL;
	lem->start_room_name = NULL;
	lem->end_room_name = NULL;
	lem->tree = NULL;
	lem->test_index = 1;
	lem->path = 1;
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

t_tree	*tree_init(t_tree *parent)
{
	t_tree	*tree;

	if (!(tree = (t_tree *)malloc(sizeof(t_tree))))
		return (NULL);
	tree->name = NULL;
    tree->parent = parent;
	tree->child = NULL;
    tree->sibling = NULL;
    return(tree);
}

t_tree	*head_tree_init(char *name)
{
	t_tree	*tree;

	if (!(tree = (t_tree *)malloc(sizeof(t_tree))))
		return (NULL);
	tree->name = name;
    tree->parent = NULL;
    tree->child = NULL;
    tree->sibling = NULL;
    return(tree);

}