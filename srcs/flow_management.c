#include "lem_in.h"

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
		if (!(new_forbidden = (int *)malloc(sizeof(int) * ((len + 3) + forbidden[0]))))
			return (NULL);
		while (i < forbidden[0]) // if null or something
		{
			new_forbidden[i] = forbidden[i];
			i++;
		}
		new_forbidden[0] = len + forbidden[0];
	}
	else
	{
		if (!(new_forbidden = (int *)malloc(sizeof(int) * (len + 3))))
			return (NULL);
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
	return (new_forbidden);
}
//next up, just test this!

int	compare(int *all_paths, int *other_path)
{
	int i;
	int j;

	i = 0;
	while (i < all_paths[0] * -1)
	{
		j = 0;
		while (j < other_path[0] * -1)
		{
			if (all_paths[i] == other_path[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int scan_similar(t_lem *lem, int *valid_path)
{
	int j;
	int i;

	i = 2;
	while (i < ((valid_path[0] * -1)))
	{
		if (compare(lem->all_paths[lem->i_placeholder + 1], lem->all_paths[valid_path[i]]) == 1)
			return (1);
		i++;
	}
	return (1);
}

int find_low_int_array(t_lem *lem, int result)
{
	int i;
	int lowest;
	int placeholder;

	i = 0;
	lowest = 0;
	placeholder = 0;
	while (i < lem->max_paths)
	{
		if (lowest < (lem->all_paths[i][0] * -1))
		{
			lowest = lem->all_paths[i][0] * -1;
			placeholder = i;
		}
		i++;
	}
	lowest = lowest - 2;
	ft_printf("lowest: %d\n", lowest);
	if (result == 0)
		return (lowest + lem->ants);
	else
		return (placeholder);
}

int add_path(int **valid_paths, t_lem *lem, int len)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < lem->max_valid_path)
		i++;
	if (!(valid_paths[i] = (int *)malloc(sizeof(int) * len)))
		return (1);
	valid_paths[i][0] = len * -1;
	valid_paths[i][1] = find_low_int_array(lem, 0);
	while (len >= 3)
	{
		valid_paths[i][j] = find_low_int_array(lem, 1);
		j++;
		len--;
	}
	ft_printf("valid_paths first index: %d valid_paths second index: %d\n", valid_paths[i][0], valid_paths[i][1]);
	return (0);

	//valid_paths[0] = -3|steps(ants+shortest/longest)|index
}
// void	add_into_allpaths(t_lem *lem, int *forbidden)
// {
// 	while (i < forbidden[0])
// 	{

// 	}
// }

int recursion_adding(t_lem *lem, int i, int **valid_paths)
{
	int compare;

	// i represents the length of a single int array ex. i = 3 = [1][2][3]

	compare = i;
	if (compare + 1 < lem->nbr_paths)
	{
		while (i < lem->nbr_paths)
		{
			if (scan_similar(lem, valid_paths[lem->i_placeholder], 0)) // finds if the two indexes has any rooms that are similar
			{
				lem->malloc_len++;
				lem->i_placeholder++;
				valid_paths = append_array(valid_paths, lem->max_valid_path);
				lem->max_valid_path++;
				ft_printf("malloc len:%d max valid path:%d\n", lem->malloc_len, lem->max_valid_path);
				add_path(valid_paths, lem, lem->malloc_len);
				recursion_adding(lem, i + 1, valid_paths);
			}
			i++;
			compare++;
		}
		lem->malloc_len = 3;
		// 	add_into_allpaths(lem, forbidden); // count 0 and negative for malloc, adding
	}
}

0: -2|6|0
1: -3|4|0|1  
2: -4|4|0|1|2 // how do we get index 2 to find the two indexes to compare to 2
3: -3|4|0|2
4: -2|5|3

int flow_management(t_lem *lem)
{
	int **valid_paths;
	
	if (!(valid_paths = (int **)malloc(sizeof(int *) * lem->max_valid_path)))
		return (1);
	if (!(first_path(valid_paths, lem, 3)))
		return (1);
	recursion_adding(lem, 0, valid_paths);
	return (0);
}