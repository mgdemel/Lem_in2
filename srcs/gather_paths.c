#include "lem_in.h"
#include <stdio.h>

void copy_previous_path(t_lem *lem, int r, int path, int i)
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

int copy_col(int r, t_lem *lem, int array, char *name)
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
	if (name != NULL && (ft_strcmp(name, lem->end_room_name) == 0))
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

int scan_paths(t_tree *start, t_lem *lem, int i, int r)
{
	t_tree *tree;
	t_room *room;
	int prev_index;
	//int k;

	// k = 0;
	// while (k < 18)
	// {
	// 	ft_printf("%d\n", lem->all_paths[i][k]);
	// 	k++;
	// }

	prev_index = r;
	tree = start;
	room = lem->all_rooms;
	ft_printf("Scan path with tree->name:%s\n", tree->name);
	ft_printf("i:%d\nr:%d\n", i, r);
	//ft_printf("path:%d\n", lem->all_paths[i][r]);
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
			ft_printf("prev_index:%d\nlem->path:%d\n%i\n", prev_index, lem->path, i);
			if (!(lem->all_paths[lem->path] = (int *)malloc(sizeof(int) * lem->nbr_rooms))) //the most it could be is all of the rooms connected to one another
				return (1);
			copy_previous_path(lem, prev_index, lem->path, i);
			ft_printf("BABA\n");
			scan_paths(tree->sibling, lem, lem->path, r);
		}
		ft_printf("test1\n");
		r++;
		tree = tree->child;
		room = lem->all_rooms;
		ft_printf("test1\n");
		if (tree->name != NULL && ft_strcmp(tree->name, lem->end_room_name) == 0)
		{
			while (room->next != NULL && (ft_strcmp(room->name, tree->name) != 0))
				room = room->next;
			lem->all_paths[i][r] = room->roomnum;
			r++;
			break;
		}
	}
	copy_col(r, lem, i, tree->name);
	ft_printf("test2\n");
	return (0);
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
	if (!(lem->all_paths[i] = (int *)malloc(sizeof(int) * lem->nbr_rooms))) //the most it could be is all of the rooms connected to one another
		return (1);
	scan_paths(start, lem, 0, 0);
	
	return (0);
}
