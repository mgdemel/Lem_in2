#include "lem_in.h"

void	copy_previous_path(t_lem *lem, int r, int path, int i)
{
	while (r >= 0)
	{
		lem->all_paths[path][r] = lem->all_paths[i][r];
		r--;
	}
}

void	copy_col(int r, t_lem *lem, int array, int name)
{
	int	*new;
	int	i;

	i = 0;
	new = (int *)malloc(sizeof(int) * (r + 2));
	if (new == NULL)
		error_message(lem, 1);
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
}

void	scan_paths2(t_lem *lem, int i)
{
	lem->path++;
	lem->all_paths[lem->path] = (int *)malloc(sizeof(int) * lem->nbr_rooms + 2);
	if (lem->all_paths[lem->path] == NULL)
		error_message(lem, 1);
	copy_previous_path(lem, lem->prev_index, lem->path, i);
}

void	scan_paths(t_tree *tree, t_lem *lem, int i, int r)
{

	lem->prev_index = r;
	while (tree->name != 0)
	{
		get_room_num(tree, lem, r, i);
		lem->prev_index++;
		if (tree->sib != NULL && tree->name != lem->e_room_index)
		{
			scan_paths2(lem, i);
			scan_paths(tree->sib, lem, lem->path, r);
		}
		r++;
		if (tree->name != lem->e_room_index)
			tree = tree->child;
		if (tree->name == lem->e_room_index)
		{
			get_room_num(tree, lem, r, i);
			r++;
			break ;
		}
	}
	if (tree->name == 0 || tree->name == lem->e_room_index)
		copy_col(r, lem, i, tree->name);
}

void	create_path_arr(t_lem *lem)
{
	t_tree	*tree;
	t_tree	*tree2;

	tree = lem->tree;
	tree2 = lem->tree2;
	lem->prev_index = 0;

	arr_row_size(tree, lem);
	arr_row_size(tree2, lem);
	lem->all_paths = (int **)malloc(sizeof(int *) * lem->max_paths);
	lem->all_paths[lem->path] = (int *)malloc(sizeof(int) * lem->nbr_rooms + 2);
	if (lem->all_paths == NULL || lem->all_paths[0] == NULL)
		error_message(lem, 1);
	scan_paths(tree, lem, 0, 0);
	scan_paths(tree2, lem, 0, lem->prev_index);
}
