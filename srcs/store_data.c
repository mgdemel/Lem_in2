#include "../includes/lem_in.h"

char **add_tunnel(char *line, t_lem *lem)
{
	int i;
	char **new;

	if (!(new = (char **)malloc(sizeof(char *) * (lem->nbr_tunnels))))
		return (NULL);
	i = 0;
	if (lem->nbr_tunnels != 1)
	{
		while (i < lem->nbr_tunnels - 1)
		{
			new[i] = ft_strdup(lem->tunnels[i]);
			free(lem->tunnels[i]);
			i++;
		}
	}
	new[i] = ft_strdup(line);
	if (lem->tunnels != NULL)
		free(lem->tunnels);
	return (new);
}

static int get_ants(int fd, char *line, t_lem *lem)
{
	get_next_line(fd, &line);
	if (!ft_isalldigit(line))
		return (1);
	lem->ants = ft_atoi(line);
	ft_printf("%s\n", line); // <----------------------- part of the program!!
	ft_strdel(&line);
	return (0);
}

int get_room_type(t_lem *lem, t_room *room, char *line)
{
	ft_printf("%s\n", line); // <----------------------- part of the program!!
	if (check_rooms_validity(line, lem) == 1 || lem->found_start_end > 2)
		return (1);
	if (ft_strstr(line, "##start"))
		room->roomtype = 1;
	else if (ft_strstr(line, "##end"))
		room->roomtype = 3;
	if (!(ft_strstr(line, "#")))
		room = get_room(line, room, lem);
	return (0);
}

int store_data(t_lem *lem, t_room *room, int fd)
{
	int i;
	char *line;

	i = 0;
	line = NULL;
	if (get_ants(fd, line, lem) == 1)
		return (1);
	while (get_next_line(fd, &line) > 0)
	{
		if (!(ft_strstr(line, "-")))
		{
			ft_printf("line:%s\n", line);
			if (get_room_type(lem, room, line) == 1)
				return (1);
		}
		else
		{
			if (check_tunnel_validity(line, lem) == 1 || lem->found_start_end != 2 || lem->nbr_rooms == 0)
				return (1);
			lem->tunnels = add_tunnel(line, lem);
			i++;
		}
		ft_strdel(&line);
	}
	return (0);
}
