#include "lem_in.h"

t_lem	*initialize_lem(void)
{
	t_lem *lem;

	lem = (t_lem *)malloc(sizeof(t_lem));
	if (lem == NULL)
		error_message(lem, 1);
	lem->nbr_tunnels = 0;
	lem->nbr_rooms = 0;
	lem->current_roomnum = 0;
	lem->found_start_end = 0;
	lem->all_rooms = NULL;
	lem->tunnels = NULL;
	lem->tunnel_index = 0;
	lem->s_room_name = NULL;
	lem->e_room_name = NULL;
	lem->max_paths = 1;
	lem->path = 0;
	lem->sib_name = 0;
	lem->malloc_len = 4;
	lem->i_pos = 0;
	lem->result = NULL;
	lem->t_index = 0;
	lem->siborchild = -1;
	return (lem);
}

t_room	*initialize_room(t_lem *lem)
{
	t_room	*room;

	room = (t_room *)malloc(sizeof(t_room));
	if (room == NULL)
		error_message(lem, 1);
	room->name = NULL;
	room->roomtype = 2;
	lem->current_roomnum++;
	room->roomnum = lem->current_roomnum;
	room->next = NULL;
	return (room);
}

t_tree	*tree_init(t_lem *lem, t_tree *parent)
{
	t_tree	*tree;

	tree = (t_tree *)malloc(sizeof(t_tree));
	if (tree == NULL)
		error_message(lem, 1);
	tree->name = 0;
	if (parent == NULL)
		tree->parent = NULL;
	else
		tree->parent = parent;
	tree->child = NULL;
	tree->sib = NULL;
	return (tree);
}

t_tree	*head_tree_init(t_lem *lem, int name)
{
	t_tree	*tree;

	tree = (t_tree *)malloc(sizeof(t_tree));
	if (tree == NULL)
		error_message(lem, 1);
	tree->name = name;
	tree->parent = NULL;
	tree->child = NULL;
	tree->sib = NULL;
	return (tree);
}
