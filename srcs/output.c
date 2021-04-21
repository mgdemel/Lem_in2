#include "lem_in.h"
	//Options:
	// i       len     steps       paths
	// 1       -4      5           0 2
	// result = [-4, 5, 0, 2]
	// path 0 = [1, 3, 4, 8]
	// path 2 = [1, 2, 5, 6, 8]
	// lem->setss = 5 (total sets per output)
	// moves_per_set = 2 (the number of paths being used each round)
	
	// options 2 = [-4,        5,        0,       				2]
	// 									  |						|
	// final paths 0 = 					  [-4, 1, 3, 4, 8, -1]	|
	// final paths 2 = 											[-5, 1, 2, 5, 6, 8, -1]




int	output(t_lem *lem)
{
	int moves_per_set;
	int ant_num;
	int i;
	int j;
	int x;
	int **ant_flow;

	i = 2;
	j = 2; //skips over the start room!
	x = 0;
	moves_per_set = (lem->result[0] * -1) - 2;
	ant_num = 1;
	lem->sets = lem->result[1];

	if (!(ant_flow = (int **)malloc(sizeof(int *) * moves_per_set))) //makes as many rows as there are paths
		return (1);
	while(x < moves_per_set)
	{
		if (!(ant_flow[x] = (int *)malloc(sizeof(int) * )))
			return (1);
		x++;
	}
// --------------------------- TESTING START ------------------------------
	// int x = 2; //remove!
	// int y = 1; //remove!

	// print_int_arr(lem->result, lem->result[0] * -1, "result");
	// ft_printf("rows to print (result[1]): %d\nnumber of paths to use (result[0 - 2]): %d\n\npaths:\n", lem->sets, moves_per_set);
	// while (x < (lem->result[0] * -1))
	// {
	// 	y = 1;
	// 	while (y < (lem->final_paths[lem->result[x]][0] * -1))
	// 	{
	// 		ft_printf("Final path num: %d\n", lem->final_paths[lem->result[x]][y]);
	// 		ft_printf("Name:%s\n", lem->room_directory[lem->final_paths[lem->result[x]][y]]);
	// 		y++;
	// 	}
	// 	x++;
	// 	if (x < (lem->result[0] * -1))
	// 		ft_printf("\n\n");
	// }
	// ft_printf("\nmoves:%d, mpr:%d \n\n", lem->sets, moves_per_round);
// --------------------------- TESTING DONE ------------------------------
	while (lem->ants > 0) 
	{
		while (lem->sets > 0)
		{
			moves_per_set = ((lem->result[0] * -1) - 2);
			i = 2; //first path in result
			while (moves_per_set > 0 && lem->ants > 0)
			{
				if (ft_strcmp((lem->room_directory[lem->final_paths[lem->result[i]][j]]), lem->room_directory[lem->e_room_index] != 0))
					ft_printf("L%d-%s ", ant_num, lem->room_directory[lem->final_paths[lem->result[i]][j]]);
				ant_num++;
				i++;
				lem->ants--;
				moves_per_set--;
			}
			k++;
			lem->sets--;
			ft_printf("\n");
		}
	}
}

//sets ant_num:
//0    | 1 | 2 |
//1    | 1 | 2 | 3 | 4 |
//2    | 1 | 2 | 3 | 4 | 5 |
//3	   | 2 | 3 | 4 | 5 |
//5    | 4 | 5 |

// L1-three L2-two 
// L1-four  L2-five  	L3-three L4-two 
// L1-eight L2-six 		L3-four  L4-five  		L5-three
// 			L2-eight 	L3-eight L4-six 		L5-four
// 								 L4-eight 		L5-eight


//ant  |1|0|
//ant  |2|-2|
//ant  |3|-2|
//ant  |4|-3|
//ant  |5|-3|






