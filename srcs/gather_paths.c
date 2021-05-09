#include "lem_in.h"

void	copy_previous_path(t_lem *lem, int r, int path, int i)
{
	while (r >= 0)
	{
		lem->all_paths[path][r] = lem->all_paths[i][r];
		r--;
	}
}

int	copy_col(int r, t_lem *lem, int array, int name)
{
	int	new[r + 2]; //gotta do something about this for norm
	int	i;

	i = 0;
	new[i] = ((r + 1) * -1);
	i++;
	while (i < (r + 1))
	{
		new[i] = lem->all_paths[array][i - 1];
		i++;
	}
	if (name != 0 && name == lem->e_room_index)
		new[i] = -1;
	else
		new[i] = -2;
	i = 0;
	while (i < (r + 2))
	{
		lem->all_paths[array][i] = new[i];
		i++;
	}
	lem->test_stopper++;
	return (0);
}

int	scan_paths(t_tree *start, t_lem *lem, int i, int r)
{
	t_tree	*tree;
	int		prev_index;

	prev_index = r;
	tree = start;
	while (tree->name != 0)
	{
		get_room_num(tree, lem, r, i);
		prev_index++;
		if (tree->sib != NULL && tree->name != lem->e_room_index)
		{
			lem->path++;
			if (!(lem->all_paths[lem->path] = (int *)malloc(sizeof(int) * lem->nbr_rooms + 2)))
				return (1);
			copy_previous_path(lem, prev_index, lem->path, i);
			scan_paths(tree->sib, lem, lem->path, r);
		}
		r++;
		tree = tree->child;
		if (tree->name != 0 && tree->name == lem->e_room_index)
		{
			get_room_num(tree, lem, r, i);
			r++;
			break ;
		}
	}
	if (tree->name == 0 || tree->name == lem->e_room_index)
		copy_col(r, lem, i, tree->name);
	return (0);
}

int	create_path_arr(t_lem *lem)
{
	t_tree	*start;

	start = lem->tree;
	arr_row_size(start, lem);
//	ft_printf("max:%d\nnbr_rooms:%d\n", lem->max_paths, lem->nbr_rooms);
	if (!(lem->all_paths = (int **)malloc(sizeof(int *) * lem->max_paths)))
		return (1);
	if (!(lem->all_paths[0] = (int *)malloc(sizeof(int) * lem->nbr_rooms + 2)))
		return (1);
	if (!(scan_paths(start, lem, 0, 0)))
		return (1);
	return (0);
}
