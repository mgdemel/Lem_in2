#include "lem_in.h"

// char	*get_room_name(t_lem *lem, int moves)
// {

// }

void	output(t_lem *lem)
{
	int ant;
	int moves_per_round;
	int moves;
	char *room_name;
	int i;
	int j;

	i = 2;
	ant = 1;
	moves_per_round = (lem->result[0] * -1) - 2;
	moves = moves_per_round;
	room_name = NULL;

/*
	options 2 = [-4,        9,        0,       				2]
									  |						|
	final paths 0 = 				[-4, 1, 3, 4, 8, -1]	|
	final paths 2 = 										[-5, 1, 2, 5, 6, 8, -1]
*/	
	ft_printf("OUTPUT TESTING\n");
	ft_printf("\nALL FINAL PATHS:\n");
	//print_double_arr(lem->final_paths, lem->max_paths);
	//print_int_arr(lem->result, lem->result[0] * -1, "result");
	ft_printf("lem->result[0] * -1) -2:%d\n", (lem->result[0] * -1));
	ft_printf("RESULT:\n");
	while (i < (lem->result[0] * -1))
	{
		j = 1;
		while (j < (lem->final_paths[lem->result[i]][0] * -1))
		{
		//	ft_printf("Final path num: %d\n", lem->final_paths[lem->result[i]][j]);
		//	ft_printf("Name:%s\n", lem->room_directory[lem->final_paths[lem->result[i]][j]]);
			j++;
		}
		i++;
		if (i < (lem->result[0] * -1))
			ft_printf("\nCHAINGING PATH\n");
	}

	// Testing stops

//
//	while (moves < lem->result[1])
//	{
//
//		moves++;
//	}


	while (ant < lem->ants && moves < lem->result[1])
	{
		ft_printf("moves:%d, mpr:%d, ant:%d\n", moves, moves_per_round, ant);
		moves_per_round = (lem->result[0] * -1) - 2;
		while (moves_per_round > 0 && ant < lem->ants)
		{
			//room_name = get_room_name(lem, moves);
			//need some kind of recursion that keeps track of how the first round of ants progress while also adding the next round of ants in the next step
			ft_printf("L%d- ", ant);
			ant++;
			moves_per_round--;
		}
		ft_printf("\n");
		moves += moves_per_round;
	}
}

//    Options:
	// i       len     steps       paths
	// 1       -4      9           0 2
	// result = [-4, 9, 0, 2]
	// path 0 = [1, 3, 4] we need to convert that number into the actual room name by going to that numeric address in the linked list
	// moves = 9 (total moves per output)
	// moves_per_round = 2 (the number of paths being used each round)
	
	// make a function that goes into the appropriate path and finds the appropriate room index and converts that back to the room name


// L1-1 L2-2 
// L1-3 L2-4 L3-1 L4-2
// L1-5 L2-6 L3-3 L4-4 L5-1 L6-2
// L1-E L2-E L3-5 L4-6 L5-3 L6-4
// L3-E L4-E L5-5 L6-6
// L5-E L6-E


// L1-1 L2-2
// L1-4 L3-1 L2-3
// L3-4 L2-4