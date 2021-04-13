#include "lem_in.h"

static char	**add_tunnel(char *line, t_lem *lem)
{
	int		i;
	char	**new;

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

static int	get_ants(int fd, char *line, t_lem *lem)
{
	get_next_line(fd, &line);
	if (!ft_isalldigit(line))
		return (1);
	lem->ants = ft_atoi(line);
	ft_printf("%s\n", line); // <---- part of the program!!
	ft_strdel(&line);
	return (0);
}

static int	get_tunnel(char *line, t_lem *lem)
{
	int i;

	i = 0;
	if (check_tunnel_validity(line, lem) == 1 || lem->found_start_end != 2
	|| lem->nbr_rooms == 0)
		return (1);
	lem->tunnels = add_tunnel(line, lem);
	i++;
	return (0);
}

static int	get_room_and_tunnel(t_lem *lem, t_room *room, char *line, int fd)
{
	while (get_next_line(fd, &line) > 0)
	{
		if (!(ft_strstr(line, "-")))
		{
			if (check_rooms_validity(line, lem) == 1 ||
			lem->found_start_end > 2)
				return (1);
			if (ft_strstr(line, "##start"))
				room->roomtype = 1;
			else if (ft_strstr(line, "##end"))
				room->roomtype = 3;
			if (!(ft_strstr(line, "#")))
				room = get_room(line, room, lem);
			ft_printf("%s\n", line); // <--------- part of the program!!
		}
		else
		{
			if (get_tunnel(line, lem))
				return (1);
			ft_printf("%s\n", line); // <--------- part of the program!!
		}
		ft_strdel(&line);
	}
	return (0);
}

int			store_data(t_lem *lem, t_room *room, int fd)
{
	char 	*line;
	int 	i;
	t_room 	*tmp;

	line = NULL;
	i = 1;
	if (get_ants(fd, line, lem))
		return (1);
	if (get_room_and_tunnel(lem, room, line, fd))
		return (1);
	if (!(lem->directory = (char**)malloc(sizeof(char *) * lem->current_roomnum)))
		return (1);
	tmp = lem->all_rooms;
	lem->directory[0] = ft_strdup("START");
	while (room->next != NULL)
	{
		lem->directory[i] = ft_strdup(room->name);
		room = room->next;
		i++;
	}
	return (0);
}
