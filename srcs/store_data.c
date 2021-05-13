#include "lem_in.h"

static char	**add_tunnel(char *line, t_lem *lem)
{
	int		i;
	char	**new;

	i = 0;
	if (!(new = (char **)malloc(sizeof(char *) * (lem->nbr_tunnels))))
		return (NULL);
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
	ft_putendl(line);
	ft_strdel(&line);
	return (0);
}

static int	get_tunnel(char *line, t_lem *lem)
{
	int	i;

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
		if (ft_strstr(line, " ") || ft_strstr(line, "#"))
		{
			if (check_rooms_validity(line, lem, 0, 0) == 1
				|| lem->found_start_end > 2)
				return (1);
			if (ft_strstr(line, "##start"))
				room->roomtype = 1;
			else if (ft_strstr(line, "##end"))
				room->roomtype = 3;
			if (!(ft_strstr(line, "#")))
				room = get_room(line, room, lem);
			ft_putendl(line);
		}
		else
		{
			if (get_tunnel(line, lem))
				return (1);
			ft_putendl(line);
		}
		ft_strdel(&line);
	}
	return (0);
}

int	store_data(t_lem *lem, t_room *room, int fd)
{
	char	*line;
	int		i;
	t_room	*tmp;

	line = NULL;
	i = 1;
	if (get_ants(fd, line, lem))
		return (1);
	if (get_room_and_tunnel(lem, room, line, fd))
		return (1);
	if (!(lem->room_directory = (char **)malloc(sizeof(char *) * lem->current_roomnum)))
		return (1);
	tmp = lem->all_rooms;
	lem->room_directory[0] = ft_strdup("SKIP");
	while (room->next != NULL)
	{
		if (ft_strcmp(room->name, lem->e_room_name) == 0)
			lem->e_room_index = i;
		if (ft_strcmp(room->name, lem->s_room_name) == 0)
			lem->s_room_index = i;
		if (room_duplicates(lem, room->name, i) == 1)
		{
			ft_printf("ERROR\n"); //change to error function
			exit(1);
		}
		else
			lem->room_directory[i] = ft_strdup(room->name);
		room = room->next;
		i++;
	}
	return (0);
}
