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
