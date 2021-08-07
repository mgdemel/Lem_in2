#include "lem_in.h"
int	*get_result(int **options, t_lem *lem)
{
	int	i;
	int	lowest;
	int	tab;

	i = 0;
	tab = 0;
	lowest = options[0][1];
	while (i < lem->i_pos)
	{
		if (options[i][1] < lowest)
		{
			lowest = options[i][1];
			tab = i;
		}
		i++;
	}
	return (options[tab]);
}

int	**add_minor_option(int **options, t_lem *lem, int next_path, int num)
{
	int	i;
	int	j;
	int	len;

	i = 1;
	j = 2;
	len = lem->malloc_len;
	options[num] = (int *)malloc(sizeof(int) * len);
	if (options[num] == NULL)
		error_message(lem, 1);
	options[num][0] = (len * -1);
	while (len > 3)
	{
		options[num][j] = options[num - 1][j];
		j++;
		len--;
	}
	j--;
	options[num][j] = next_path;
	j++;
	options[num][j] = -1;
	options[num][1] = set_steps(options[num], lem, lem->ants);
	return (options);
}

int	**recursion_adding(t_lem *lem, int **options, int comp)
{
	int	i;

	i = 0;
	if (lem->i_pos < lem->final_tab - 1)
	{
		while (comp < lem->final_tab)
		{
			if (!(scan_similar(lem, options[lem->i_pos - 1], lem->final[comp])))
			{
				lem->malloc_len++;
				options = append_array(lem, options, lem->i_pos);
				options = add_minor_option(options, lem, comp, lem->i_pos);
				lem->i_pos++;
				options = recursion_adding(lem, options, comp + 1);
			}
			comp++;
		}
	}
	lem->malloc_len = 4;
	return (options);
}

int	**add_major_option(int **options, t_lem *lem, int index, int num)
{
	options[index] = (int *)malloc(sizeof(int) * 4);
	if (options[index] == NULL)
		error_message(lem, 1);
	options[index][0] = -4;
	options[index][1] = lem->ants + (lem->final[num][0] * -1) - 2;
	options[index][2] = num;
	options[index][3] = -1;
	return (options);
}

void	flow_management(t_lem *lem)
{
	int	**options;
	int	major_index;
	int	comp;

	major_index = 0;
	comp = 0;
	options = (int **)malloc(sizeof(int *) * 1);
	if (options == NULL)
		error_message(lem, 1);
	options = add_major_option(options, lem, lem->i_pos, 0);
	while (major_index <= lem->final_tab - 1)
	{
		if (lem->i_pos != 0)
		{
			options = append_array(lem, options, lem->i_pos);
			add_major_option(options, lem, lem->i_pos, major_index);
		}
		lem->i_pos++;
		major_index++;
		comp++;
		options = recursion_adding(lem, options, comp);
	}
	lem->result = get_result(options, lem);
	free_int_array(options, lem->i_pos);
}
