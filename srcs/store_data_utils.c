#include "../includes/lem_in.h"

static int	get_room_data(char *line, t_room *room, t_lem *lem)
{
	int len;
	int i;

	len = 0;
	while (line[len] != ' ')
		len++;
	if (!(room->name = (char *)malloc(sizeof(char) * len + 1)))
		return (1);
	line[len] = '\0';
	i = len;
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
			lem->end_room_name = ft_strdup(room->name);
	}
	i++;
	room->x = ft_atoi(&line[i]);
	while (line[i] != ' ')
		i++;
	room->y = ft_atoi(&line[i]);
	return (0);
}

t_room		*get_room(char *line, t_room *room, t_lem *lem)
{
	room->next = initialize_room(lem);
	get_room_data(line, room, lem);
	return (room->next);
}


int			check_rooms_validity(char *line, t_lem *lem)
{
	int i;
	int valid;

	valid = 0;
	i = 0;
	if (ft_strstr(line, "##start") || ft_strstr(line, "##end"))
	{
		lem->found_start_end++;
		return (0);
	}
	else if (!(ft_strstr(line, "-")))
	{
		if (ft_strstr(line, "#"))
			return (0);
		else
		{
			while (line[i] != '\0')
			{
				if (line[i] == ' ')
					valid++;
				i++;
			}
			lem->nbr_rooms++;
		}
	}
	if (valid == 2)
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