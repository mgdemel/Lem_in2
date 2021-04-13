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
	int x;

	x = 0;
	while (x < lem->current_roomnum && (ft_strcmp(lem->directory[x], tree->name) != 0))
		x++;
	lem->all_paths[i][r] = x;
}