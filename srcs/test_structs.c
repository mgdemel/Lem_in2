#include "lem_in.h"

void print_tunnel_dir(int **arr, int max)
{
	int t = 0;
	int tt = 0;

	while(t < max)
	{
		tt = 0;
		while (tt < 4)
		{
			ft_printf(" %d |", arr[t][tt]);
			tt++;
		}
		ft_printf("\n");
		t++;
	}
	t = 0;
	ft_printf("\n");
}


void print_double_arr(int **arr, int max)
{
	int t = 0;
	int tt = 0;

	while(t < max)
	{
		tt = 0;
		while (tt < (arr[t][0] * -1))
		{
			ft_printf(" %d |", arr[t][tt]);
			tt++;
		}
		ft_printf(" %d |", arr[t][tt]);
		ft_printf("\n");
		t++;
	}
	t = 0;
	ft_printf("\n");
}

void print_int_arr(int *arr, int len, char *str)
{
	int i;

	i = 0;
	ft_printf("\n***---STARTING PRINT ARR---***\n");
	while (i < len)
	{
		ft_printf("%s:%d\n", str, arr[i]);
		i++;
	}
	ft_printf("\n");
}

void test_array(t_lem *lem)
{
	int i;

	i = 0;
	while (i < lem->nbr_tunnels)
	{
		ft_printf("%s\n", lem->tunnels[i]);
		i++;
	}
}

void scan_tree(t_tree *start, t_lem *lem, int i)
{
	t_tree *tree;

	ft_printf("STARTED SCAN_TREE\n");
	tree = start;
	i = 0;
	//  ft_printf("sibling pointer address %p\n", tree->sib);
	if (tree->name != 0)
	{
		while (tree->name != lem->e_room_index)
		{
			ft_putchar('\n');
			ft_printf("Step %d\n", lem->test_index);
			ft_printf("name of current room %d|\n", tree->name);
			lem->test_index++;
			if (tree->sib != NULL)
			{
				ft_printf("Changing PATH, found sibling\n");
				ft_printf("parent is %d\n", tree->parent->name);
				scan_tree(tree->sib, lem, lem->path);
			}
			if (tree->child->name != 0)
				tree = tree->child;
			else
				break ;
		}
	}
	ft_printf("name last room %d\nwith parent %d\n", tree->name, tree->parent->name);
}

void scan_rooms(t_lem *lem)
{
	t_room *room = lem->all_rooms;
	while (room->next != NULL)
	{
		ft_putstr("name: ");
		ft_putstr(room->name);
		ft_putchar('\n');

		ft_putstr("roomtype: ");
		ft_putnbr(room->roomtype);
		ft_putchar('\n');

		ft_putstr("roomnum: ");
		ft_putnbr(room->roomnum);
		ft_putchar('\n');
		ft_putchar('\n');

		room = room->next;
	}
}

void print_lem(t_lem *lem)
{
	ft_putstr("ants: ");
	ft_putnbr(lem->ants);
	ft_putchar('\n');

	ft_putstr("nbr_tunnels: ");
	ft_putnbr(lem->nbr_tunnels);
	ft_putchar('\n');

	ft_putstr("nbr_rooms: ");
	ft_putnbr(lem->nbr_rooms);
	ft_putchar('\n');

	ft_putstr("found_start_end: ");
	ft_putnbr(lem->found_start_end);
	ft_putchar('\n');

	// ft_putstr("all_paths: \n");
	// test_array(lem->all_paths);
	// ft_putchar('\n');

	ft_putstr("tunnels: \n");
	test_array(lem);
	ft_putchar('\n');

	ft_putstr("start room name: \n");
	ft_putstr(lem->start_room_name);
	ft_putchar('\n');

	ft_putstr("end room name: \n");
	ft_putstr(lem->e_room_name);
	ft_putchar('\n');
}

void scan_arrays(t_lem *lem)
{
	int j;
	int test_index;
	int k;

	k = 0;
	test_index = 0;
	j = 0;
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
			ft_printf("\n");
		}
		else
			ft_printf(" NULL");
		ft_putchar('\n');
		j++;
		k = 0;
		test_index++;
	}
}

void test_structs(t_lem *lem)
{
	t_tree *start;
	// int i;

	start = lem->tree;
	// i = 0;
	// t_tree *start = lem->tree;
	// lem->max_paths = lem->max_paths;
	// ft_putchar('\n');
	// ft_putchar('\n');
	ft_printf("TESTED STRUCTS\n");
	// ft_printf("********    LEM TESTING:    ********\n");
	// ft_printf("********    PRINT INFO:    ********\n\n");
	// print_lem(lem);
	ft_printf("********    SCAN ROOMS:    ********\n\n");
	scan_rooms(lem);
	ft_printf("********    SCAN THE TREE OF ROOMS:    ********\n\n");
	scan_tree(start, lem, 1);
	// ft_printf("********    SCAN THE ARRAY:     *********\n\n");
	// scan_arrays(lem);
	// ft_putchar('\n');
	// while (i < lem->max_paths)
	// {
	// 	ft_printf("Last index of %d is :%d\n", i, lem->all_paths[i][lem->all_paths[i][0] * -1]);
	// 	i++;
	// }
	print_double_arr(lem->final, lem->negative_one);
}