#include "lem_in.h"
#include <stdio.h>

void copy_previous_path(t_lem *lem, int r, int path, int i)
{
	// while (k < 2)
	// {
	// 	ft_printf("%d\n", lem->all_paths[path - 1][k]);
	// 	k++;
	// }
	if (i != 0)
	{
		if (lem->all_paths[i - 1][0] <= 0)
		{
			while (r >= 0)
			{
				lem->all_paths[path][r] = lem->all_paths[i - 1][r + 1];
				r--;
			}
		}
		else
		{
			ft_printf("went here2\n");
			ft_printf("path:%d\n", path);
			ft_printf("i:%d\n", i);
			ft_printf("all_paths:%d\n", lem->all_paths[8][0]);
			while (r >= 0)
			{

				lem->all_paths[path][r] = lem->all_paths[path - 1][r];
				r--;
			}
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

int *copy_col(int r, int *arr)
{
	int *new;
	int i;

	i = 0;
	if (!(new = (int *)malloc(sizeof(int) * r + 2)))
		return (NULL);
	new[i] = ((r + 1) * -1);
	i++;
	while (i < (r + 1))
	{
		new[i] = arr[i - 1];
		i++;
	}
	new[i] = -1;
	free(arr);
	return (new);
}

void scan_paths(t_tree *start, t_lem *lem, int i, int r)
{
	t_tree *tree;
	t_room *room;
	int prev_index;
	int k;

	k = 0;
	while (k < 18)
	{
		ft_printf("%d\n", lem->all_paths[i][k]);
		k++;
	}

	prev_index = r;
	tree = start;
	room = lem->all_rooms;
	ft_printf("Scan path with tree->name:%s\n", tree->name);
	ft_printf("i:%d\nr:%d\n", i, r);
	ft_printf("path:%d\n", lem->all_paths[i][r]);
	while (tree->name != NULL)
	{
		//ft_printf("treename %s\n", tree->child->name);
		while (room->next != NULL && (ft_strcmp(room->name, tree->name) != 0))
			room = room->next;
		ft_printf("copied over %d\n", room->roomnum);
		lem->all_paths[i][r] = room->roomnum; // BREAKS HERE CANT ACCESS lem->all_paths[6] after making this
		ft_printf("path:%d\n", lem->all_paths[i][r]);
		prev_index++;
		if (tree->sibling != NULL && (ft_strcmp(tree->name, lem->end_room_name) != 0))
		{
			ft_printf("\nSTARTED SIBLING\n");
			lem->path++;
			//lem->siblings_down++;
			ft_printf("prev_index:%d\nlem->path:%d\n%i\n", prev_index, lem->path, i);
			if (lem->all_paths[lem->path] != NULL)
				copy_previous_path(lem, prev_index, lem->path, i);
			scan_paths(tree->sibling, lem, lem->path, r);
			//lem->siblings_down--;
		}
		r++;
		tree = tree->child;
		room = lem->all_rooms;
		if (tree->name != NULL && ft_strcmp(tree->name, lem->end_room_name) == 0)
		{
			while (room->next != NULL && (ft_strcmp(room->name, tree->name) != 0))
				room = room->next;
			lem->all_paths[i][r] = room->roomnum;
			r++;
			break;
		}
	}
	if (tree->name != NULL)
		lem->all_paths[i] = copy_col(r, lem->all_paths[i]);
}

void arr_row_size(t_tree *start, t_lem *lem)
{
	t_tree *tree;

	tree = start;
	if (tree->name != NULL)
	{
		while (ft_strcmp(tree->name, lem->end_room_name) != 0)
		{
			if (tree->sibling != NULL)
			{
				lem->max_paths++;
				arr_row_size(tree->sibling, lem);
			}
			tree = tree->child;
			if (tree->name == NULL)
				break;
		}
	}
}

int create_path_arr(t_lem *lem)
{
	int i;
	int j;
	int k;
	t_tree *start;
	int test_index;

	i = 0;
	j = 0;
	k = 0;
	test_index = 0;
	lem->test_index = 0;
	start = lem->tree;
	arr_row_size(start, lem);
	if (!(lem->all_paths = (int **)malloc(sizeof(int *) * lem->max_paths + 1)))
		return (1);
	while (i < lem->max_paths)
	{
		if (!(lem->all_paths[i] = (int *)malloc(sizeof(int) * lem->nbr_rooms))) //the most it could be is all of the rooms connected to one another
			return (1);
		i++;
	}
	scan_paths(start, lem, 0, 0);
	ft_putstr("all_paths:\n");
	while (j < lem->max_paths)
	{
		ft_printf("Index %d:", test_index);
		if (lem->all_paths[j] != NULL)
		{
			while (k < (lem->all_paths[j][0] * -1) + 1)
			{
				ft_putnbr(lem->all_paths[j][k]);
				ft_putchar('|');
				k++;
			}
		}
		else
			ft_printf(" NULL");
		ft_putchar('\n');
		// if (test_index == 7)
		// {
		// 	ft_printf("WE ARE IN 7 NOW\n");
		// 	break;
		// }
		j++;
		k = 0;
		test_index++;
	}
	return (0);
}
