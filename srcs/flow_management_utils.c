#include "lem_in.h"

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

int	set_steps(int *option, t_lem *lem) //something a bit off here - sometimes the steps don't include the final steps
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
