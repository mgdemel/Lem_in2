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

int	comp(int *final, int *other_path)
{
	int	i;
	int	j;

	i = 2;
	while (i < (final[0] * -1) - 1)
	{
		j = 2;
		while (j < (other_path[0] * -1) - 1)
		{
			if (final[i] == other_path[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	set_steps(int *option, t_lem *lem)
{
	int	*ants_and_len;
	int	i;
	int	ants_cpy;
	int	tab;

	tab = (option[0] * -1) - 3;
	ants_cpy = lem->ants;
	i = 0;
	if (!(ants_and_len = (int *)malloc(sizeof(int) * tab)))
		ft_printf("ERRRROR");
	while (i < tab)
	{
		ants_and_len[i] = (lem->final[option[i + 2]][0] * -1) - 3;
		i++;
	}
	while (ants_cpy > 0)
	{
		i = 0;
		while (i + 1 < tab && ants_and_len[i] > ants_and_len[i + 1])
			i++;
		ants_and_len[i]++;
		ants_cpy--;
	}
	tab = ants_and_len[0];
	free(ants_and_len);
	return (tab);
}

int	**add_minor_option(int **options, t_lem *lem, int next_path, int num)
{
	int	i;
	int	j;
	int	len;

	i = 1;
	j = 2;
	len = lem->malloc_len;
	if (!(options[num] = (int *)malloc(sizeof(int) * len)))
		ft_printf("ERRRRRRRRORRRRROORRR");
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
	options[num][1] = 0;
	options[num][1] = set_steps(options[num], lem);
	return (options);
}
int	scan_similar(t_lem *lem, int *index_of_valid_paths, int *to_comp)
{
	int	i;

	i = 2;
	while (i < (index_of_valid_paths[0] * -1) - 1)
	{
		if (comp(lem->final[index_of_valid_paths[i]], to_comp) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	**recursion_adding(t_lem *lem, int **options, int comp)
{
	int	i;

	i = 0;
	if (lem->i_pos < lem->max_paths - 1)
	{
		while (comp < lem->max_paths)
		{
			/*
			**	Assumes we are comparing a "x | y | path" int array, adding onto paths as long as possible.
			**	Have to exit once it's not possible, and add next path as a single option.
			*/
			if (scan_similar(lem, options[lem->i_pos - 1], lem->final[comp]) == 0)
			{
				lem->malloc_len++;
				options = append_array(options, lem->i_pos);
				options = add_minor_option(options, lem, comp, lem->i_pos);
				lem->i_pos++;
				options = recursion_adding(lem, options, comp + 1);
			}
			comp++;
		}
	}
	lem->malloc_len = 4;
	return(options);
}

int **add_major_option(int **options, t_lem *lem, int index, int num)
{
	if (!(options[index] = (int *)malloc(sizeof(int) * 4)))
		ft_printf("ERRRRRRRRORRRRROORRR");
	options[index][0] = -4; //sets the len (index0) to a negative number
	options[index][1] = lem->ants + (lem->final[num][0] * -1) - 4; //set_steps(options[0], lem->ants); //should set the steps (index1) to # of steps 
	options[index][2] = num;
	options[index][3] = -1;
	return (options);
}

int flow_management(t_lem *lem)
{
	int **options;
	int i;
	int j;
	int comp;
	int	major_index;
	
	i = 0;
	j = 0;
	comp = 0;
	major_index = 0;
	lem->i_pos = 0;
	if (!(options = (int **)malloc(sizeof(int *) * 1)))
		return (1);
	ft_printf("before first major option\n");
	options = add_major_option(options, lem, lem->i_pos, 0);
	while (major_index <= lem->max_paths - 1)
	{
		if (lem->i_pos != 0)
		{
			options = append_array(options, lem->i_pos);
			add_major_option(options, lem, lem->i_pos, major_index);
		}
		lem->i_pos++;
		major_index++;
		comp++;
		options = recursion_adding(lem, options, comp);
	}
	ft_printf("hello\n");
	print_double_arr(options, lem->i_pos);
	lem->result = get_result(options, lem);
	return (0);
}