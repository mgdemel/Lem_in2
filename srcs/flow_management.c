#include "lem_in.h"

int compare(int *final_paths, int *other_path)
{
	int i;
	int j;

	i = 2;
	print_int_arr(final_paths, final_paths[0] * -1, "Final_paths");
	print_int_arr(other_path, other_path[0] * -1, "other_path");
	while (i < (final_paths[0] * -1) - 1)
	{
		j = 2;
		while (j < (other_path[0] * -1) - 1)
		{
			if (final_paths[i] == other_path[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int		set_steps(int **path, t_lem *lem, int ants)
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
	while (i < path[0][0] * -1)
	{
		// find the actual path stored at this index from the other array
		// take the value of that path's first index * -1
		// store that value into path_len
		// steps = how many steps it takes a single ant to get from start to end of that path
		i++;
	}
	return(steps);
}

int **add_minor_option(int **options, t_lem *lem, int len, int num)
{
	int i;
	int j;

	i = 1;
	j = 2;
	ft_printf("\nSTARTING ADD MINOR OPTION\n");
	ft_printf("Values\nlen:%d\nnum:%d\n", len, num);
	//ft_printf("previous:%d\n", options[lem->index_options - 1][0]);
	if (!(options[num] = (int *)malloc(sizeof(int) * len)))
		ft_printf("ERRRRRRRRORRRRROORRR");
	options[num][0] = len * -1; //sets the len (index0) to a negative number
	//options[0] = -3 | 10 | 0 |
	//options[1] = -4 | 10 | 0 | 1
	//options[2] = -5 | 10 | 0 | 1 | lem->i_placeholder + 1;
	while (len > 3)
	{
		options[num][j] = options[num - 1][j];
		j++;
		len--;
	}
	options[num][j] = lem->i_placeholder + 1;
	options[num][1] = set_steps(options, lem,  lem->ants);
	print_int_arr(options[num], options[num][0] * -1, "Minor Options");
//	lem->index_options++;
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

/*

	SUB_MAP
	final_paths:
	i       len         rooms
	0                   1 3 4 8
	1                   1 2 4 8
	2                   1 2 5 6 8
	3                   1 2 7 6 8
	4                   1 3 5 6 8

    Options:
	i       len     steps       paths
	0       -3      x           0     | while
	1       -4      x           0 2
	2       -3      x           1     | while               
	3       -4      x           1 4
	4       -3      x           2     
	5       -3      x           3
	6       -3      x           4

*/

int scan_similar(t_lem *lem, int *index_of_valid_paths, int *to_compare)
{
	int i;

	i = 2;
	ft_printf("index_of_valid_paths[0]:%d\n", index_of_valid_paths[0]);
	while (i < (index_of_valid_paths[0] * -1)) // MIG?HT HAVE TO BE < not <=
	{
		// index_of_valid_paths  == -3 | 0 |     0
		//index_of_valid_paths = -5 | 4 | 0 | 1 | 2
		ft_printf("Comparing final_paths[%d]\n", index_of_valid_paths[i]);
		if (compare(lem->final_paths[index_of_valid_paths[i]], to_compare) == 1)
		{
			ft_printf("RETURNING THE COMPARE 1\n");
			return (1);
		}
		i++;
	}
	ft_printf("Returning 0 :)\n");
	return (0);
}

int **recursion_adding(t_lem *lem, int **options, int compare)
{
	int i;

	i = 0;
	/*
	**	Malloc_len as a stopping point for while loop?
	*/
	ft_printf("max_paths: %d\n", lem->max_paths);
	if (lem->i_placeholder < lem->max_paths - 1)
	{
		// num == what we need to compare
		// if num == 2, then we move in while loop TWICE and compare it to 3, and 4, moving into this function again if one is compared succefully
		// if num == 3, then we move in while loop ONCE and compare it to 4, which is the last of allpaths indexes
		// if num == 4, don't do this while loop
		while (compare < lem->max_paths) 
		{
			/*
			**	Assumes we are comparing a "x | y | path" int array, adding onto paths as long as possible.
			**	Have to exit once it's not possible, and add next path as a single option.
			*/
			ft_printf("going into scan_similar with options[num]:%d\n", lem->i_placeholder - 1);
			if (scan_similar(lem, options[lem->i_placeholder - 1], lem->final_paths[compare]) == 0) // finds if the two indexes has any rooms that are similar
			{
				ft_printf("scan_similar succeeded\n");
				lem->malloc_len++;
				options = append_array(options, lem->i_placeholder); // adding a malloced space for a valid path
				ft_printf("append_array succeeded\n");
				ft_printf("malloc len:%d num:%d\n", lem->malloc_len, lem->i_placeholder);
				options = add_minor_option(options, lem, lem->malloc_len, lem->i_placeholder); // NEEDS TO BE FIXEDfd
				print_int_arr(options[lem->i_placeholder], options[lem->i_placeholder][0] * -1, "Options:");
				print_double_arr(options, lem->i_placeholder);
				
				// lem->compare++; // index of options[compare] should go linearly
				lem->i_placeholder++;
				options = recursion_adding(lem, options, compare + 1);
				ft_printf("END OF IF\n");
			}
			compare++;
			ft_printf("increasing compare:%d\n", compare);
		}
	
	}
	ft_printf("ENDED RECURSION\n");
	lem->malloc_len = 3;
	return(options);
}

int **add_major_option(int **options, t_lem *lem, int index, int num)
{
	if (!(options[index] = (int *)malloc(sizeof(int) * 3)))
		ft_printf("ERRRRRRRRORRRRROORRR");
	options[index][0] = -3; //sets the len (index0) to a negative number
	options[index][1] = lem->ants + (lem->final_paths[num][0] * -1) - 2; //set_steps(options[0], lem->ants); //should set the steps (index1) to # of steps 
	options[index][2] = num;
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
	int compare;
	int	major_index;

	i = 0;
	j = 0;
	compare = 0;
	major_index = 0;
	lem->i_placeholder = 0;
	if (!(options = (int **)malloc(sizeof(int *) * 1)))
		return (1);
	options = add_major_option(options, lem, lem->i_placeholder, 0);
	print_int_arr(options[lem->i_placeholder], options[lem->i_placeholder][0] * -1, "Options:");
	while (major_index <= lem->max_paths - 1)
	{
		if (lem->i_placeholder != 0)
		{
			ft_printf("major_index:%d\n", major_index);
			options = append_array(options, lem->i_placeholder);
			add_major_option(options, lem, lem->i_placeholder, major_index);
			print_int_arr(options[lem->i_placeholder], options[lem->i_placeholder][0] * -1, "Options:");
		}
		lem->i_placeholder++;
		major_index++;
		compare++;
		options = recursion_adding(lem, options, compare);
		ft_printf("DID THE RECURSION\n");
		ft_printf("i_placeholder:%d\n", lem->i_placeholder);
	}
	print_double_arr(options, lem->i_placeholder);
	return (0);
}