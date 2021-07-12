#include "lem_in.h"

/*
**	An int** array is sent in to be increased by one, so we add one in
**	tmp and copy over all content to the tmp and return that.
*/

int	**append_array(t_lem *lem, int **arr, int max)
{
	int	**tmp;
	int	i;
	int	j;

	i = 0;
	tmp = (int **)malloc(sizeof(int *) * (max + 1));
	if (tmp == NULL)
		error_message(lem, 2);
	while (i < max)
	{
		j = 0;
		tmp[i] = (int *)malloc(sizeof(int) * (arr[i][0] * -1));
		if (tmp[i] == NULL)
			error_message(lem, 1);
		while (j < (arr[i][0] * -1))
		{
			tmp[i][j] = arr[i][j];
			j++;
		}
		i++;
	}
	i = 0;
	free_int_array(arr, max);
	return (tmp);
}

int	compare(int *final, int *other_path)
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

int	set_steps(int *option, t_lem *lem, int i, int ants_cpy)
{
	int	*ants_and_len;
	int	tab;

	tab = (option[0] * -1) - 3;
	ants_and_len = (int *)malloc(sizeof(int) * tab);
	if (ants_and_len == NULL)
		error_message(lem, 1);
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

int	scan_similar(t_lem *lem, int *index_of_valid_paths, int *to_comp)
{
	int	i;

	i = 2;
	while (i < (index_of_valid_paths[0] * -1) - 1)
	{
		if (compare(lem->final[index_of_valid_paths[i]], to_comp) == 1)
			return (1);
		i++;
	}
	return (0);
}
