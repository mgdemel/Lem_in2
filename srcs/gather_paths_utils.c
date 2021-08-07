#include "lem_in.h"

int		*ft_intdup(int *row)
{
	int		i;
	int		*tmp;

	i = 0;
	while (row[i] != -1)
		i++;
	tmp = (int *)malloc(sizeof(int) * (i + 1));
	i = 0;
	while (row[i])
	{
		tmp[i] = row[i];
		i++;
	}
	tmp[i] = -1;
	return (tmp);
}

void	arr_row_size(t_tree *start, t_lem *lem)
{
	t_tree *tree;

	tree = start;
	while (tree->name != 0 && tree->name != lem->e_room_index)
	{
		if (tree->sib != NULL)
		{
			lem->max_paths++;
			arr_row_size(tree->sib, lem);
		}
		if (tree->name != lem->e_room_index)
			tree = tree->child;
		if (tree->name == 0 || tree->name == lem->e_room_index)
			break ;
	}
}

void	get_room_num(t_tree *tree, t_lem *lem, int room, int path)
{
	int	x;

	x = 0;
	while (x < lem->current_roomnum && x != tree->name)
		x++;
	lem->all_paths[path][room] = x;
}

/*
** Discards dead ends from all_paths
*/
void	discard_deadends(t_lem *lem)
{
	int	i;
	int	j;
	int	tab;

	i = 0;
	j = 0;
	tab = lem->max_paths;
	while (i < tab)
	{
		if (lem->all_paths[i][lem->all_paths[i][0] * -1] == -1)
		{
			lem->sorted[j] = ft_intdup(lem->all_paths[i]);
			j++;
		}
		else
			lem->max_paths--;
		i++;
	}
}

/*
**	Sorts paths from short to long
*/
void	sort_paths(t_lem *lem)
{
	int	*tmp;
	int	x;

	x = 0;
	lem->sorted = (int **)malloc(sizeof(int *) * lem->max_valid);
	if (lem->sorted == NULL)
		error_message(lem, 2);
	discard_deadends(lem);
	// ft_putstr("\n\nALL SORTED PATHS: \n"); //remove after
	// print_double_arr(lem->sorted, lem->max_paths); //remove after
	while (x + 1 < lem->max_valid)
	{
		if (lem->sorted[x][0] * -1 > lem->sorted[x + 1][0] * -1)
		{
			tmp = lem->sorted[x];
			lem->sorted[x] = lem->sorted[x + 1];
			lem->sorted[x + 1] = tmp;
			x = 0;
		}
		else
			x++;
	}
}

void	count_valid_paths(t_lem *lem)
{
	int	i;

	i = 0;
	lem->max_valid = 0;
	while (i < lem->max_paths)
	{
		if (lem->all_paths[i][lem->all_paths[i][0] * -1] == -1)
			lem->max_valid++;
		i++;
	}
	sort_paths(lem);
	// ft_putstr("\n\nALL SORTED PATHS: \n"); //remove after
	// print_double_arr(lem->sorted, lem->max_paths); //remove after
}
