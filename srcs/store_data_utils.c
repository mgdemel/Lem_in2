#include "lem_in.h"

static int	get_room_data(char *line, t_room *room, t_lem *lem)
{
	int len;

	len = 0;
	while (line[len] != ' ')
		len++;
	if (!(room->name = (char *)malloc(sizeof(char) * len + 1)))
		return (1);
	room->name[len] = '\0';
	while (len > 0)
	{
		len--;
		room->name[len] = line[len];
	}
	if (room->roomtype == 1 || room->roomtype == 3)
	{
		if (room->roomtype == 1)
			lem->start_room_name = ft_strdup(room->name);
		else
			lem->e_room_name = ft_strdup(room->name);
	}
	return (0);
}

t_room		*get_room(char *line, t_room *room, t_lem *lem)
{
	room->next = initialize_room(lem);
	get_room_data(line, room, lem);
	return (room->next);
}

int			find_start_end(char *line, t_lem *lem)
{
	if (ft_strstr(line, "##start") || ft_strstr(line, "##end"))
	{
		lem->found_start_end++;
		return (1);
	}
	return (0);
}

int			check_rooms_validity(char *line, t_lem *lem)
{
	int i;
	int space;

	space = 0;
	i = 0;
	if (find_start_end(line, lem))
		return (0);
	else if (ft_strstr(line, " ") || ft_strstr(line, "#"))
	{
		if (ft_strstr(line, "#"))
			return (0);
		else
		{
			while (line[i] != '\0')
			{
				if (line[i] == ' ')
					space++;
				i++;
			}
			lem->nbr_rooms++;
		}
	}
	if (space == 2)
		return (0);
	return (1);
}

int			check_tunnel_validity(char *line, t_lem *lem)
{
	if (ft_strstr(line, "-") || ft_strstr(line, "#"))
	{
		if (ft_strstr(line, "#"))
			return (0);
		lem->nbr_tunnels++;
	}
	else
		return (1);
	return (0);
}
