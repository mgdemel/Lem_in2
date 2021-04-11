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

	ant = 1;
	moves_per_round = (lem->result[0] * -1) - 2;
	moves = moves_per_round;
	room_name = NULL;
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
