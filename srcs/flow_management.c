#include "../includes/lem_in.h"

int *add_to_forbidden_array(t_lem *lem, int src, int to_add, int *forbidden)
{
	int len;
	int i;
	int index;
	int *new_forbidden;

	i = 1;
	index = 2;
	len = (((lem->all_paths[src][0] - lem->all_paths[to_add][0]) * -1) - 2);
	if (forbidden != NULL)
	{
		if (!(new_forbidden = (int*)malloc(sizeof(int) * ((len + 3) + forbidden[0]))));
			return(NULL);
		while (i < forbidden[0]) // if null or something
		{
			new_forbidden[i] = forbidden[i];
			i++;
		}
		new_forbidden[0] = len + forbidden[0];
	}
	else
	{
		if (!(new_forbidden = (int*)malloc(sizeof(int) * (len + 3))));
			return(NULL);
		new_forbidden[0] = len;
	}
	new_forbidden[i] = src * -1;
	i++;
	new_forbidden[i] = to_add * -1;
	i++;
	while (i < (lem->all_paths[src][0] * -1))
	{
		new_forbidden[i] = lem->all_paths[src][index];
		index++;
		i++;
	}
	index = 2;
	while (i < (lem->all_paths[to_add][0] * -1))
	{
		new_forbidden[i] = lem->all_paths[to_add][index];
		index++;
		i++;
	}
	return(new_forbidden);
}
//next up, just test this!

int scan_similar(t_lem *lem, int src, int to_compare)
{
	int i;
	int j;

	i = 2;
	while (i < (lem->all_paths[src][0])* -1)
	{
		j = 2;
		while (j < (lem->all_paths[to_compare][0])* -1)
		{
			if (lem->all_paths[to_compare][j] == lem->all_paths[src][i])
				return(0);
			else
				j++;
		}
		i++;
	}
	return(1);
}

int	find_low_int_array(t_lem *lem, int result)
{
	int i;
	int lowest;

	i = 0;
	lowest = 0;

	while (i < lem->max_paths)
	{
		if (lowest < (lem->all_paths[i][0] * -1))
			lowest = lem->all_paths[i][0] * -1;
	}
	lowest = lowest - 2;
	if (result == 0)
		return (lowest + lem->ants);
	else
		return (i);
}

void	first_path(t_lem *lem)
{
	int i;

	i = 0;
	while (lem->all_paths[i][0] < 0)
		i++;
	if (!(lem->all_paths[i] = (int*)malloc(sizeof(int) * 2)))
			return (1);
	lem->all_paths[i][0] = find_low_int_array(lem, 0);
	lem->all_paths[i][1] = find_low_int_array(lem, 1);
}

void	flow_management(t_lem *lem)
{
	int i;
	int max_j;
	int j;
	int *forbidden;

	j = 1;
	i = 0;
	first_path(lem);
	while (i < lem->nbr_paths)
	{
		forbidden = NULL;
		j = i + 1;
		while (j < lem->nbr_paths)
		{
			if (scan_similar(lem, i, j) == 1)
			{
				forbidden = add_to_forbidden_array(lem, i, j, forbidden);
		//		forbidden[0, -1, 3, 4, 2, 5, 6];
		//		forbidden[0, -1, 3, 4, 2, 5, 6, -5, 7, 8];
			}
			j++;
		}
		if (forbidden != NULL)
			add_into_lem_allpaths_with_negative_forbidden(); // count 0 and negative for malloc, adding
		i++;
	}
}