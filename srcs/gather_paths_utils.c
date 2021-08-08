#include "lem_in.h"

int		*ft_intdup(int *row, t_lem *lem)
{
	int		i;
	int		*tmp;

	i = 0;
	while (row[i] != -1)
		i++;
	tmp = (int *)malloc(sizeof(int) * (i + 1));
	if (tmp == NULL)
		error_message(lem, 2);
	i = 0;
	while (row[i] != -1)
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

void	populate_sorted(t_lem *lem)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < lem->max_paths)
	{
		if (lem->all_paths[i][lem->all_paths[i][0] * -1] == -1)
		{
			lem->sorted[j] = ft_intdup(lem->all_paths[i], lem);
			j++;
		}
		i++;
	}
}

/*
**	Sorts paths from short to long
*/
void	sort_paths(t_lem *lem)
{
	int	i;
	int *tmp;

	i = 0;
	lem->sorted = (int **)malloc(sizeof(int *) * lem->max_valid);
	if (lem->sorted == NULL)
		error_message(lem, 2);
	populate_sorted(lem);
	while((i + 1) < lem->max_valid)
	{
		if (lem->sorted[i][0] * -1 > lem->sorted[i + 1][0] * -1)
		{
			tmp = lem->sorted[i];
			lem->sorted[i] = lem->sorted[i + 1];
			lem->sorted[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
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
}
