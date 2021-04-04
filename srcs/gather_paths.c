#include "lem_in.h"

void	copy_previous_path(t_lem *lem, int r, int path, int i)
{
	if (i != 0 && lem->all_paths[i - 1][0] <= 0)
	{
		while (r >= 0)
		{
			lem->all_paths[path][r] = lem->all_paths[i][r + 1];
			r--;
		}
	}
	else
	{
		while (r >= 0)
		{
			lem->all_paths[path][r] = lem->all_paths[i][r];
			r--;
		}
	}
}

int		copy_col(int r, t_lem *lem, int array, char *name)
{
	int new[r + 2];
	int i;

	i = 0;
	new[i] = ((r + 1) * -1);
	i++;
	while (i < (r + 1))
	{
		new[i] = lem->all_paths[array][i - 1];
		i++;
	}
	if (name != NULL && (ft_strcmp(name, lem->e_room_name) == 0))
		new[i] = -1;
	else
		new[i] = -2;
	i = 0;
	while (i < (r + 2))
	{
		lem->all_paths[array][i] = new[i];
		i++;
	}
	return (0);
}

int		scan_paths(t_tree *start, t_lem *lem, int i, int r)
{
	t_tree	*tree;
	int		prev_index;

	prev_index = r;
	tree = start;
	while (tree->name != NULL)
	{
		get_room_num(tree, lem, r, i);
		prev_index++;
		if (tree->sib != NULL && ft_strcmp(tree->name, lem->e_room_name) != 0)
		{
			lem->path++;
			if (!(lem->all_paths[lem->path] = (int *)malloc(sizeof(int) * lem->nbr_rooms)))
				return (1);
			copy_previous_path(lem, prev_index, lem->path, i);
			scan_paths(tree->sib, lem, lem->path, r);
		}
		r++;
		tree = tree->child;
		if (tree->name != NULL && ft_strcmp(tree->name, lem->e_room_name) == 0)
		{
			get_room_num(tree, lem, r, i);
			r++;
			break ;
		}
	}
	if (tree->name == NULL || ft_strcmp(tree->name, lem->e_room_name) == 0)
		copy_col(r, lem, i, tree->name);
	return (0);
}

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

int		create_path_arr(t_lem *lem)
{
	int		i;
	t_tree	*start;
	int		test_index;

	i = 0;
	test_index = 0;
	lem->test_index = 0;
	start = lem->tree;
	arr_row_size(start, lem);
	if (!(lem->all_paths = (int **)malloc(sizeof(int *) * lem->max_paths)))
		return (1);
	if (!(lem->all_paths[i] = (int *)malloc(sizeof(int) * lem->nbr_rooms)))
		return (1);
	if (!(scan_paths(start, lem, 0, 0)))
		return (1);
	return (0);
}
