#include "lem_in.h"
void	output_ant(int **ant_flow, int j, t_lem *lem)
{
	ft_putchar('L');
	ft_putnbr(ant_flow[j][0]);
	ft_putchar('-');
	ft_putstr(lem->room_directory[ant_flow[j][ant_flow[j][1]]]);
	ft_putchar(' ');
}

int	output_set(int mps, int **ant_flow, t_lem *lem)
{
	int	flow;
	int	no_flow;
	int	i;
	int	j;

	flow = 0;
	no_flow = 0;
	i = 0;
	j = 0;
	while (i < mps && i < lem->ants)
	{
		if (ant_flow[j][ant_flow[j][1]] != -1)
		{
			output_ant(ant_flow, j, lem);
			ant_flow[j][1] += 1;
			flow++;
		}
		else
			no_flow++;
		j++;
		i++;
	}
	return (flow + no_flow);
}

void	flow(int **ant_flow, t_lem *lem, int sets, int mps)
{
	int	flow;

	flow = 0;
	lem->printed = 0; //remove later!
	while (sets >= 0)
	{
		mps = (lem->result[0] * -1) - 3 + flow;
		flow = output_set(mps, ant_flow, lem);
		ft_printf("\n");
		sets--;
		lem->printed++; //remove later!
	}
}

int	**create_ant_flow(int i, int j, int **ant_flow, t_lem *lem)
{
	int	ant_num;
	int	k;

	ant_num = 1;
	while (i < lem->ants)
	{
		k = 2;
		ant_flow[i][0] = ant_num;
		ant_flow[i][1] = 2;
		while (k < ((lem->sorted[lem->result[j]][0] + 2) * -1) + 2)
		{
			ant_flow[i][k] = lem->sorted[lem->result[j]][k];
			k++;
		}
		ant_flow[i][k] = -1;
		ant_num++;
		i++;
		if (j < (lem->result[0] * -1) - 2)
			j++;
		else
			j = 2;
	}
	return (ant_flow);
}

void	output(t_lem *lem)
{
	int	**ant_flow;
	int	i;
	int	j;

	i = 0;
	j = 2;
	ant_flow = (int**)malloc(sizeof(int*) * lem->ants);
	if (ant_flow == NULL)
		error_message(lem, 1);
	while (i < lem->ants)
	{
		ant_flow[i] = (int*)malloc(sizeof(int) * (3 + ((lem->sorted[lem->result[j]][0]) + 2) * -1));
		if (ant_flow[i] == NULL)
			error_message(lem, 1);
		if (j < (lem->result[0] * -1) - 2)
			j++;
		else
			j = 2;
		i++;
	}
	ant_flow = create_ant_flow(0, 2, ant_flow, lem);
	flow(ant_flow, lem, lem->result[1], (lem->result[0] * -1) - 3);
	free_int_array(ant_flow, lem->ants);
}
