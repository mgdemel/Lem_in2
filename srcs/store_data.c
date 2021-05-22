#include "lem_in.h"

static char	**add_tunnel(char *line, t_lem *lem)
{
	int		i;
	char	**new;

	i = 0;
	new = (char **)malloc(sizeof(char *) * lem->nbr_tunnels);
	if (new == NULL)
		error_message(lem, 1);
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

void	get_ants(int fd, char *line, t_lem *lem)
{
	get_next_line(fd, &line);
	if (!ft_isalldigit(line) || ft_atoi(line) == 0
		|| ft_isspace(ft_atoi(&line[0]) == 1))
		error_message(lem, 2);
	lem->ants = ft_atoi(line);
	ft_putendl(line);
	ft_strdel(&line);
}

void	get_tunnel(char *line, t_lem *lem)
{
	int	i;

	i = 0;
	if (lem->found_start_end != 2)
		error_message(lem, 6);
	if (lem->nbr_rooms == 0)
		error_message(lem, 3);
	check_tunnel_validity(line, lem);
	lem->tunnels = add_tunnel(line, lem);
	i++;
}

void	get_room_and_tunnel(t_lem *lem, t_room *room, char *line, int fd)
{
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strstr(line, " ") || ft_strstr(line, "#"))
		{
			check_rooms_validity(line, lem, 0, 0);
			if (lem->found_start_end > 2)
				error_message(lem, 7);
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
			get_tunnel(line, lem);
			ft_putendl(line);
		}
		ft_strdel(&line);
	}
}

void	store_data(t_lem *lem, t_room *room, int fd)
{
	char	*line;
	int		i;
	t_room	*tmp;

	line = NULL;
	i = 1;
	get_ants(fd, line, lem);
	get_room_and_tunnel(lem, room, line, fd);
	lem->room_directory = (char **)malloc(sizeof(char *) * lem->current_roomnum);
	if (lem->room_directory == NULL)
		error_message(lem, 1);
	tmp = lem->all_rooms;
	lem->room_directory[0] = ft_strdup("SKIP");
	while (room->next != NULL)
	{
		if (ft_strcmp(room->name, lem->e_room_name) == 0)
			lem->e_room_index = i;
		if (ft_strcmp(room->name, lem->s_room_name) == 0)
			lem->s_room_index = i;
		room_duplicates(lem, room->name, i);
		lem->room_directory[i] = ft_strdup(room->name);
		room = room->next;
		i++;
	}
}
