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

int compare(int *all_paths, int *other_path)
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
		if (lowest < (lem->final_paths[i][0] * -1))
		{
			lowest = lem->final_paths[i][0] * -1;
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


void	set_steps(int *path)
{
	int i;
	int steps;

	i = 2;
	steps = 0;
	while (i < path[0] * -1)
	{
		i++;
	}
}
//add_path(options, lem, 3)
int **add_path(int **options, t_lem *lem, int len)
{
	int j;

	j = 0;
	if (!(options[lem->max_options] = (int *)malloc(sizeof(int) * len)))
		ft_printf("ERRRRRRRRORRRRROORRR");
	options[lem->max_options][0] = len * -1; //sets the len (index0) to a negative number
	options[lem->max_options][1] = 0;    //set_steps(lem, options[lem->max_options]); //should set the steps (index1) to # of steps 
	while (len >= 3)
	{
		options[lem->max_options][j] = find_low_int_array(lem, 1);
		j++;
		len--;
	}
	ft_printf("options len (index0): %d options steps (index1): %d\n", options[lem->max_options][0], options[lem->max_options][1]);
	return (options);
}
// I  STEPS ROOMS
// 0: 1 2 3
// 1: 4 5 6
// 2: 7 8 9
// ants: 3
// 			I  LEN  STEPS   PATHS
// options  0: -2   6       0
// 			1: -3   5       0 1
// 			2: -4   4       0 1 2
// 			3: -2   6       1
// 			4: -3   5       1 2
// 			5: -2   6       2
// 			// ... as many as there are possible combinations
// 			// find situation with the lowest steps!
// steps = 9       
// 			1     2
// 			a     3
// 			a	  4
// 			a	  5
// 			a	  6
// 			a	  7
// 			a	  8
// 			a     a
// 			a     a

int scan_similar(t_lem *lem, int *valid_path)
{
	int j;
	int i;

	i = 2;
	j = 1;
	while (i <= ((valid_path[0] * -1))) // MIG?HT HAVE TO BE < not <=
	{
		if (compare(lem->all_paths[valid_path[i]], lem->all_paths[lem->i_placeholder + 1]) == 1)
			return (1);
		i++;
	}
	return (0);
}

int recursion_adding(t_lem *lem, int i, int **options)
{
	int compare;
	int possibilities; //can be max the same number of ants - 13 ants with 13 possibilites means one ant per possibility!

	// i represents the length of a single int array ex. i = 3 = [1][2][3]

	compare = i;
	possibilities = 0;
	while (possibilities < lem->ants)
	{
		while (i < lem->nbr_paths)
		{
			if (i >= lem->ants)
				break ;
			if (scan_similar(lem, options[compare])) // finds if the two indexes has any rooms that are similar
			{

				// only add if it's a good path
				// good path = low steps
				// steps = ants + length of path
				lem->malloc_len++;
				options = append_array(options, lem->max_options); // adding a malloced space for a valid path
				lem->max_options++;
				ft_printf("malloc len:%d max valid path:%d\n", lem->malloc_len, lem->max_options);
				add_path(options, lem, lem->malloc_len);
				recursion_adding(lem, i + 1, options);
				compare++;
			}
			lem->i_placeholder++;
			i++;
		}
		lem->malloc_len = 3;
		possibilities++;
		// 	add_into_allpaths(lem, forbidden); // count 0 and negative for malloc, adding
	}
	return(0);
}

int flow_management(t_lem *lem)
{
	int **options;
	int i;

	i = 0;
	if (!(options = (int **)malloc(sizeof(int *) * lem->max_options)))
		return (1);
	options = add_path(options, lem, 3);
	ft_printf("ADDED PATH\n");
	ft_printf("options[0][0]: %d\n", options[0][0]);
	while (i < (options[0][0] * -1))
	{
		ft_printf("option:%d\n", options[0][i]);
		i++;
	}
	recursion_adding(lem, 0, options);
	return (0);
}