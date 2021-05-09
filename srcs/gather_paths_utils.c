#include "lem_in.h"

void	arr_row_size(t_tree *start, t_lem *lem)
{
	t_tree	*tree;

	tree = start;
	while (tree->name != lem->e_room_index && tree->name != 0)
	{
		if (tree->sib != NULL)
		{
			lem->max_paths++;
			arr_row_size(tree->sib, lem);
		}
		tree = tree->child;
		if (tree->name == 0)
			break ;
	}
}

/*
**	A util of scan_paths in gater_paths
*/

void	get_room_num(t_tree *tree, t_lem *lem, int r, int i)
{
	int	x;

	x = 0;
	while (x < lem->current_roomnum && x != tree->name)
		x++;
	lem->all_paths[i][r] = x;
}

/*
**	Discards dead ends from all_paths and sorts paths from short to long
*/
void	sort_paths(t_lem *lem)
{
	int *tmp;
	int i;
	int j;
	int x;
	int tab;

	i = 0;
	j = 0;
	x = 0;
	tab = lem->max_paths;
//	ft_printf("lem->negative_one:%d\n", lem->negative_one);
	if (!(lem->final = (int **)malloc(sizeof(int *) * lem->negative_one)))
		ft_printf("ERROR in sort_paths");
	while (i < tab)
	{
		if (lem->all_paths[i][lem->all_paths[i][0] * -1] == -1)
		{
			lem->final[j] = lem->all_paths[i];
			j++;
		}
		else
			lem->max_paths--;
		i++;
	}
	while (x + 1 < lem->negative_one)
	{
		if (lem->final[x][0] * -1 > lem->final[x + 1][0] * -1)
		{
			tmp = lem->final[x];
			lem->final[x] = lem->final[x + 1];
			lem->final[x + 1] = tmp;
			x = 0;
		}
		else
			x++;
	}
	ft_putstr("\n\nALL VALID PATHS - SORTED: \n");
	ft_printf("total:%d\n", lem->total_paths);
	print_double_arr(lem->final, lem->max_paths);
}

void	count_valid_paths(t_lem *lem)
{
	int i;

	i = 0;
	lem->negative_one = 0;
	while (i < lem->max_paths)
	{
		if (lem->all_paths[i][lem->all_paths[i][0] * -1] == -1)
			lem->negative_one++;
		i++;
	}
}
