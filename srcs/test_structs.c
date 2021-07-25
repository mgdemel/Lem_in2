#include "lem_in.h"

void print_ants_and_len(int *ants_and_len, int tab)
{
	int i;

	i = 0;
	ft_printf("ants_and_len: ");
	while (i < tab)
	{
		ft_printf("| %d ", ants_and_len[i]);
		i++;
	}
	ft_printf("|\n");
}

void print_option(int *option)
{
	int c;
	
	c = 0;
	ft_printf("option: ");
	while (option[c] != -1)
	{
		ft_printf("| %d ", option[c]);
		c++;
	}
	ft_printf("| -1 |\n");
}

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
		if (arr[t][tt -1] != -1)
			ft_printf(" %d |", arr[t][tt]);
		ft_printf("\n");
		t++;
	}
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
				ft_printf("%d\n", tree->sib->name);
				ft_printf("NO SEG\n");
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
}