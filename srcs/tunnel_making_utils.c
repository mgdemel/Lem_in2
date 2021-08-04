#include "lem_in.h"

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

char	**ft_tunnelsplit(char *tunnel, t_lem *lem, int y)
{
	char	**rooms;
	int		b;
	int		i;

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
	int	s1;
	int	s2;

	i = 0;
	while (i < lem->nbr_tunnels)
	{
		j = 0;
		s1 = lem->tunnel_dir[i][0];
		s2 = lem->tunnel_dir[i][1];
		while (j < lem->nbr_tunnels)
		{
			if (j != i && ((lem->tunnel_dir[j][0] == s1
					&& lem->tunnel_dir[j][1] == s2)
				|| (lem->tunnel_dir[j][0] == s2 && lem->tunnel_dir[j][1] == s1))
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
