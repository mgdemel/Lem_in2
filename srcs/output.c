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

void move_it(int moves_per_set, int sets, int **ant_flow, t_lem *lem)
{
	int i;
	int j;
	int k;
	int flow;

	i = 0;
	j = 2;
	k = 1;
	flow = 1;

	while (sets > 0)
	{
		moves_per_set *= flow;
		i = 0;
		j = 2;
		while (i < (moves_per_set))
		{
			if (ant_flow[i][1] == 0)
				moves_per_set++; //increasing the scope for print!
			else
			{
				ft_printf("L%d-%s ", ant_flow[i][0], lem->room_directory[lem->final_paths[lem->result[j]][k + flow]]);
				ant_flow[i][1] += 1;
				j++;
			}
			i++;
		}
		ft_printf("\n");
		flow++;
		sets--;
	}
}
int	output(t_lem *lem)
{
	int moves_per_set;
	int ant_num;
	int i;
	int j;
	int **ant_flow;

	i = 0;
	j = 2;
	moves_per_set = (lem->result[0] * -1) - 2;
	ant_num = 1;

	if (!(ant_flow = (int**)malloc(sizeof(int*) * lem->ants))) //makes as manj rows as there are paths
		return (1);
	while (i < lem->ants)
	{
		if (!(ant_flow[i] = (int*)malloc(sizeof(int) * 2)))
			return (1);
		i++;
	}

// --------------------------- TESTING START ------------------------------
	// i = 2; //remove!

	// print_int_arr(lem->result, lem->result[0] * -1, "result");
	// ft_printf("rows to print (result[1]): %d\nnumber of paths to use (result[0 - 2]): %d\n\npaths:\n", lem->sets, moves_per_set);
	// while (i < (lem->result[0] * -1))
	// {
	// 	j = 1;
	// 	while (j < (lem->final_paths[lem->result[i]][0] * -1))
	// 	{
	// 		ft_printf("Final path num: %d\n", lem->final_paths[lem->result[i]][j]);
	// 		ft_printf("Name:%s\n", lem->room_directory[lem->final_paths[lem->result[i]][j]]);
	// 		j++;
	// 	}
	// 	i++;
	// 	if (i < (lem->result[0] * -1))
	// 		ft_printf("\n\n");
	// }
// --------------------------- TESTING DONE ------------------------------

	i = 0;
	while (i < lem->ants) 
	{
		moves_per_set = ((lem->result[0] * -1) - 2);
		j = 2;
		while (ant_num <= lem->ants && moves_per_set > 0)
		{
			ant_flow[i][0] = ant_num;
			ant_flow[i][1] = lem->final_paths[lem->result[j]][0] + 2;
			ant_num++;
			moves_per_set--;
			i++;
			j++;
		}
	}

	// --------------------------- TESTING START ------------------------------
	// i = 0;
	// j = 0;
	// while(i < lem->ants)
	// {
	// 	j = 0;
	// 	while (j < 2)
	// 	{
	// 		ft_printf(" %d |", ant_flow[i][j]);
	// 		j++;
	// 	}
	// 	ft_printf("\n");
	// 	i++;
	// }
	// ft_printf("\n");
	// --------------------------- TESTING DONE ------------------------------
	move_it(moves_per_set, lem->result[1], ant_flow, lem);
	return(0);
}

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
