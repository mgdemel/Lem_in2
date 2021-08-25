#include "lem_in.h"

void	remove_deadends2(int count, int save, t_lem *lem, int before)
{
	if (count == 1 && lem->tunnel_dir[save][0] != lem->s_room_index
	&& lem->tunnel_dir[save][1] != lem->s_room_index
	&& lem->tunnel_dir[save][0] != lem->e_room_index
	&& lem->tunnel_dir[save][1] != lem->e_room_index)
	{
		if (before == 1)
			lem->tunnel_dir[save][3] = -1;
		else
			lem->tunnel_dir[save][3] = 1;
	}
}	

void	remove_deadends(t_lem *lem, int prev, int before, int save)
{	
	int	i;
	int	count;
	int	room;

	room = 1;
	while (room < lem->nbr_rooms)
	{
		count = 0;
		i = 0;
		while (i < lem->nbr_tunnels)
		{
			if ((lem->tunnel_dir[i][0] == room || lem->tunnel_dir[i][1] == room)
			&& lem->tunnel_dir[i][3] == 0 && lem->tunnel_dir[i][2] == 0)
			{
				count++;
				save = i;
			}
			i++;
		}
		remove_deadends2(count, save, lem, before);
		room++;
	}
	if (save != prev)
		remove_deadends(lem, save, before, 0);
}

void	init_tunnel_arr(t_lem *lem)
{
	int	i;
	int	j;

	i = 0;
	while (i < lem->nbr_tunnels)
	{
		j = 0;
		lem->tunnel_dir[i][2] = 0;
		lem->tunnel_dir[i][3] = 0;
		lem->tunnel_dir[i][4] = 0;
		i++;
	}
}

void	get_tunnel_rooms(t_lem *lem)
{
	int		i;
	int		j;
	char	**rooms;

	i = 0;
	while (i < lem->nbr_tunnels)
	{
		j = 0;
		rooms = ft_tunnelsplit(lem->tunnels[i], lem, 0);
		while (j < 2)
		{
			find_room_name(lem, rooms[j], i, j);
			j++;
		}
		free(rooms[0]);
		free(rooms[1]);
		free(rooms);
		i++;
	}
}

void	get_tunnel_int_arr(t_lem *lem)
{
	int	i;

	i = 0;
	lem->tunnel_dir = (int **)malloc(sizeof(int *) * lem->nbr_tunnels);
	if (lem->tunnel_dir == NULL)
		error_message(lem, 1);
	while (i < lem->nbr_tunnels)
	{
		lem->tunnel_dir[i] = (int *)malloc(sizeof(int) * 5);
		if (lem->tunnel_dir[i] == NULL)
			error_message(lem, 1);
		i++;
	}
	init_tunnel_arr(lem);
	get_tunnel_rooms(lem);
	remove_duplicated(lem);
	remove_deadends(lem, 0, 1, 0);
}
