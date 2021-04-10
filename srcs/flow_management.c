#include "lem_in.h"

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

int		set_steps(int *path, t_lem *lem, int ants)
{
	int i;
	int steps;
	int path_len;

	i = 2;
	steps = 0;
	path_len = 0;
	ants = lem->ants;
	if (ants == lem->ants)
		return (steps);
	while (i < path[0] * -1)
	{
		// find the actual path stored at this index from the other array
		// take the value of that path's first index * -1
		// store that value into path_len
		// steps = how many steps it takes a single ant to get from start to end of that path
		i++;
	}
	return(steps);
}

int **add_option(int **options, t_lem *lem, int len)
{
	int i;
	int j;

	i = 1;
	j = 2;
	//ft_printf("previous:%d\n", options[lem->max_options - 1][0]);
	if (!(options[lem->max_options] = (int *)malloc(sizeof(int) * len)))
		ft_printf("ERRRRRRRRORRRRROORRR");
	options[lem->max_options][0] = len * -1; //sets the len (index0) to a negative number
	options[lem->max_options][1] = set_steps(options[lem->max_options - 1], lem,  lem->ants); //
	ft_printf("options:%d\n", options[lem->max_options][0]);
	ft_printf("options:%d\n", options[lem->max_options][1]);
	//options[0] = -3 | 10 | 0 |
	//options[1] = -4 | 10 | 0 | 1
	//options[2] = -5 | 10 | 0 | 1 | lem->i_placeholder + 1;
	while (len > 3)
	{
		options[lem->max_options][j] = options[lem->max_options - 1][j];
		ft_printf("options:%d\n", options[lem->max_options][j]);		
		i++;
		j++;
		len--;
	}
	options[lem->max_options][j] = lem->i_placeholder + i;
	ft_printf("options:%d\n", lem->i_placeholder + i);
//	lem->max_options++;
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
	int i;

	i = 2;
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
	int possibilities; //can be max the same number of ants: 13 ants with 13 possibilites means one ant per possibility!

	// i represents the length of a single int array ex. i = 3 = [1][2][3]

	compare = i;
	possibilities = 1;
	while (possibilities < 5 && possibilities != lem->max_paths && i <= lem->ants)
	{
		ft_printf("i: %d\n", i);
		ft_printf("nbr_paths:%d\n", lem->max_paths);
		while (i < lem->max_paths) //itterates thru allpaths array
		{
			/*
			**	Assumes we are comparing a "x | y | path" int array, adding onto paths as long as possible.
			**	Have to exit once it's not possible, and add next path as a single option.
			*/
			ft_printf("going into scan_similar\n");
			if (scan_similar(lem, options[compare])) // finds if the two indexes has any rooms that are similar
			{
				// steps = ants + length of path
				ft_printf("scan_similar succeeded\n");
				lem->malloc_len++;
				options = append_array(options, lem->max_options); // adding a malloced space for a valid path
				ft_printf("append_array succeeded\n");
				lem->max_options++;
				ft_printf("malloc len:%d max valid path:%d\n", lem->malloc_len, lem->max_options);
				options = add_option(options, lem, lem->malloc_len); // NEEDS TO BE FIXED
				lem->i_placeholder++;
				recursion_adding(lem, i + 1, options);
				compare++;
			}
			i++;
		}
		lem->malloc_len = 3;
		possibilities++;
		// 	add_into_allpaths(lem, forbidden); // count 0 and negative for malloc, adding
	}
	return(0);
}

int **add_first_option(int **options, t_lem *lem, int len)
{
	int j;

	j = 2;
	if (!(options[0] = (int *)malloc(sizeof(int) * len)))
		ft_printf("ERRRRRRRRORRRRROORRR");
	options[0][0] = len * -1; //sets the len (index0) to a negative number
	options[0][1] = lem->ants + (lem->all_paths[lem->i_placeholder][0] * -1) - 2; //set_steps(options[0], lem->ants); //should set the steps (index1) to # of steps 
	while (len >= 3)
	{
		options[0][j] = 0;
		ft_printf("test\n");
		j++;
		len--;
	}
	ft_printf("option[0]: %d option[1]: %d\n", options[0][0], options[0][1]);
	return (options);
}

/*
	-3 | 16 | 1    =    allpaths[0] = 
*/

int flow_management(t_lem *lem)
{
	int **options;
	int i;
	int j;

	i = 0;
	j = 0;
	if (!(options = (int **)malloc(sizeof(int *) * 1)))
		return (1);
	options = add_first_option(options, lem, 3);
	ft_printf("ADDED PATH\n");
	ft_printf("options[0][0]: %d\n", options[lem->max_options][0]);
	ft_printf("lem->max_options: %d\n", lem->max_options);
	while (j <= lem->max_options)
	{
		i = 0;
		ft_printf("option: ");
		while (i < (options[lem->max_options][0] * -1))
		{
			ft_printf(" %d |", options[lem->max_options][i]);
			i++;
		}
		ft_printf("\n");
		j++;
	}
	ft_printf("\n");
	recursion_adding(lem, 0, options);
	return (0);
}