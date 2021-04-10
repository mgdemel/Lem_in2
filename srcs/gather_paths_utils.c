#include "lem_in.h"

void	arr_row_size(t_tree *start, t_lem *lem)
{
	t_tree *tree;

	tree = start;
	if (tree->name != NULL)
	{
		while (ft_strcmp(tree->name, lem->e_room_name) != 0)
		{
			if (tree->sib != NULL)
			{
				lem->max_paths++;
				arr_row_size(tree->sib, lem);
			}
			tree = tree->child;
			if (tree->name == NULL)
				break ;
		}
	}
}

/*
**	A util of scan_paths in gater_paths
*/

void	get_room_num(t_tree *tree, t_lem *lem, int r, int i)
{
	t_room	*room;

	room = lem->all_rooms;
	while (room->next != NULL && (ft_strcmp(room->name, tree->name) != 0))
		room = room->next;
	lem->all_paths[i][r] = room->roomnum;
}