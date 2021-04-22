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
void print_ant_dir(t_lem *lem, int **ant_flow)
{
		int i = 0;
		int j = 0;
		while(i < lem->ants)
		{
			j = 0;
			while (j < 3)
			{
				ft_printf(" %d |", ant_flow[i][j]);
				j++;
			}
			ft_printf("\n");
			i++;
		}
		ft_printf("\n");
}


void move_it(int sets, int **ant_flow, t_lem *lem)
{
	int i;
	int j;
	int k;
	int flow;

	i = 0;
	k = 1;
	flow = 1;
	while (sets > 0)
	{
		i = 0;
		j = 2;
		while (i < lem->ants)
		{
			ft_printf("here with i:%d and ants:%d\n", i, lem->ants);
			if (ant_flow[i][1] == 0)
			{
				ant_flow[i][2] = 1; // closes lock
				ft_printf("LOCKED FLOW\n");
				print_ant_dir(lem, ant_flow);
				i++;
			}
			if (lem->room_directory[lem->final_paths[lem->result[j]][k + flow]] != '\0' && ant_flow[i][2] == 0)
			{
				ft_printf("L%d-%s ", ant_flow[i][0], lem->room_directory[lem->final_paths[lem->result[j]][k + flow]]);
				ft_printf("\nj: %d, what's in there before: %d\n", j, lem->result[j]);
				ant_flow[i][1] += 1;
				ant_flow[i][2] = 0; // opens lock
				i++;
				if (j < (lem->result[0] * -1) -1)
					j++;
				else
					j = 2;
				ft_printf("\nj: %d, what's in there after: %d\n", j, lem->result[j]);
				ft_printf("\nFLOW\n");
				print_ant_dir(lem, ant_flow);
			}
			else
			 i++;
		}
		flow++;
		sets--;
		ft_printf("\n");
		ft_printf("END OF SET\n");
		print_ant_dir(lem, ant_flow);
	}
	ft_printf("FINAL FLOW\n");
	print_ant_dir(lem, ant_flow);
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
		if (!(ant_flow[i] = (int*)malloc(sizeof(int) * 3)))
			return (1);
		i++;
	}

// --------------------------- TESTING START ------------------------------
	i = 2; //remove!

	print_int_arr(lem->result, lem->result[0] * -1, "result");
	ft_printf("rows to print (result[1]): %d\nnumber of paths to use (result[0 - 2]): %d\n\npaths:\n", lem->sets, moves_per_set);
	while (i < (lem->result[0] * -1))
	{
		j = 1;
		while (j < (lem->final_paths[lem->result[i]][0] * -1))
		{
			ft_printf("Final path num: %d\n", lem->final_paths[lem->result[i]][j]);
			ft_printf("Name:%s\n", lem->room_directory[lem->final_paths[lem->result[i]][j]]);
			j++;
		}
		i++;
		if (i < (lem->result[0] * -1))
			ft_printf("\n\n");
	}
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
			ant_flow[i][2] = 1; //initialized as blocked
			ant_num++;
			moves_per_set--;
			i++;
			j++;
		}
	}
	i = 0;
	moves_per_set = ((lem->result[0] * -1) - 2);
	while (i < moves_per_set)
	{
		ant_flow[i][2] = 0; //unlocks for first set
		i++;
	}
	ft_printf("FLOW INIT\n");
	print_ant_dir(lem, ant_flow);
	move_it(lem->result[1], ant_flow, lem);
	return(0);
}

// L1-three L2-two 
// L1-four  L2-five  	L3-three L4-two 
// L1-eight L2-six 		L3-four  L4-five  		L5-three
// 			L2-eight 	L3-eight L4-six 		L5-four
// 								 L4-eight 		L5-eight

//ant  |1|0|1
//ant  |2|-2|1
//ant  |3|-2|1
//ant  |4|-3|1
//ant  |5|-3|1
