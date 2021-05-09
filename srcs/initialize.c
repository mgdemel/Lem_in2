#include "lem_in.h"

t_lem	*initialize_lem(void)
{
	t_lem *lem;

	if (!(lem = (t_lem *)malloc(sizeof(t_lem))))
		return (NULL);
	lem->ants = 0;
	lem->nbr_tunnels = 0;
	lem->nbr_rooms = 0;
	lem->current_roomnum = 0;
	lem->tunnel_directory = NULL;
	lem->room_directory = NULL;
	lem->found_start_end = 0;
	lem->tunnel_index = 0;
	lem->all_rooms = NULL;
	lem->all_paths = NULL;
	lem->tunnels = NULL;
	lem->s_room_name = NULL;
	lem->e_room_name = NULL;
	lem->s_room_index = 0;
	lem->e_room_index = 0;
	lem->tree = NULL;
	lem->test_index = 1;
	lem->max_paths = 1;
	lem->path = 0;
	lem->sib_name = 0;
	lem->malloc_len = 4;
	lem->i_pos = 0;
	lem->final = NULL;
	lem->comp = 0;
	lem->result = NULL;
	lem->total_paths = 0;
	return (lem);
}

t_room	*initialize_room(t_lem *lem)
{
	t_room	*room;

	if (!(room = (t_room *)malloc(sizeof(t_room))))
		return (NULL);
	room->name = NULL;
	room->roomtype = 2;
	lem->current_roomnum++;
	room->roomnum = lem->current_roomnum;
	room->next = NULL;
	return (room);
}

t_tree	*tree_init(t_tree *parent)
{
	t_tree	*tree;

	if (!(tree = (t_tree *)malloc(sizeof(t_tree))))
		return (NULL);
	tree->name = 0;
	tree->parent = parent;
	tree->child = NULL;
	tree->sib = NULL;
	return (tree);
}

t_tree	*head_tree_init(int name)
{
	t_tree	*tree;

	if (!(tree = (t_tree *)malloc(sizeof(t_tree))))
		return (NULL);
	tree->name = name;
	tree->parent = NULL;
	tree->child = NULL;
	tree->sib = NULL;
	return (tree);
}
