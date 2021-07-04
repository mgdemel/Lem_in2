#include "lem_in.h"

void	copy_previous_path(t_lem *lem, int prev_room, int path, int prev_path)
{
	while (prev_room >= 0)
	{
		lem->all_paths[path][prev_room] = lem->all_paths[prev_path][prev_room];
		prev_room--;
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

void	scan_paths2(t_lem *lem, int prev_path)
{
	lem->path++;
	lem->all_paths[lem->path] = (int *)malloc(sizeof(int) * lem->nbr_rooms + 2);
	if (lem->all_paths[lem->path] == NULL)
		error_message(lem, 1);
	copy_previous_path(lem, lem->prev_room, lem->path, prev_path);
}

void	scan_paths(t_tree *tree, t_lem *lem, int path, int room)
{

	lem->prev_room = room;
	while (tree->name != 0)
	{
		get_room_num(tree, lem, room, path);
		lem->prev_room++;
		if (tree->sib != NULL && tree->name != lem->e_room_index)
		{
			scan_paths2(lem, path);
			scan_paths(tree->sib, lem, lem->path, room);
		}
		room++;
		if (tree->name != lem->e_room_index)
			tree = tree->child;
		if (tree->name == lem->e_room_index)
		{
			lem->all_paths[path][room] = lem->e_room_index;
			room++;
			break ;
		}
	}
	if (tree->name == 0 || tree->name == lem->e_room_index)
		copy_col(room, lem, path, tree->name);
}

void	create_path_arr(t_lem *lem)
{
	t_tree	*tree;
	t_tree	*tree2;

	tree = lem->tree;
	tree2 = lem->tree2;
	lem->prev_room = 0;

	arr_row_size(tree, lem);
	arr_row_size(tree2, lem);
	lem->all_paths = (int **)malloc(sizeof(int *) * lem->max_paths);
	lem->all_paths[lem->path] = (int *)malloc(sizeof(int) * lem->nbr_rooms + 2);
	if (lem->all_paths == NULL || lem->all_paths[0] == NULL)
		error_message(lem, 1);
	scan_paths(tree, lem, 0, 0);
	//lem->path++;
	scan_paths(tree2, lem, lem->path, 0);
	// ft_printf("ALL_PATHS: \n");
	// print_double_arr(lem->all_paths, lem->max_paths);
}
