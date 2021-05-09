#include "lem_in.h"
void	print_ant_dir(t_lem *lem, int **ant_flow)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < lem->ants)
	{
		j = 0;
		while (ant_flow[i][j] != -1)
		{
			ft_printf(" %d |", ant_flow[i][j]);
			j++;
		}
		ft_printf(" %d |", ant_flow[i][j]);
		ft_printf("\n");
		i++;
	}
	ft_printf("\n");
}

void	flow(int **ant_flow, t_lem *lem, int sets, int mps)
{
	int	flow;
	int no_flow;
	int	i;
	int	j;

	flow = 0;
	no_flow = 0;
	lem->printed = 0; //remove later!
	while (sets > 0)
	{
		j = 0;
		i = 0;
		mps = (lem->result[0] * -1) - 3 + flow + no_flow;
		flow = 0;
		no_flow = 0;
		while (i < mps && i < lem->ants)
		{
			if (ant_flow[j][ant_flow[j][1]] != -1)
			{
				ft_printf("L%d-%s ", ant_flow[j][0], lem->room_directory[ant_flow[j][ant_flow[j][1]]]);
				ant_flow[j][1] += 1;
				flow++;
			}
			else
				no_flow++;
			j++;
			i++;
		}
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
		while (k < ((lem->final[lem->result[j]][0] + 2) * -1) + 2)
		{
			ant_flow[i][k] = lem->final[lem->result[j]][k];
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

int	output(t_lem *lem)
{
	int	**ant_flow;
	int	i;
	int	j;

	i = 0;
	j = 2;
	if (!(ant_flow = (int**)malloc(sizeof(int*) * lem->ants)))
		return (1);
	while (i < lem->ants)
	{
		if (!(ant_flow[i] = (int*)malloc(sizeof(int) * (3 + ((lem->final[lem->result[j]][0]) + 2) * -1))))
			return (1);
		if (j < (lem->result[0] * -1) - 2)
			j++;
		else
			j = 2;
		i++;
	}
	ant_flow = create_ant_flow(0, 2, ant_flow, lem);
	flow(ant_flow, lem, lem->result[1], (lem->result[0] * -1) - 3);
	free_int_array(ant_flow, lem->ants);
	return (0);
}
