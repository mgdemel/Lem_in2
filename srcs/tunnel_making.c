#include "lem_in.h"

void	find_room_name(t_lem *lem, char *room_name, int row, int column)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (i < (lem->nbr_rooms + 1))
	{
		if (ft_strcmp(lem->room_directory[j], room_name) == 0)
			lem->tunnel_dir[row][column] = j;
		else
			j++;
		i++;
	}
}

void	remove_duplicated(t_lem *lem)
{
	int	i;
	int	j;
	int	save1;
	int	save2;

	i = 0;
	while (i < lem->nbr_tunnels)
	{
		j = 0;
		save1 = lem->tunnel_dir[i][0];
		save2 = lem->tunnel_dir[i][1];
		while (j < lem->nbr_tunnels)
		{
			if (j != i && ((lem->tunnel_dir[j][0] == save1
				&& lem->tunnel_dir[j][1] == save2)
				|| (lem->tunnel_dir[j][0] == save2
				&& lem->tunnel_dir[j][1] == save1))
				&& lem->tunnel_dir[j][2] == 0)
			{
				lem->tunnel_dir[i][0] = -1;
				lem->tunnel_dir[i][1] = -1;
			}
			j++;
		}
		i++;
	}
}

int	tunnel_room_scan(t_lem *lem, int i, int b, char *tunnel)
{
	int	a;

	a = 0;
	while (lem->room_directory[i][a] != '\0'
		&& lem->room_directory[i][a] == tunnel[b])
	{
		a++;
		b++;
		if (lem->room_directory[i][a] == '\0'
			&& (tunnel[b] == '-' || tunnel[b] == '\0'))
		{
			lem->tunnel_index = b + 1;
			return (1);
		}
	}
	return (0);
}

char	**ft_tunnelsplit(char *tunnel, t_lem *lem)
{
	char	**rooms;
	int		y;
	int		b;
	int		i;

	y = 0;
	rooms = (char **)malloc(sizeof(char *) * 2);
	if (rooms == NULL)
		error_message(lem, 1);
	while (y < 2)
	{
		i = 1;
		while (i < lem->nbr_rooms + 1)
		{
			b = lem->tunnel_index;
			if (tunnel_room_scan(lem, i, b, tunnel) == 1)
			{
				rooms[y] = ft_strdup(lem->room_directory[i]);
				break ;
			}
			i++;
		}
		y++;
	}
	lem->tunnel_index = 0;
	return (rooms);
}

void	get_tunnel_int_arr(t_lem *lem)
{
	int		i;
	int		j;
	char	**rooms;

	i = 0;
	j = 0;
	lem->tunnel_dir = (int **)malloc(sizeof(int *) * lem->nbr_tunnels);
	if (lem->tunnel_dir == NULL)
		error_message(lem, 1);
	while (i < lem->nbr_tunnels)
	{
		lem->tunnel_dir[i] = (int *)malloc(sizeof(int) * 3);
		if (lem->tunnel_dir[i] == NULL)
			error_message(lem, 1);
		i++;
	}
	i = 0;
	while (i < lem->nbr_tunnels)
	{
		j = 0;
		rooms = ft_tunnelsplit(lem->tunnels[i], lem);
		lem->tunnel_dir[i][2] = 0;
		lem->tunnel_dir[i][3] = 0;
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
	remove_duplicated(lem);
}
