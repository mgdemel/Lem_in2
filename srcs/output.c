#include "lem_in.h"

char	*get_room_name(t_lem *lem, int moves)
{

}

int	get_moves(t_lem *lem)
{
	int moves;
	moves = 0;

	return(moves);
}

void	output(t_lem *lem)
{
	int ant;
	int moves;
	char *room_name;
	int	*result;

	ant = 1;
	moves = 0;
	room_name = NULL;
	while (ant <= lem->ants)
	{
		moves = get_moves(lem);
		while (moves > 0)
		{
			room_name = get_room_name(lem, moves);
			ft_printf("L%d-%s ", ant, room_name);
			ant--;
		}
		moves--;
	}
}
