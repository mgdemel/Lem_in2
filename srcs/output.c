#include "lem_in.h"

void	output(t_lem *lem)
{
	t_room *room;

	room = lem->all_rooms;
	ft_printf("%d\n", lem->ants);
	while (room->next != NULL)
	{
		if (room->roomtype == 1)
			ft_printf("##start\n");
		if (room->roomtype == 3)
			ft_printf("##end\n");
		ft_printf("%s %d %d\n", room->name, room->x, room->y);
		room = room->next;
	}
}
