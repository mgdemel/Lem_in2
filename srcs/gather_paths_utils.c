#include "lem_in.h"

void	arr_row_size(t_tree *start, t_lem *lem)
{
	t_tree *tree;

	tree = start;
	ft_printf("tree->name:%d\n", tree->name);
	if (tree->name != 0)
	{
		while (tree->name != lem->e_room_index)
		{
			ft_printf("roomroom\n");
			if (tree->sib != NULL)
			{
				ft_printf("roomroom2\n");
				lem->max_paths++;
				arr_row_size(tree->sib, lem);
			}
			ft_printf("roomroom3\n");
			tree = tree->child;
			ft_printf("name after child is made:%d\n");
			if (tree->name == 0)
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
	while (x < lem->current_roomnum && x != tree->name)
		x++;
	lem->all_paths[i][r] = x;
}